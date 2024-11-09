using System.Collections;
using System.Numerics;
using System.Text;

namespace Lab2;

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

    public readonly override string ToString() =>
        ToString("F2");

    public readonly string ToString(string format) =>
        $"X: {X.ToString(format)}, Y1: {Y1.ToString(format)}, Y2: {Y2.ToString(format)}";
}

// Abstract base class V1Data
public abstract class V1Data : IEnumerable<DataItem>
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
    public abstract IEnumerator<DataItem> GetEnumerator();

    IEnumerator IEnumerable.GetEnumerator() =>
        GetEnumerator();

    public override string ToString() =>
        $"Type: {GetType().Name}, Key: {Key}, Date: {Date}";
}

// Class V1DataList derived from V1Data
public class V1DataList : V1Data
{
    public List<DataItem> DataItems { get; set; }

    public V1DataList(string key, DateTime date) : base(key, date) =>
        DataItems = new List<DataItem>();

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

            double minDiff = Double.PositiveInfinity;
            double maxDiff = Double.NegativeInfinity;

            foreach (DataItem item in DataItems)
            {
                double diff = Complex.Abs(item.Y1 - item.Y2);
                if (diff < minDiff)
                    minDiff = diff;
                if (diff > maxDiff)
                    maxDiff = diff;
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

        V1DataArray result = new(source.Key, source.Date);
        result.XArray = xArray;
        result.YArray = yArray;

        return result;
    }

    public override string ToString() =>
        base.ToString() + $", Number of elements: {DataItems.Count}";

    public override string ToLongString(string format)
    {
        StringBuilder sb = new(ToString() + "\n");
        foreach (DataItem item in DataItems)
            sb.AppendLine(item.ToString(format));
        return sb.ToString();
    }

    public override IEnumerator<DataItem> GetEnumerator() =>
        DataItems.GetEnumerator();
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

    public DataItem? this[int index] =>
        index >= 0 && index < XArray.Length
            ? new DataItem(XArray[index], YArray[index * 2], YArray[index * 2 + 1])
            : null;

    public override int XLength => XArray.Length;

    public override (double, double) MinMaxDifference
    {
        get
        {
            if (XArray.Length == 0)
                return (0.0, 0.0);

            double minDiff = Double.PositiveInfinity;
            double maxDiff = Double.NegativeInfinity;

            for (int i = 0; i < XArray.Length; i++)
            {
                double diff = Complex.Abs(YArray[i * 2] - YArray[i * 2 + 1]);
                if (diff < minDiff)
                    minDiff = diff;
                if (diff > maxDiff)
                    maxDiff = diff;
            }

            return (minDiff, maxDiff);
        }
    }

    public override string ToLongString(string format)
    {
        StringBuilder sb = new($"{ToString()}\n");

        for (int i = 0; i < XArray.Length; i++)
        {
            DataItem item = new(XArray[i], YArray[i * 2], YArray[i * 2 + 1]);
            sb.AppendLine(item.ToString(format));
        }

        return sb.ToString();
    }

    public override IEnumerator<DataItem> GetEnumerator()
    {
        for (int i = 0; i < XArray.Length; i++)
            yield return new DataItem(XArray[i], YArray[i * 2], YArray[i * 2 + 1]);
    }

    public bool Save(string filename)
    {
        try
        {
            using BinaryWriter bw = new(File.Open(filename, FileMode.Create));
            // Save base class data
            bw.Write(Key);
            bw.Write(Date.ToBinary());

            // Save XArray length and elements
            bw.Write(XArray.Length);
            foreach (double x in XArray)
                bw.Write(x);

            // Save YArray length and elements
            bw.Write(YArray.Length);
            foreach (Complex y in YArray)
            {
                bw.Write(y.Real);
                bw.Write(y.Imaginary);
            }

            return true;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error saving V1DataArray to file {filename}: {ex.Message}");
            return false;
        }
    }

