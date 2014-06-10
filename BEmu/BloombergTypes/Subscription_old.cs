//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/Subscription.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

//namespace Bloomberglp.Blpapi
//{
//    using System;
//    using System.Collections.Generic;
//    using System.Linq;
//    using System.Text;

//    public class Subscription
//    {
//        private readonly string _security;
//        internal string Security { get { return this._security; } }

//        private readonly List<string> _fields;
//        internal List<string> Fields { get { return this._fields; } }

//        private readonly CorrelationID _corr;
//        public CorrelationID CorrelationID { get { return this._corr; } }

//        private readonly int? _conflationInterval;
//        internal int? ConflationInterval { get { return this._conflationInterval; } }

//        public Subscription(string security, string fields)
//        {
//            this._security = Subscription.CheckSecurity(security);
//            this._fields = new List<string>(fields.Split(',').Select(s => Subscription.CheckField(s)));
//            this._corr = null;
//            this._conflationInterval = null;
//        }

//        public Subscription(string security, string fields, string options) : this(security, fields)
//        {
//            this._conflationInterval = this.ReadConflationInterval(new List<string>(options.Split(',')));
//        }

//        public Subscription(string security, string fields, CorrelationID correlationID) : this(security, fields)
//        {
//            this._corr = correlationID;
//        }

//        public Subscription(string security, string fields, string options, CorrelationID correlationID) : this(security, fields, options)
//        {
//            this._corr = correlationID;
//        }

//        public Subscription(string subscriptionString)
//        {
//            this._security = Subscription.ParseSubscriptionStringSecurity(subscriptionString);
//            this._fields = new List<string>(Subscription.ParseSubscriptionStringFields(subscriptionString).Split(',').Select(s => Subscription.CheckField(s)));
//            this._corr = new CorrelationID();

//            string strOptions = Subscription.ParseSubscriptionStringOptions(subscriptionString);
//            if (!Types.Extensions.IsNullOrWhiteSpace(strOptions))
//                this._conflationInterval = this.ReadConflationInterval(strOptions.Split(',').ToList());
//        }

//        public Subscription(string subscriptionString, CorrelationID correlationID) : this(subscriptionString)
//        {
//            this._corr = correlationID;
//        }

//        public Subscription(string security, IList<string> fields)
//        {
//            this._security = Subscription.CheckSecurity(security);
//            this._fields = new List<string>(fields.Select(s => Subscription.CheckField(s)));
//            this._corr = new CorrelationID();
//            this._conflationInterval = null;
//        }

//        public Subscription(string security, IList<string> fields, IList<string> options) : this(security, fields)
//        {
//            this._conflationInterval = this.ReadConflationInterval(options);
//        }

//        public Subscription(string security, IList<string> fields, IList<string> options, CorrelationID correlationID) : this(security, fields, options)
//        {
//            this._corr = correlationID;
//        }

//        public Subscription(string security, IList<string> fields, CorrelationID correlationID) : this(security, fields)
//        {
//            this._corr = correlationID;
//        }

//        private static string CheckSecurity(string security)
//        {
//            if (security.Contains('?'))
//                throw new ArgumentNullException(security);
//            return security;
//        }

//        private static string CheckField(string field)
//        {
//            if (field.Contains('&'))
//                throw new ArgumentException(field);
//            return field;
//        }

//        private int? ReadConflationInterval(IList<string> options)
//        {
//            int? result = null;
//            foreach (var item in options)
//            {
//                if (item.StartsWith("interval="))
//                {
//                    int temp;
//                    string strInterval = item.Substring(item.IndexOf('=') + 1);
//                    if (int.TryParse(strInterval, out temp))
//                        result = temp;
//                }
//            }
//            return result;
//        }

//        private static string ParseSubscriptionStringSecurity(string str)
//        {
//            int qIndex = str.IndexOf('?');

//            if (qIndex >= 0)
//                return Subscription.CheckSecurity(str.Substring(0, qIndex));

//            else
//                return Subscription.CheckSecurity(str);
//        }

//        private static string ParseSubscriptionStringFields(string str)
//        {
//            int fIndex = str.IndexOf("?fields=", StringComparison.OrdinalIgnoreCase);
//            if (fIndex >= 0)
//            {
//                string str2 = str.Substring(fIndex + 8);
//                int aIndex = str2.IndexOf('&');
//                if (aIndex >= 0)
//                {
//                    return str2.Substring(0, aIndex);
//                }
//                else
//                {
//                    return str2;
//                }
//            }
//            else
//                return "";
//        }

//        private static string ParseSubscriptionStringOptions(string str)
//        {
//            int aIndex = str.IndexOf('&');

//            if (aIndex >= 0)
//                return Subscription.CheckSecurity(str.Substring(aIndex + 1));

//            else
//                return "";
//        }

//        public override string ToString()
//        {
//            StringBuilder strb = new StringBuilder();
//            strb.Append(this._security);

//            if (this._fields.Any())
//            {
//                strb.Append("?");
//                for (int i = 0; i < this._fields.Count; i++)
//                {
//                    strb.Append(this._fields[i]);
//                    if (i < this._fields.Count - 1)
//                        strb.Append(",");
//                }
//            }

//            if (this._conflationInterval != null)
//            {
//                strb.AppendFormat("interval={0}", this._conflationInterval.Value);
//            }

//            return strb.ToString();
//        }

//        public override bool Equals(object obj)
//        {
//            if (obj == null)
//                return false;

//            var other = obj as Subscription;
//            if (other == null)
//                return false;

//            else
//                return object.ReferenceEquals(this, obj);
//        }

//    }
//}
