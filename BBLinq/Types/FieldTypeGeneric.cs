using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    public class FieldType<T> : FieldTypeParent
    {
        private readonly T _value;

        internal FieldType(string bbKey, string fieldName) : base(bbKey, fieldName)
        {
            this._value = default(T);
        }

        internal FieldType(string bbKey, string fieldName, T value) : base(bbKey, fieldName)
        {
            this._value = value;
        }

        public T Value { get { return this._value; } }

        public override string ToString()
        {
            return string.Format("{0}, {1} = {2}", base.BBKey, base.FieldName, this._value);
        }        
    }
}
