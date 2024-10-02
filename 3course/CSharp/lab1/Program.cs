using System.Text;
using System.Numerics;
using Spectre.Console;
using System.Security.Cryptography.X509Certificates;

#pragma warning disable IDE0290 // Use primary constructor (IDE0290)
#pragma warning disable IDE0301 // Use collection expression (IDE0301)

namespace Lab1;

// Delegate definitions
public delegate void FValues(double x, ref Complex y1, ref Complex y2);
public delegate DataItem FDI(double x);

// Struct DataItem
public struct DataItem
{
    public double X { get; set; }
    public Complex Y1 { get; set; }
    public Complex Y2 { get; set; }

    public DataItem(double x, Complex y1, Complex y2)
    {
        X = x;
        Y1 = y1;
        Y2 = y2;
    }

    public readonly override string ToString()
    {
        return ToString("F2");
    }

    public readonly string ToString(string format)
    {
        return $"X: {X.ToString(format)}, Y1: {Y1.ToString(format)}, Y2: {Y2.ToString(format)}";
    }
}

// Abstract base class V1Data
public abstract class V1Data
{
    public string Key { get; set; }
    public DateTime Date { get; set; }

    protected V1Data(string key, DateTime date)
    {
        Key = key;
        Date = date;
    }

    public abstract int XLength { get; }
    public abstract (double, double) MinMaxDifference { get; }
    public abstract string ToLongString(string format);

    public override string ToString()
    {
        return $"Type: {GetType().Name}, Key: {Key}, Date: {Date}";
    }
}

// Class V1DataList derived from V1Data
public class V1DataList : V1Data
{
    public List<DataItem> DataItems { get; set; }

    public V1DataList(string key, DateTime date) : base(key, date)
    {
        DataItems = new List<DataItem>();
    }

    public V1DataList(string key, DateTime date, double[] x, FDI F) : base(key, date)
    {
        DataItems = new List<DataItem>();
        HashSet<double> xSet = new();
        foreach (double xi in x)
        {
            if (xSet.Add(xi))
            {
                DataItem item = F(xi);
                DataItems.Add(item);
            }
        }
    }

    public override int XLength => DataItems.Count;

    public override (double, double) MinMaxDifference
    {
        get
        {
            if (DataItems.Count == 0)
                return (0.0, 0.0);

            double minDiff = double.PositiveInfinity;
            double maxDiff = double.NegativeInfinity;

            foreach (var item in DataItems) // var - местный auto
            {
                double diff = Complex.Abs(item.Y1 - item.Y2);
                if (diff < minDiff) minDiff = diff;
                if (diff > maxDiff) maxDiff = diff;
            }

            return (minDiff, maxDiff);
        }
    }

    public static explicit operator V1DataArray(V1DataList source)
    {
        double[] xArray = new double[source.DataItems.Count];
        Complex[] yArray = new Complex[source.DataItems.Count * 2];

        for (int i = 0; i < source.DataItems.Count; i++)
        {
            xArray[i] = source.DataItems[i].X;
            yArray[i * 2] = source.DataItems[i].Y1;
            yArray[i * 2 + 1] = source.DataItems[i].Y2;
        }

        V1DataArray result = new V1DataArray(source.Key, source.Date);
        result.XArray = xArray;
        result.YArray = yArray;

        return result;
    }

    public override string ToString()
    {
        return base.ToString() + $", Number of elements: {DataItems.Count}";
    }

    public override string ToLongString(string format)
    {
        var sb = new StringBuilder(ToString() + "\n");
        foreach (var item in DataItems)
        {
            sb.AppendLine(item.ToString(format));
        }
        return sb.ToString();
    }
}

// Class V1DataArray derived from V1Data
public class V1DataArray : V1Data
{
    public double[] XArray { get; set; }
    public Complex[] YArray { get; set; }

    public V1DataArray(string key, DateTime date) : base(key, date)
    {
        // Avoid zero-length array allocations
        XArray = Array.Empty<double>();
        YArray = Array.Empty<Complex>();
    }

    public V1DataArray(string key, DateTime date, double[] x, FValues F) : base(key, date)
    {
        XArray = new double[x.Length];
        YArray = new Complex[x.Length * 2];

        for (int i = 0; i < x.Length; i++)
        {
            XArray[i] = x[i];
            Complex y1 = new();
            Complex y2 = new();

            F(x[i], ref y1, ref y2);
            YArray[i * 2] = y1;
            YArray[i * 2 + 1] = y2;
        }
    }

    public DataItem? this[int index]
    {
        get
        {
            return (index >= 0 && index < XArray.Length)
                ? new DataItem(XArray[index], YArray[index * 2], YArray[index * 2 + 1])
                : null;
        }
    }

    public override int XLength => XArray.Length;

    public override (double, double) MinMaxDifference
    {
        get
        {
            if (XArray.Length == 0)
                return (0.0, 0.0);

            double minDiff = double.PositiveInfinity;
            double maxDiff = double.NegativeInfinity;

            for (int i = 0; i < XArray.Length; i++)
            {
                double diff = Complex.Abs(YArray[i * 2] - YArray[i * 2 + 1]);
                if (diff < minDiff) minDiff = diff;
                if (diff > maxDiff) maxDiff = diff;
            }

            return (minDiff, maxDiff);
        }
    }

    // Redundant override
    // public override string ToString()
    // {
    //     return base.ToString();
    // }

    public override string ToLongString(string format)
    {
        var sb = new StringBuilder($"{ToString()}\n");

        for (int i = 0; i < XArray.Length; i++)
        {
            DataItem item = new DataItem(XArray[i], YArray[i * 2], YArray[i * 2 + 1]);
            sb.AppendLine(item.ToString(format));
        }

        return sb.ToString();
    }
}

