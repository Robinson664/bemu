//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/MessageMarketSubscriptionData.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.MarketDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class MessageMarketSubscriptionData : Message
    {
        private readonly Dictionary<string, Element> _fields;
        private readonly string _security;

        internal MessageMarketSubscriptionData(Subscription sub, Dictionary<string, object> fields) : base(new Name("MarketDataEvents"), sub.CorrelationID, null)
        {
            this._fields = new Dictionary<string, Element>();
            foreach (var item in fields)
            {
                Element elm = null;
                if (item.Value is double)
                    elm = new ElementMarketDouble(item.Key, (double)item.Value);

                else if (item.Value is Datetime)
                {
                    Datetime temp = (Datetime)item.Value;
                    switch (temp.DateTimeType)
                    {
                        case Datetime.DateTimeTypeEnum.date:
                            elm = new ElementMarketDate(item.Key, temp.ToSystemDateTime());
                            break;
                        case Datetime.DateTimeTypeEnum.time:
                            elm = new ElementMarketTime(item.Key, temp.ToSystemDateTime());
                            break;
                        case Datetime.DateTimeTypeEnum.both:
                            elm = new ElementMarketDatetime(item.Key, temp.ToSystemDateTime());
                            break;
                    }
                }

                else if (item.Value is int)
                    elm = new ElementMarketInt(item.Key, (int)item.Value);
                else if (item.Value is string)
                    elm = new ElementMarketString(item.Key, (string)item.Value);
                else if (item.Value is bool)
                    elm = new ElementMarketBool(item.Key, (bool)item.Value);

                if (elm != null)
                    this._fields.Add(item.Key.ToUpper(), elm);
            }
            this._security = sub.Security;
        }

        public override string TopicName { get { return this._security; } }
        public override IEnumerable<Element> Elements { get { return this._fields.Values; } }
        public override int NumElements { get { return this._fields.Count; } }

        public override object this[string name, int index]
        {
            get
            {
                if (index == 0)
                    return this[name].GetValue();
                else
                    return base[name, index];
            }
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("{0} = {{{1}", this.MessageType.ToString(), Environment.NewLine);
            foreach (var item in this.Elements)
            {
                result.Append(item.PrettyPrint(1));
            }
            result.AppendLine("}");

            return result.ToString();
        }

    }
}
