using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    internal static class NextCorrelationId
    {
        private static uint _nextCorrelationId = 0;

        public static uint Get()
        {
            return ++NextCorrelationId._nextCorrelationId;
        }
    }
}
