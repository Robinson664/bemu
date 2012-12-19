using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.HistoricalDataRequest
{
    public class ElementHistoricString : Element
    {
        private readonly string _value;
        private readonly string _name;

        internal ElementHistoricString(string name, string value)
        {
            this._name = name;
            this._value = value;
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return false; } }

        public override object this[int index]
        {
            get
            {
                if (index == 0)
                    return this._value;
                else
                    return base[index];
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return base.PrettyPrintHelper(tabIndent, this._value.ToString());
        }

        public override object GetValue()
        {
            return this._value;
        }

        public override string GetValueAsString()
        {
            return this._value;
        }
                
    }
}
