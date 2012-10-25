using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    public class FieldType
    {
        private readonly object _value;
        private readonly string _fieldName;
        private readonly string _bbKey;

        public FieldType(string bbKey, string fieldName)
        {
            this._value = null;
            this._fieldName = fieldName;
            this._bbKey = bbKey;
        }

        public FieldType(string bbKey, string fieldName, object value)
        {
            this._value = value;
            this._fieldName = fieldName;
            this._bbKey = bbKey;
        }

        public string FieldName { get { return this._fieldName; } }
        public string BBKey { get { return this._bbKey; } }
        public object Value { get { return this._value; } }
    }
}
