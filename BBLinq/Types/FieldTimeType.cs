using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BBLinq.Types
{
    public class FieldTimeType : FieldDateTypeParent
    {
        internal FieldTimeType(string bbKey, string fieldName, DateTime date) : base(bbKey, fieldName, date)
        {
        }

        internal FieldTimeType(string bbKey, string fieldName, object value, DateTime date) : base(bbKey, fieldName, value, date)
        {
        }

        public override string ToString()
        {
            return string.Format("{0:h:mm:ss} - {1}", base.Date, base.ToString());
        }
    }
}
