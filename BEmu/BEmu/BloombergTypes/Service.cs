using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu
{
    public abstract class Service
    {
        public abstract Request CreateRequest(string operationName);
        public abstract string Name { get; }
    }
}
