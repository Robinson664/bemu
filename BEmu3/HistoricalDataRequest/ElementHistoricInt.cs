using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.HistoricalDataRequest
{
    public class ElementReferenceInt : Element
    {
        private readonly int _value;
        private readonly string _name;

        internal ElementReferenceInt(string name, int value)
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

        public override int GetValueAsInt32()
        {
            return this._value;
        }

        public override long GetValueAsInt64()
        {
            return (long)this._value;
        }

        public override float GetValueAsFloat32()
        {
            return (float)this._value;
        }

        public override double GetValueAsFloat64()
        {
            return (double)this._value;
        }

        public override string GetValueAsString()
        {
            return this._value.ToString();
        }
                
    }
}
