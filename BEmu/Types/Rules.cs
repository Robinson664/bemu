using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.Types
{
    internal static class Rules
    {
        public static bool IsSecurityError(string security)
        {
            return security == null || security.StartsWith("Z", StringComparison.OrdinalIgnoreCase);
        }
    }
}
