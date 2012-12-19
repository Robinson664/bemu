using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.MarketDataRequest
{
    public class ElementMarketNull : Element
    {
        private readonly string _name;

        internal ElementMarketNull(string name)
        {
            this._name = name;
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return 0; } }
        public override bool IsArray { get { return true; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsNull { get { return true; } }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return new StringBuilder();
        }

    }
}
