//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="Types/DisplayFormats.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bloomberglp.Blpapi.Types
{
    /// <summary>
    /// For Number formatters, see http://msdn.microsoft.com/en-us/library/dwhawy9k(v=vs.110).aspx
    /// For Date formatters, see http://msdn.microsoft.com/en-us/library/8kb3ddd4(v=vs.110).aspx
    /// </summary>
    internal static class DisplayFormats
    {
        internal static string FormatNumberNoSeparators(double dbl, int numDecimals = 0)
        {
            string formatString = string.Format("f{0}", numDecimals);
            return dbl.ToString(formatString);
        }

        internal static string FormatDate(Datetime date) //default date
        {
            return date.ToSystemDateTime().ToString("yyyy-MM-dd"); //mkt data has time zone information, but the other requests don't
        }

        internal static string FormatTimeZone(Datetime time) //default time
        {
            return time.ToSystemDateTime().ToString("HH:mm:ss.fff%K");
        }

        internal static string FormatDatetimeZone(Datetime datetime) //default datetime
        {
            return datetime.ToSystemDateTime().ToString("yyyy-MM-dd HH:mm:ss.fff%K");
        }

        internal static class MarketDataRequests
        {
            internal static string FormatDateZone(Datetime date) //default date
            {
                return date.ToSystemDateTime().ToString("yyyy-MM-dd%K"); //mkt data has time zone information, but the other requests don't
            }
        }

        internal static class HistoricalOrReferenceRequests
        {
            internal static string FormatDate(Datetime date)
            {
                return date.ToSystemDateTime().ToString("yyyy-MM-dd");
            }

            internal static bool TryParseInput(string str, out DateTime date)
            {
                return DateTime.TryParseExact(str, "yyyyMMdd", System.Globalization.CultureInfo.InvariantCulture, System.Globalization.DateTimeStyles.None, out date);
            }
        }

        internal static class IntradayRequests //IntradayBar, IntradayTick
        {
            internal static string FormatDatetime(Datetime datetime)
            {
                return datetime.ToSystemDateTime().ToString("yyyy-MM-ddTHH:mm:ss.fff");
            }
        }
    }
}
