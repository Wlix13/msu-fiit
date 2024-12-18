using System.Numerics;

namespace lab3;

public static class Lab3
{
    public static void Main(string[] args)
    {
        var inputData = GenerateNonUniformGrid(0.0, 10.0, 7);
        var dataArr = new V1DataArray("Test", DateTime.Now, inputData, (double x, ref Complex y1, ref Complex y2) =>
        {
            // var random = new Random();
            // var value = random.NextDouble() * random.NextDouble() * 10;
            var value = x * x * x;
            y1 = new Complex(value, 0);
            y2 = new Complex(value, 0);
        });

        var splineData = new SplineData(
            dataArr,
            1000,
            100,
            -100
        );
        splineData.BuildSpline();

        Console.WriteLine(splineData.ToLongString("F3"));

        splineData.Save("spline_results.txt", "F3");
        splineData.SaveAsPlot();
    }

    public static double[] GenerateNonUniformGrid(double start, double end, int numPoints)
    {
        var grid = new double[numPoints];
        var rand = new Random();

        grid[0] = start;
        grid[^1] = end;

        for (var i = 1; i < numPoints - 1; i++)
        {
            var fraction = i / (double)(numPoints - 1);
            var uniformPoint = start + fraction * (end - start);
            var perturbation = (rand.NextDouble() - 0.5) * (end - start) / (2 * numPoints);
            grid[i] = uniformPoint + perturbation;
        }

        Array.Sort(grid);

        return grid;
    }
}