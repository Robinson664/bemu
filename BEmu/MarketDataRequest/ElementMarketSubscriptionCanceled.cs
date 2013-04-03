//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/ElementMarketSubscriptionCanceled.cs" company="Jordan Robinson">
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
