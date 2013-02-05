using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.Types
{
    internal static class DataGenerator
    {
        private readonly static Random _random = new Random(100);

        public enum FieldDataTypeEnum { price, timeInterval, date, time, strike }

        public static MyType GenerateFieldData<MyType>(FieldDataTypeEnum field)
        {
            switch (field)
            {
                case FieldDataTypeEnum.price:
                    return (MyType)(object)DataGenerator.Price();
                case FieldDataTypeEnum.timeInterval:
                    break;
                case FieldDataTypeEnum.date:
                    break;
                case FieldDataTypeEnum.time:
                    break;
                case FieldDataTypeEnum.strike:
                    return (MyType)(object)DataGenerator.Strike();
                default:
                    throw new NotImplementedException();
            }   
        }

        private static double Price()
        {
            return Math.Round(DataGenerator._random.NextDouble() * 100d, 2);
        }

        private static DateTime Date()
        {
            return DateTime.Now.AddDays(-1d * DataGenerator._random.NextDouble() * 100d);
        }

        private static DateTime Time()
        {
            return DateTime.Now.AddMinutes(-1d * DataGenerator._random.NextDouble() * 100d);
        }

        private static int Strike()
        {
            return DataGenerator._random.Next(1, 20) * 5;
        }

    }
}