    public static bool Load(string filename, ref V1DataArray? v1DataArray)
    {
        try
        {
            using BinaryReader br = new(File.Open(filename, FileMode.Open));
            string key = br.ReadString();
            long dateData = br.ReadInt64();
            DateTime date = DateTime.FromBinary(dateData);

            // Read XArray
            int xArrayLength = br.ReadInt32();
            double[] xArray = new double[xArrayLength];
            for (int i = 0; i < xArrayLength; i++)
                xArray[i] = br.ReadDouble();

            // Read YArray
            int yArrayLength = br.ReadInt32();
            Complex[] yArray = new Complex[yArrayLength];
            for (int i = 0; i < yArrayLength; i++)
            {
                double real = br.ReadDouble();
                double imaginary = br.ReadDouble();
                yArray[i] = new Complex(real, imaginary);
            }

            v1DataArray = new V1DataArray(key, date)
            {
                XArray = xArray,
                YArray = yArray
            };

            return true;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error loading V1DataArray from file {filename}: {ex.Message}");
            return false;
        }
    }
}

// Class V1MainCollection derived from List<V1Data>
public class V1MainCollection : List<V1Data>, IEnumerable<DataItem>
{
    public V1Data? this[string key] => Find(data => data.Key == key);

    public new bool Add(V1Data v1Data)
    {
        if (Exists(data => data.Key == v1Data.Key && data.Date == v1Data.Date))
            return false;

        base.Add(v1Data);
        return true;
    }

    public V1MainCollection(int nA, int nL)
    {
        for (int i = 0; i < nA; i++)
        {
            double[] xArray = { i, i + 0.5 };
            V1DataArray dataArray = new($"DataArray_{i}", DateTime.Now, xArray, DataItemFunctions.FValueMethod);
            Add(dataArray);
        }

        for (int i = 0; i < nL; i++)
        {
            double[] xArray = { i + 0.1, i + 0.6 };
            V1DataList dataList = new($"DataList_{i}", DateTime.Now, xArray, DataItemFunctions.FDI_Method);
            Add(dataList);
        }
    }

    public V1MainCollection()
    {
        // Add one V1DataArray
        double[] xArray = { 0.0, 0.5, 1.0 };
        V1DataArray dataArray = new("DataArrayKey", DateTime.Now, xArray, DataItemFunctions.FValueMethod);
        Add(dataArray);

        // Add one V1DataList
        double[] xValues = { 0.0, 0.25, 0.5, 0.75, 1.0 };
        V1DataList dataList = new("DataListKey", DateTime.Now, xValues, DataItemFunctions.FDI_Method);
        Add(dataList);
    }

    public override string ToString()
    {
        StringBuilder sb = new();
        foreach (V1Data data in this)
            sb.AppendLine(data.ToString());
        return sb.ToString();
    }

    public string ToLongString(string format)
    {
        StringBuilder sb = new();
        foreach (V1Data data in this)
            sb.AppendLine(data.ToLongString(format));
        return sb.ToString();
    }

    IEnumerator<DataItem> IEnumerable<DataItem>.GetEnumerator()
    {
        foreach (V1Data v1Data in this)
        {
            foreach (DataItem dataItem in v1Data)
                yield return dataItem;
        }
    }

    IEnumerator IEnumerable.GetEnumerator() =>
        GetEnumerator();

    public double MaxAbsY1
    {
        get
        {
            List<DataItem> dataItems = this.SelectMany<V1Data, DataItem>(v1Data => v1Data).ToList();
            return dataItems.Count != 0
                ? dataItems.Max(dataItem => dataItem.Y1.Magnitude)
                : -1;
        }
    }

