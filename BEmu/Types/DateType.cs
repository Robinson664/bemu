using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.Types
{
    internal class DateType
    {
        public DateTime Date { get; set; }
        public DateType(DateTime date)
        {
            this.Date = date;
        }
    }
}
