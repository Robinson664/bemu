using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BBLinq;

namespace SimpleTest
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] bbKeys = { "CMG US EQUITY", "SPY US EQUITY" };
            string[] fields = { "BID", "ASK" };

            bbKeys.BBMktData(fields, ftypes =>
                {
                    foreach (var item in ftypes.Where(w => fields.Contains(w.FieldName)))
                    {
                        Console.WriteLine(string.Format("{0}, {1:h:mm:ss}, {2} = {3}", item.BBKey, item.Date, item.FieldName, item.Value));
                    }
                });

            Console.ReadLine();
        }
    }
}
