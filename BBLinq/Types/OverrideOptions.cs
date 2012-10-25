using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    internal static class OverrideOptionsType
    {
        public static string Convert(OverrideOptions arg)
        {
            switch (arg)
            {
                case OverrideOptions.averagePrice: return "OVERRIDE_OPTION_GPA";
                case OverrideOptions.closingPrice:
                default:
                    return "OVERRIDE_OPTION_CLOSE";
            }
        }
    }

    /// <summary>
    /// Indicates whether to use the average or the closing price in quote calculation.
    /// </summary>
    public enum OverrideOptions
    {
        /// <summary>
        /// Use the closing price in quote calculation (OVERRIDE_OPTION_CLOSE)
        /// </summary>
        closingPrice,

        /// <summary>
        /// Use the average price in quote calculation (OVERRIDE_OPTION_GPA)
        /// </summary>
        averagePrice
    }
}
