using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    internal static class HistDataPeriodicityType
    {
        public static string Convert(HistDataPeriodicity arg)
        {
            switch (arg)
            {
                case HistDataPeriodicity.weekly: return "WEEKLY";
                case HistDataPeriodicity.monthly: return "MONTHLY";
                case HistDataPeriodicity.quarterly: return "QUARTERLY";
                case HistDataPeriodicity.semi_annually: return "SEMI_ANNUALLY";
                case HistDataPeriodicity.yearly: return "YEARLY";
                case HistDataPeriodicity.daily:
                default:
                    return "DAILY";
            }
        }
    }

    /// <summary>
    /// Determine the frequency of the output. To be used in conjunction with Period Adjustment.
    /// </summary>
    public enum HistDataPeriodicity
    {
        /// <summary>
        /// Returns one data point per day
        /// </summary>
        daily,

        /// <summary>
        /// Returns one data point per week
        /// </summary>
        weekly,

        /// <summary>
        /// Returns one data point per month
        /// </summary>
        monthly,

        /// <summary>
        /// Returns one data point per quarter
        /// </summary>
        quarterly,

        /// <summary>
        /// Returns one data point per half year
        /// </summary>
        semi_annually,

        /// <summary>
        /// Returns one data point per year
        /// </summary>
        yearly
    }
}
