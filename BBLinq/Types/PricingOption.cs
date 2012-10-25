using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    internal static class PricingOptionType
    {
        public static string Convert(PricingOption arg)
        {
            switch (arg)
            {
                case PricingOption.yield: return "PRICING_OPTION_YIELD";
                case PricingOption.price:
                default:
                    return "PRICING_OPTION_PRICE";
            }
        }
    }

    /// <summary>
    /// Sets quote to Price or Yield for a debt instrument whose default value is quoted in yield (depending on pricing source).
    /// </summary>
    public enum PricingOption
    {
        /// <summary>
        /// Set quote to price
        /// </summary>
        price,

        /// <summary>
        /// Set quote to yield
        /// </summary>
        yield
    }
}
