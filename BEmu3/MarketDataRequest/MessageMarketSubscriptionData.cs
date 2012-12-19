using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.MarketDataRequest
{
    public class MessageMarketSubscriptionData : Message
    {
        private readonly Dictionary<string, Element> _fields;
        private readonly string _security;

        internal MessageMarketSubscriptionData(Subscription sub, Dictionary<string, object> fields) : base(new Name("MarketDataEvents"), sub.CorrelationID)
        {
            this._fields = new Dictionary<string, Element>();
            foreach (var item in fields)
            {
                Element elm = null;
                if (item.Value is double)
                    elm = new ElementMarketDouble(item.Key, (double)item.Value);
                else if (item.Value is Types.TimeType)
                    elm = new ElementMarketTime(item.Key, ((Types.TimeType)item.Value).Time);
                else if (item.Value is Types.DateType)
                    elm = new ElementMarketDate(item.Key, ((Types.DateType)item.Value).Date);

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
