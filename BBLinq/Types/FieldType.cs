using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    public class FieldType : FieldTypeParent
    {
        private readonly object _value;

        internal FieldType(string bbKey, string fieldName) : base(bbKey, fieldName)
        {
            this._value = null;
        }

        internal FieldType(string bbKey, string fieldName, object value) : base(bbKey, fieldName)
        {
            this._value = value;
        }

        public object Value { get { return this._value; } }

        public override string ToString()
        {
            return string.Format("{0}, {1} = {2}", base.BBKey, base.FieldName, this._value);
        }
    }
}
