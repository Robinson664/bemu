using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.MarketDataRequest
{
    internal class ElementMarketSubscriptionCanceled : Element
    {
        private readonly ElementMarketSubscriptionCancelReason _reason;

        internal ElementMarketSubscriptionCanceled(MessageMarketSubscriptionCanceled arg)
        {
            this._reason = (ElementMarketSubscriptionCancelReason)arg["reason"];
        }

        public override Name Name { get { return new Name("SubscriptionTerminated"); } }

        public override int NumElements { get { return 1; } }
        public override int NumValues { get { return 1; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsNull { get { return false; } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._reason;
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{2} = {{{1}", tabs, Environment.NewLine, this.Name.ToString());
            result.Append(this._reason.PrettyPrint(tabIndent + 1));            
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }

    }
}
