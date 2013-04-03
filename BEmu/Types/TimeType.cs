//------------------------------------------------------------------------------
// <copyright project="BEmu" file="Types/TimeType.cs" company="Jordan Robinson">
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

    internal class TimeType
    {
        public DateTime Time { get; set; }
        public TimeType(DateTime time)
        {
            this.Time = time;
        }
    }
}
