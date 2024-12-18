using System.Collections.Concurrent;
using System.Runtime.InteropServices;
using System.Text;
using OxyPlot;
using OxyPlot.ImageSharp;
using OxyPlot.Series;

namespace lab3;

#pragma warning disable S112 // General exceptions should never be thrown
#pragma warning disable S2365 // Properties should be used to access the value of the field


enum StopCode
{
    Success = 0,
    InvalidInput = 1,
    DecompositionFailed = 2,
    SolveFailed = 3,
    UnknownError = 4
}

public class SplineData(
    V1DataArray v1DataArray,
    int numKnots,
    double firstDerivativeStart,
    double firstDerivativeEnd
)
{
    public V1DataArray Data { get; } = v1DataArray;
    private int NumKnots { get; } = numKnots;
    private double FirstDerivativeStart { get; } = firstDerivativeStart;
    private double FirstDerivativeEnd { get; } = firstDerivativeEnd;
    private double[] SplineCoefficients { get; } = new double[v1DataArray.XArray.Length];
    private double[] RealYArray => Data.YArray.Where((v, i) => i % 2 == 0).Select(v => v.Real).ToArray();

    [DllImport(@"./spline/libspline.dylib", CallingConvention = CallingConvention.Cdecl)]
    private static extern bool SolveSpline(
        double[] x, double[] y, int numKnots,
        double derivStart, double derivEnd,
        double[] splineCoeffs, out int stopCode
    );

    // Call the native C++ function to solve the spline
    public void BuildSpline()
    {
        var x = Data.XArray;
        if (x.Length < 2)
            throw new Exception("Number of knots must be at least 2!");

        var y = new double[Data.YArray.Length / 2];
        for (int i = 0, j = 0; i < Data.YArray.Length; i += 2, j++)
            y[j] = Data.YArray[i].Real;

        var success = SolveSpline(
            x, y, x.Length,
            FirstDerivativeStart, FirstDerivativeEnd,
            SplineCoefficients, out int stopCode
        );

        if (!success)
            throw new Exception(Enum.GetName(typeof(StopCode), stopCode));
    }

    private static double[] GenerateGrid(double minX, double maxX, int numKnots)
    {
        var knots = new double[numKnots];
        var step = (maxX - minX) / (numKnots - 1);
        for (var i = 0; i < numKnots; i++) knots[i] = minX + i * step;

        return knots;
    }

    public double EvaluateSpline(double evalPoint)
    {
        var x = Data.XArray;
        var y = RealYArray;
        var secondDerivatives = SplineCoefficients;

        // Find the interval using binary search
        var i = Array.BinarySearch(x, evalPoint);
        if (i < 0) i = ~i - 1;
        i = Math.Max(0, Math.Min(i, x.Length - 2));

        // Compute h, the interval width
        var h = x[i + 1] - x[i];
        const double tolerance = 1e-10;
        if (Math.Abs(h) < tolerance)
            throw new InvalidOperationException("Zero interval width detected!");

        // Compute spline components
        var a = (x[i + 1] - evalPoint) / h;
        var b = (evalPoint - x[i]) / h;
        var c = (Math.Pow(a, 3) - a) * (h * h) / 6.0;
        var d = (Math.Pow(b, 3) - b) * (h * h) / 6.0;

        // Spline value
        return a * y[i] + b * y[i + 1] + c * secondDerivatives[i] + d * secondDerivatives[i + 1];
    }

    public string ToLongString(string format)
    {
        var sb = new StringBuilder();
        sb.Append($"V1DataArray: {Data.ToLongString(format)}\n");
        sb.Append("Spline approximation results:\n");

        for (var i = 0; i < Data.XArray.Length; i++)
            sb.Append($"Node {i + 1}: {SplineCoefficients[i].ToString(format)}\n");

        return sb.ToString();
    }

    public void Save(string filename, string format)
    {
        var content = ToLongString(format);
        File.WriteAllText(filename, content);
    }

    public void SaveAsPlot(string path = "spline_plot.png")
    {
        var plotModel = new PlotModel { Title = "Spline Visualization" };

        var lineSeries = new LineSeries
        {
            Title = "Spline",
            StrokeThickness = 2
        };

        // Evaluating spline at grid points and adding to the line series
        var uniformGrid = GenerateGrid(Data.XArray[0], Data.XArray[^1], NumKnots);
        var results = new ConcurrentQueue<DataPoint>();
        Parallel.ForEach(uniformGrid, knot =>
        {
            // Evaluate spline at each grid point (S(x)) using spline coefficients
            results.Enqueue(new DataPoint(knot, EvaluateSpline(knot)));
        });
        lineSeries.Points.AddRange(results.OrderBy(p => p.X));

        // Adding scatter series for the initial points
        var scatterSeries = new ScatterSeries
        {
            MarkerType = MarkerType.Circle,
            MarkerSize = 3,
            MarkerFill = OxyColors.Red
        };

        // Adding initial points to the scatter series
        for (var i = 0; i < Data.XArray.Length; i++)
            // Use the real part of the data YArray from Data
            scatterSeries.Points.Add(new ScatterPoint(Data.XArray[i], RealYArray[i]));

        // Adding both series to the plot model
        plotModel.Series.Add(lineSeries);
        plotModel.Series.Add(scatterSeries);

        // Save the plot as an image
        var outputPath = Path.Combine(Directory.GetCurrentDirectory(), path);
        Directory.CreateDirectory(Path.GetDirectoryName(outputPath)!);
        using var stream = File.Create(outputPath);
        var exporter = new PngExporter(1920, 1080);
        exporter.Export(plotModel, stream);

        Console.WriteLine($"Spline plot with overlaying points saved to {path}.");
        Console.WriteLine($"path");
    }
}