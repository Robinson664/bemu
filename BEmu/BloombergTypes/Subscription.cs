//------------------------------------------------------------------------------
// <copyright project="BEmu" file="BloombergTypes/Subscription.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    public class Subscription
    {
        private readonly string _security;
        internal string Security { get { return this._security; } }

        private readonly List<string> _fields;
        internal List<string> Fields { get { return this._fields; } }

        private readonly CorrelationID _corr;
        public CorrelationID CorrelationID { get { return this._corr; } }

        private readonly int? _conflationInterval;
        internal int? ConflationInterval { get { return this._conflationInterval; } }

        public Subscription(string security, IList<string> fields)
        {
            this._security = security.ToUpper();
            this._fields = fields.Select(s => s.ToUpper()).ToList();
            this._corr = new CorrelationID();
            this._conflationInterval = null;
        }

        public Subscription(string security, IList<string> fields, IList<string> options)
        {
            this._security = security.ToUpper();
            this._fields = fields.Select(s => s.ToUpper()).ToList();
            this._corr = new CorrelationID();
            this._conflationInterval = this.ReadConflationInterval(options);
        }

        public Subscription(string security, string field, CorrelationID correlationID)
        {
            this._security = security.ToUpper();
            this._fields = new List<string>();
            this._fields.Add(field);
            this._corr = correlationID;
            this._conflationInterval = null;
        }

        public Subscription(string security, IList<string> fields, IList<string> options, CorrelationID correlationID)
        {
            this._security = security.ToUpper();
            this._fields = fields.Select(s => s.ToUpper()).ToList();
            this._corr = correlationID;
            this._conflationInterval = this.ReadConflationInterval(options);
        }

        private int? ReadConflationInterval(IList<string> options)
        {
            int? result = null;
            foreach (var item in options)
            {
                string str = item.ToLower();
                if (str.StartsWith("interval="))
                {
                    int temp;
                    string strInterval = str.Substring(str.IndexOf('=') + 1);
                    if (int.TryParse(strInterval, out temp))
                        result = temp;
                }
            }
            return result;
        }

    }
}
