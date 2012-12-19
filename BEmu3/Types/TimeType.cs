using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.Types
{
    internal class TimeType
    {
        public DateTime Time { get; set; }
        public TimeType(DateTime time)
        {
            this.Time = time;
        }
    }
}
