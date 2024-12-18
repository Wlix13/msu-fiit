#include "library.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <iostream>
#include <vector>

using Eigen::SparseMatrix;
using Eigen::VectorXd;
using Eigen::Triplet;

bool SolveSpline(
    const double* x, const double* y, int n,
    double derivStart, double derivEnd,
    double* splineCoeffs, int* stopCode)
{
    try
    {
        if (n < 2)
        {
            *stopCode = InvalidInput;
            return false;
        }

        // Precompute differences
        std::vector<double> h(n - 1);
        for (int i = 0; i < n - 1; ++i)
        {
            h[i] = x[i + 1] - x[i];
            if (h[i] <= 0)
            {
                *stopCode = InvalidInput;
                return false;
            }
        }

        // Prepare tri-diagonal matrix using SparseMatrix
        SparseMatrix<double> A(n, n);
        std::vector<Triplet<double>> coefficients;
        VectorXd b = VectorXd::Zero(n);

        // Start boundary
        coefficients.emplace_back(0, 0, 2 * h[0]);
        coefficients.emplace_back(0, 1, h[0]);
        b(0) = 6 * ((y[1] - y[0]) / h[0] - derivStart); // First derivative at start

        // Internal points
        for (int i = 1; i < n - 1; ++i)
        {
            coefficients.emplace_back(i, i - 1, h[i - 1]);
            coefficients.emplace_back(i, i, 2 * (h[i - 1] + h[i]));
            coefficients.emplace_back(i, i + 1, h[i]);
            b(i) = 6 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]);
        }

        // End boundary
        coefficients.emplace_back(n - 1, n - 2, h[n - 2]);
        coefficients.emplace_back(n - 1, n - 1, 2 * h[n - 2]);
        b(n - 1) = 6 * (derivEnd - (y[n - 1] - y[n - 2]) / h[n - 2]); // First derivative at end

        // Build sparse matrix
        A.setFromTriplets(coefficients.begin(), coefficients.end());

        // Solve the sparse linear system
        Eigen::SimplicialLDLT<SparseMatrix<double>> solver;
        solver.compute(A);
        if (solver.info() != Eigen::Success)
        {
            *stopCode = DecompositionFailed;
            return false;
        }

        VectorXd splineCoefficients = solver.solve(b);
        if (solver.info() != Eigen::Success)
        {
            *stopCode = SolveFailed;
            return false;
        }

        // Copy results to output
        std::copy_n(splineCoefficients.data(), n, splineCoeffs);

        *stopCode = Success;
        return true;
    }
    catch (...)
    {
        *stopCode = UnknownError;
        return false;
    }
}
