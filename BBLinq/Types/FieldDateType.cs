using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    public class FieldDateType : FieldType
    {
        private readonly DateTime _date;

        public FieldDateType(string bbKey, string fieldName, DateTime date)
            : base(bbKey, fieldName)
        {
            this._date = date;
        }

        public FieldDateType(string bbKey, string fieldName, object value, DateTime date)
            : base(bbKey, fieldName, value)
        {
            this._date = date;
        }

        public DateTime Date { get { return this._date; } }
    }
}
