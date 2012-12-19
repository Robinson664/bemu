using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    public abstract class FieldTypeParent
    {
        private readonly string _fieldName;
        private readonly string _bbKey;

        protected FieldTypeParent(string bbKey, string fieldName)
        {
            this._fieldName = fieldName;
            this._bbKey = bbKey;
        }

        public string FieldName { get { return this._fieldName; } }
        public string BBKey { get { return this._bbKey; } }

        public new abstract string ToString();
    }
}