    // LINQ property for X coordinates in multiple datasets
    public IEnumerable<double>? XCoordinatesInMultipleDatasets
    {
        get
        {
            IEnumerable<V1Data> v1DataCollection = this;

            if (!v1DataCollection.Any())
                return null;

            var xCoordinatesPerData = v1DataCollection.Select((v1Data, index) => new
            {
                Index = index,
                XCoords = v1Data.Select(dataItem => dataItem.X).Distinct()
            });

            var xWithDataIndex = xCoordinatesPerData
                .SelectMany(item => item.XCoords.Select(x => new
                {
                    X = x,
                    DataIndex = item.Index
                }));

            var xGrouped = xWithDataIndex
                .GroupBy(item => item.X)
                .Select(g => new
                {
                    X = g.Key,
                    DataCount = g.Select(item => item.DataIndex).Distinct().Count()
                });

            List<double> xValues = xGrouped
                .Where(g => g.DataCount >= 2)
                .Select(g => g.X)
                .OrderBy(x => x)
                .ToList();

            return xValues.Count != 0 ? xValues : null;
        }
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
    public const string Format = "F2";

    private static void Main()
    {
        Console.WriteLine("Testing Save and Load methods:");
        TestSaveLoad();

        Console.WriteLine("\nTesting LINQ Queries and IEnumerable<DataItem>:");
        TestLINQQueries();
    }

    private static void TestSaveLoad()
    {
        V1DataArray dataArray = new("TestKey", DateTime.Now, new[] { 1.0, 2.0, 3.0 }, DataItemFunctions.FValueMethod);

        Console.WriteLine("Original V1DataArray:");
        Console.WriteLine(dataArray.ToLongString(Format));

        const string filename = "v1dataarray.dat";
        if (dataArray.Save(filename))
            Console.WriteLine($"Saved V1DataArray to file {filename}");

        V1DataArray? loadedDataArray = null;

        if (!V1DataArray.Load(filename, ref loadedDataArray))
            return;

        Console.WriteLine($"Loaded V1DataArray from file {filename}");
        Console.WriteLine("Loaded V1DataArray:");
        Console.WriteLine(loadedDataArray!.ToLongString(Format));
    }

    private static void TestLINQQueries()
    {
        V1MainCollection mainCollection = new();

        // Add elements to the collection
        // Add V1DataList with empty DataItems
        V1DataList emptyDataList = new("EmptyDataList", DateTime.Now);
        mainCollection.Add(emptyDataList);

        // Add V1DataArray with zero grid nodes
        V1DataArray emptyDataArray = new("EmptyDataArray", DateTime.Now);
        mainCollection.Add(emptyDataArray);

        // Add other elements to test LINQ queries
        // First V1DataArray
        V1DataArray dataArray1 = new("DataArray1", DateTime.Now, new[] { 1.0, 2.0, 3.0 }, DataItemFunctions.FValueMethod);
        mainCollection.Add(dataArray1);

        // Second V1DataArray
        V1DataArray dataArray2 = new("DataArray2", DateTime.Now, new[] { 2.0, 3.0, 4.0 }, DataItemFunctions.FValueMethod);
        mainCollection.Add(dataArray2);

        // V1DataList with DataItems
        V1DataList dataList = new("DataList1", DateTime.Now, new[] { 3.0, 4.0, 5.0 }, DataItemFunctions.FDI_Method);
        mainCollection.Add(dataList);

        Console.WriteLine("V1MainCollection contents:");
        Console.WriteLine(mainCollection.ToLongString("F2"));

        Console.WriteLine("V1MainCollection as DataItems:");
        foreach (V1Data dataItem in mainCollection)
            Console.WriteLine(dataItem.ToString());

        // Call properties with LINQ queries
        Console.WriteLine("\nLINQ Query Results:");

        Console.WriteLine("Maximum modulus of Y1:");
        Console.WriteLine(mainCollection.MaxAbsY1);

        Console.WriteLine("X coordinates occurring in at least two datasets:");
        IEnumerable<double>? xCoords = mainCollection.XCoordinatesInMultipleDatasets;
        if (xCoords != null)
        {
            foreach (double x in xCoords)
                Console.WriteLine(x);
        }
        else
            Console.WriteLine("No x coordinates occurring in at least two datasets.");
    }
}
