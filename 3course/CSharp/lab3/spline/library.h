#ifndef SPLINE_LIBRARY_H
#define SPLINE_LIBRARY_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

enum StopCode
{
    Success = 0,
    InvalidInput = 1,
    DecompositionFailed = 2,
    SolveFailed = 3,
    UnknownError = 4
};

extern "C" {
    EXPORT bool SolveSpline(
        const double* x, const double* y, int n,
        double derivStart, double derivEnd,
        double* splineCoeffs, int* stopReason);
}

#endif //SPLINE_LIBRARY_H
