using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.ReferenceDataRequest
{
    public class ElementReferenceDateTime : Element
    {
        private readonly Datetime _value;
        private readonly string _name;

        internal ElementReferenceDateTime(string name, DateTime value)
        {
            this._name = name;
            this._value = new Datetime(value, Datetime.DateTimeTypeEnum.both);
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return base.IsComplexType; } }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return base.PrettyPrintHelper(tabIndent, this._value.ToString());
        }

        public override object GetValue()
        {
            return this._value;
        }

        public override Datetime GetValueAsDate()
        {
            return this._value;
        }

        public override Datetime GetValueAsDatetime()
        {
            return this._value;
        }

        public override Datetime GetValueAsTime()
        {
            return this._value;
        }

    }
}
