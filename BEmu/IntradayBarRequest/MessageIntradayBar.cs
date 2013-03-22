using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.IntradayBarRequest
{
    internal class MessageIntradayBar : Message
    {
        private readonly ElementBarData _parent;

        internal MessageIntradayBar(CorrelationID corr, IEnumerable<BarTickDataType> bars, Service service) :
            base(new Name("IntradayBarResponse"), corr, service)
        {
            this._parent = new ElementBarData(bars);
        }

        public override IEnumerable<Element> Elements { get { yield return this._parent; } }
        public override object this[string name, int index] { get { return null; } }
        public override string TopicName { get { return ""; } }
        public override int NumElements { get { return 1; } }

        //public override Element AsElement { get { return new ElementReference(this); } }
        

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.Append("IntradayBarResponse (choice) = {" + Environment.NewLine);
            result.Append(this._parent.PrettyPrint(1));
            result.Append("}");

            return result.ToString();
        }
    }
}
