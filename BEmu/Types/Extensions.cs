using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.Types
{
    internal static class Extensions
    {
        /// <summary>
        /// Pulled straight from http://msdn.microsoft.com/en-us/library/system.string.isnullorwhitespace.aspx
        /// </summary>
        /// <param name="arg"></param>
        /// <returns></returns>
        public static bool IsNullOrWhiteSpace(string arg)
        {
            return String.IsNullOrEmpty(arg) || arg.Trim().Length == 0;
        }
    }
}
