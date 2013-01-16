using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.Types
{
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