// Class V1MainCollection derived from List<V1Data>
public class V1MainCollection : List<V1Data>
{
    public V1Data? this[string key]
    {
        get => Find(data => data.Key == key); // Find быстрее для List
        // get => this.FirstOrDefault(data => data.Key == key);
    }

    public new bool Add(V1Data v1Data)
    {
        if (Exists(data => data.Key == v1Data.Key && data.Date == v1Data.Date)) // Exists быстрее для List
            return false;
        // if (this.Any(data => data.Key == v1Data.Key && data.Date == v1Data.Date))
        //     return false;

        base.Add(v1Data);
        return true;
    }

    public V1MainCollection(int nA, int nL)
    {
        for (int i = 0; i < nA; i++)
        {
            double[] xArray = new[] { i, i + 0.5 };
            V1DataArray dataArray = new($"DataArray_{i}", DateTime.Now, xArray, DataItemFunctions.FValueMethod);
            Add(dataArray);
        }

        for (int i = 0; i < nL; i++)
        {
            double[] xArray = new[] { i + 0.1, i + 0.6 };
            V1DataList dataList = new($"DataList_{i}", DateTime.Now, xArray, DataItemFunctions.FDI_Method);
            Add(dataList);
        }
    }

    public override string ToString()
    {
        var sb = new StringBuilder();
        foreach (V1Data data in this)
        {
            sb.AppendLine(data.ToString());
        }
        return sb.ToString();
    }

    public string ToLongString(string format)
    {
        var sb = new StringBuilder();
        foreach (V1Data data in this)
        {
            sb.AppendLine(data.ToLongString(format));
        }
        return sb.ToString();
    }
}

// Static class with methods matching the delegates
public static class DataItemFunctions
{
    public static void FValueMethod(double x, ref Complex y1, ref Complex y2)
    {
        y1 = new Complex(Math.Cos(x), Math.Sin(x));
        y2 = new Complex(Math.Sin(x), Math.Cos(x));
    }

    public static DataItem FDI_Method(double x)
    {
        Complex y1 = new(Math.Cos(x), Math.Sin(x));
        Complex y2 = new(Math.Sin(x), Math.Cos(x));
        return new DataItem(x, y1, y2);
    }
}

// Program class with Main method
internal static class Program
{
    public const string Format = "bold springgreen3";
    static void Main()
    {
        // 1. Create V1DataList object
        double[] xValues = [0.0, 1.0, 2.0, 3.0];
        V1DataList dataList = new("DataListKey", DateTime.Now, xValues, DataItemFunctions.FDI_Method);
        AnsiConsole.MarkupLine($"[{Format}]V1DataList object:[/]");
        Console.WriteLine(dataList.ToLongString("F2"));

        // Convert to V1DataArray
        V1DataArray dataArrayFromList = (V1DataArray)dataList;
        AnsiConsole.MarkupLine($"[{Format}]V1DataArray object converted from V1DataList:[/]");
        Console.WriteLine(dataArrayFromList.ToLongString("F2"));

        // 2. Create V1DataArray object
        V1DataArray dataArray = new("DataArrayKey", DateTime.Now, xValues, DataItemFunctions.FValueMethod);
        AnsiConsole.MarkupLine($"[{Format}]V1DataArray object:[/]");
        Console.WriteLine(dataArray.ToLongString("F2"));

        // Output indexer values
        AnsiConsole.MarkupLine($"[{Format}]Indexer values for V1DataArray:[/]");
        DataItem? itemAtIndex1 = dataArray[1];
        if (itemAtIndex1.HasValue)
            Console.WriteLine($"Item at index 1: {itemAtIndex1.Value.ToString("F2")}");
        else
            Console.WriteLine("Index 1 out of range");

        DataItem? itemAtIndex10 = dataArray[10];
        if (itemAtIndex10.HasValue)
            Console.WriteLine($"Item at index 10: {itemAtIndex10.Value.ToString("F2")}");
        else
            Console.WriteLine("Index 10 out of range\n");

        // 3. Create V1MainCollection object
        V1MainCollection mainCollection = new(2, 2);
        AnsiConsole.MarkupLine($"[{Format}]V1MainCollection object:[/]");
        Console.WriteLine(mainCollection.ToLongString("F2"));

        // 4. For each element in V1MainCollection, output XLength and MinMaxDifference
        AnsiConsole.MarkupLine($"[{Format}]Properties of elements in V1MainCollection:[/]");
        foreach (var data in mainCollection)
        {
            Console.WriteLine($"xLength: {data.XLength}");
            var (minDiff, maxDiff) = data.MinMaxDifference;
            Console.WriteLine($"Min Difference: {minDiff:F2}, Max Difference: {maxDiff:F2}\n");
        }

        // 5. Output indexer values for V1MainCollection
        AnsiConsole.MarkupLine($"[{Format}]Indexer values for V1MainCollection:[/]");
        V1Data? dataWithKey = mainCollection["DataArray_1"];
        if (dataWithKey != null)
            Console.WriteLine($"Data with Key 'DataArray_1' found: {dataWithKey}\n");
        else
            Console.WriteLine("Data with Key 'DataArray_1' not found\n");

        dataWithKey = mainCollection["NonExistingKey"];
        if (dataWithKey != null)
            Console.WriteLine($"Data with Key 'NonExistingKey' found: {dataWithKey}\n");
        else
            Console.WriteLine("Data with Key 'NonExistingKey' not found\n");
    }
}
