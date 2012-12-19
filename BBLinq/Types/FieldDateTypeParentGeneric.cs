using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    public abstract class FieldDateTypeParent<T> : FieldType<T>
    {
        private readonly DateTime _date;

        protected FieldDateTypeParent(string bbKey, string fieldName, DateTime date) : base(bbKey, fieldName)
        {
            this._date = date;
        }

        protected FieldDateTypeParent(string bbKey, string fieldName, T value, DateTime date) : base(bbKey, fieldName, value)
        {
            this._date = date;
        }

        public DateTime Date { get { return this._date; } }
    }
}
