//------------------------------------------------------------------------------
// <copyright project="BEmu" file="Types/RandomDataGenerator.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.Types
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal static class RandomDataGenerator
    {
        private static Random _random = new Random(100);

        public static object ReferenceDataFromFieldName(string fieldName, string security, bool isOption, ReferenceDataRequest.RequestReference rreq)
        {
            string upper = fieldName.ToUpper();
            object result;

            if (upper == "CHAIN_TICKERS")
            {
                if (isOption)
                {
                    result = null;
                }
                else
                {
                    uint numPoints = 1;
                    string dtExp = null;
                    var optionality = ReferenceDataRequest.ElementReferenceArrayChainTickers.OptionalityEnum.call;

                    if (rreq.HasElement("overrides"))
                    {
                        var overrides = rreq["overrides"];
                        for (int i = 0; i < overrides.NumValues; i++)
                        {
                            var element = overrides.GetValueAsElement(i);

                            var fieldId = element["fieldId"].GetValueAsString();
                            var value = element["value"].GetValueAsString();

                            switch (fieldId.ToUpper())
                            {
                                case "CHAIN_POINTS_OVRD":
                                    numPoints = uint.Parse(value);
                                    break;
                                case "CHAIN_EXP_DT_OVRD":
                                    dtExp = value;
                                    break;
                                case "CHAIN_PUT_CALL_TYPE_OVRD":
                                    if (value.ToUpper() == "P")
                                        optionality = ReferenceDataRequest.ElementReferenceArrayChainTickers.OptionalityEnum.put;
                                    break;
                            }
                        }
                    }

                    ReferenceDataRequest.ElementReferenceArrayChainTickers chain = new ReferenceDataRequest.ElementReferenceArrayChainTickers(security, numPoints, dtExp, optionality);
                    result = chain;
                }
            }
            else if (upper.Contains("TICKER"))
            {
                result = security.Substring(0, security.IndexOf(' '));
            }
            else if (upper.Contains("OPT_EXPIRE_DT"))
            {
                if (security.EndsWith("COMDTY") || security.EndsWith("INDEX"))
                {
                    result = DateTime.Today.AddMonths(3);
                }
                else if (isOption)
                {
                    string strDate = security.Substring(security.LastIndexOf(' ') - 15, 6);
                    result = DateTime.ParseExact(strDate, "yyMMdd", null);
                }
                else
                    result = null;
            }
            else if (upper.Contains("TRADEABLE_DT"))
            {
                result = DateTime.Today.AddMonths(3);
            }
            else
            {
                result = RandomDataGenerator.RandomDouble();
            }

            return result;
        }

        public static object MarketDataFromFieldName(string fieldName)
        {
            object result;
            string upper = fieldName.ToUpper();

            if (upper.Contains("TIME"))
                result = new Datetime(DateTime.Now.AddMinutes(-1d * RandomDataGenerator._random.NextDouble() * 100d), Datetime.DateTimeTypeEnum.time);
            else if (upper.Contains("DATE"))
                result = new Datetime(DateTime.Now.AddDays(-1d * RandomDataGenerator._random.NextDouble() * 100d), Datetime.DateTimeTypeEnum.date);
            else
                result = RandomDataGenerator.RandomDouble();

            return result;
        }

        public static TimeSpan IntradayTickInterval()
        {
            return TimeSpan.FromMinutes(RandomDataGenerator._random.Next(1, 30)); //between 1 and 30 minutes
        }

        public static IntradayBarRequest.BarTickDataType GenerateBarData(DateTime date)
        {
            double first = RandomDataGenerator.RandomDouble();
            double second = RandomDataGenerator.RandomDouble();

            double high = Math.Max(first, second);
            double low = Math.Min(first, second);
            double open = RandomDataGenerator.RandomDouble(low, high);
            double close = RandomDataGenerator.RandomDouble(low, high);

            IntradayBarRequest.BarTickDataType result = new IntradayBarRequest.BarTickDataType()
            {
                DtTime = date,
                Volume = RandomDataGenerator.RandomInt(1000000),
                Value = RandomDataGenerator.RandomInt(1000000000),
                NumEvents = RandomDataGenerator.RandomInt(10000),
                High = high,
                Low = low,
                Open = open,
                Close = close
            };
            return result;
        }

        public static Dictionary<string, object> GetMarketDataFields(List<string> requestedFields)
        {
            Dictionary<string, object> result = new Dictionary<string, object>();

            //A market data response contains at least one of the requested fields, but not necessarilly all of them.
            //  The response contains the requested fields that changed.
            while (result.Count == 0)
            {
                for (int i = 0; i < requestedFields.Count; i++)
                {
                    if (RandomDataGenerator._random.NextDouble() < 0.25) //25% chance that a field is included in the response
                        result.Add(requestedFields[i], RandomDataGenerator.MarketDataFromFieldName(requestedFields[i]));
                }
            }

            //Market data responses contain extraneous data fields.  The user will not have requested them.
            //  To make this emulator more realistic, I'll add some extraneous fields of different types below.
            string[] extraDoubleFields = { "PREV_SES_LAST_PRICE", "PREV_CLOSE_VALUE_REALTIME", "PRICE_PREVIOUS_CLOSE_RT", "LOW", "LOW_TDY", "PRICE_LOW_RT" };
            string[] extraIntFields = { "PX_DISPLAY_FMT_MIN_#_DECIMALS_RT", "PX_DISPLAY_FMT_MAX_#_DECIMALS_RT", "NEWS_HEAT_STORY_FLOW_RT", "BID_SIZE_TDY", "BID_SIZE", "ASK_SIZE_TDY" };
            string[] extraTimeFields = { "SES_START", "LAST_UPDATE_BID_RT", "LAST_UPDATE_ASK_RT", "BID_ASK_TIME", "LAST_TRADE_RECEIVED_TIME_RT" };
            string[] extraDateFields = { "PRICE_52_WEEK_HIGH_DATE_RT", "PRICE_52_WEEK_LOW_DATE_RT", "PREV_TRADING_DT_REALTIME", "TRADING_DT_REALTIME" };
            string[] extraDateTimeFields = { "TRADE_UPDATE_STAMP_RT" };
            string[] extraStringFields = { "MKTDATA_EVENT_TYPE", "LAST_PX_LOCAL_EXCH_SOURCE_RT", "CLOSE_LOCAL_SOURCE_RT", "BID_PX_LOCAL_EXCH_SOURCE_RT", "HIGH_LOCAL_SOURCE_RT" };
            string[] extraBoolFields = { "IND_BID_FLAG", "IND_ASK_FLAG", "SHORT_SALE_THRESHOLD_REALTIME", "NO_SHORT_SELL_REALTIME", "RT_EXCH_TRADE_STATUS" };

            foreach (var item in extraDoubleFields) //random double fields
            {
                if (!result.ContainsKey(item))
                    result.Add(item, RandomDataGenerator.RandomDouble());
            }

            foreach (var item in extraIntFields) //random int fields
            {
                if (!result.ContainsKey(item))
                    result.Add(item, RandomDataGenerator.RandomInt(100));
            }

            foreach (var item in extraTimeFields) //random time fields
            {
                if (!result.ContainsKey(item))
                    result.Add(item, RandomDataGenerator.RandomTime());
            }

            foreach (var item in extraDateFields) //random date fields
            {
                if (!result.ContainsKey(item))
                    result.Add(item, RandomDataGenerator.RandomDate());
            }

            foreach (var item in extraDateTimeFields) //random datetime fields
            {
                if (!result.ContainsKey(item))
                    result.Add(item, RandomDataGenerator.RandomDatetime());
            }

            foreach (var item in extraStringFields) //random string fields
            {
                if (!result.ContainsKey(item))
                    result.Add(item, RandomDataGenerator.RandomString());
            }

            foreach (var item in extraBoolFields) //random bool fields
            {
                if (!result.ContainsKey(item))
                    result.Add(item, RandomDataGenerator.RandomBool());
            }

            //simple, inefficient shuffle algorithm
            var resultShuffled = result.OrderBy(b => RandomDataGenerator._random.NextDouble()).ToDictionary(d => d.Key, d => d.Value);

            return resultShuffled;
        }

        /// <summary>
        /// I made it so that there is a 70% chance that a market data event will include a specific security
        /// </summary>
        public static bool ShouldIncludeQuote()
        {
            return RandomDataGenerator._random.NextDouble() < 0.7;
        }

        public static TimeSpan TimeBetweenMarketDataEvents()
        {
            return TimeSpan.FromMilliseconds(RandomDataGenerator._random.NextDouble() * 2000d + 100d);
        }

        public static int IntradayTickTradeSize()
        {
            return RandomDataGenerator.RandomInt(5) * 100;
        }

        public static int Strike()
        {
            return RandomDataGenerator.RandomInt(20) * 5;
        }

        public static double RandomDouble()
        {
            return Math.Round(RandomDataGenerator._random.NextDouble() * 100d, 2);
        }

        public static double RandomDouble(double low, double high)
        {
            return Math.Round(RandomDataGenerator._random.NextDouble() * (high - low) + low, 2);
        }

        public static int RandomInt(uint max)
        {
            return RandomDataGenerator._random.Next(1, (int)max);
        }

        private static Datetime RandomTime()
        {
            return new Datetime(DateTime.Today.AddSeconds(RandomDataGenerator.RandomInt(1000)), Datetime.DateTimeTypeEnum.time);
        }

        private static Datetime RandomDate()
        {
            return new Datetime(DateTime.Today.AddDays(RandomDataGenerator.RandomInt(100)), Datetime.DateTimeTypeEnum.date);
        }

        private static Datetime RandomDatetime()
        {
            return new Datetime(DateTime.Today.AddDays(RandomDataGenerator.RandomInt(100)).AddSeconds(RandomDataGenerator.RandomInt(1000)), Datetime.DateTimeTypeEnum.both);
        }

        private static bool RandomBool()
        {
            return RandomDataGenerator._random.Next(0, 2) == 0;
        }

        private static char RandomChar()
        {
            return (char)('A' + RandomDataGenerator.RandomInt(25) - 1);
        }

        public static string RandomString()
        {
            int length = RandomDataGenerator.RandomInt(10);
            return RandomDataGenerator.RandomString(length);
        }

        public static string RandomString(int length)
        {
            StringBuilder result = new StringBuilder(length);
            for (int i = 0; i < length; i++)
            {
                result.Append(RandomDataGenerator.RandomChar());
            }
            return result.ToString();
        }

    }
}
