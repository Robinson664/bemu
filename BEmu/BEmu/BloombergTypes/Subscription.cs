using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu
{
    public class Subscription
    {
        private readonly string _security;
        internal string Security { get { return this._security; } }

        private readonly List<string> _fields;
        internal List<string> Fields { get { return this._fields; } }

        private readonly CorrelationID _corr;
        public CorrelationID CorrelationID { get { return this._corr; } }

        public Subscription(string security, IList<string> fields)
        {
            this._security = security.ToUpper();
            this._fields = fields.Select(s => s.ToUpper()).ToList();
            this._corr = new CorrelationID();
        }

        public Subscription(string security, IList<string> fields, IList<string> options, CorrelationID correlationID)
        {
            this._security = security.ToUpper();
            this._fields = fields.Select(s => s.ToUpper()).ToList();
            this._corr = correlationID;
        }

    }
}
