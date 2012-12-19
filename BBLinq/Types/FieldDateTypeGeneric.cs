using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    public class FieldDateType<T> : FieldDateTypeParent<T>
    {
        internal FieldDateType(string bbKey, string fieldName, DateTime date) : base(bbKey, fieldName, date)
        {
        }

        internal FieldDateType(string bbKey, string fieldName, T value, DateTime date) : base(bbKey, fieldName, value, date)
        {
        }

        public override string ToString()
        {
            return string.Format("{0:yyyy-MM-dd} - {1}", base.Date, base.ToString());
        }
    }
}
