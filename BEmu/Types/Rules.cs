//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="Types/Rules.cs" company="Jordan Robinson">
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
    internal static class Rules
    {
        public static bool IsSecurityError(string security)
        {
            return security == null || security.StartsWith("Z", StringComparison.OrdinalIgnoreCase);
        }

        public static bool IsBadField(string field)
        {
            return field == null || field.StartsWith("Z", StringComparison.OrdinalIgnoreCase);
        }
    }
}
