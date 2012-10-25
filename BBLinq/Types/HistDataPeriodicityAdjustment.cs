using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    internal static class HistDataPeriodicityAdjustmentType
    {
        public static string Convert(HistDataPeriodicityAdjustment arg)
        {
            switch (arg)
            {
                case HistDataPeriodicityAdjustment.calendar: return "CALENDAR";
                case HistDataPeriodicityAdjustment.fiscal: return "FISCAL";
                case HistDataPeriodicityAdjustment.actual:
                default:
                    return "ACTUAL";
            }
        }
    }

    /// <summary>
    /// Determine the frequency and calendar type of the output. To be used in conjunction with Period Selection.
    /// </summary>
    public enum HistDataPeriodicityAdjustment
    {
        /// <summary>
        /// These revert to the actual date from today (if the end date is left blank) or from the End Date
        /// </summary>
        actual,

        /// <summary>
        /// For pricing fields, these revert to the last business day of the specified calendar period.
        /// </summary>
        calendar,

        /// <summary>
        /// These periods revert to the fiscal period end for the company
        /// </summary>
        fiscal
    }
}
