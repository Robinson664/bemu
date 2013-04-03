//------------------------------------------------------------------------------
// <copyright project="BEmu" file="Types/IndentType.cs" company="Jordan Robinson">
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

    public static class IndentType
    {
        public const string TAB = "    "; //four spaces        

        public static string Indent(int count) //this could definitely be optimized, but I'm not building this for performance
        {
            StringBuilder result = new StringBuilder(count * IndentType.TAB.Length);
            for (int i = 0; i < count; i++)
                result.AppendFormat(IndentType.TAB);
            return result.ToString();
        }

    }
}
