//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="Types/Extensions.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bloomberglp.Blpapi.Types
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
