//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/MessageMarketSubscriptionCanceled.cs" company="Jordan Robinson">
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

    internal class MessageMarketSubscriptionCanceled : Message
    {
        private readonly string _topicName;
        private readonly ElementMarketSubscriptionCancelReason _reason;

        internal MessageMarketSubscriptionCanceled(Subscription sub) : base(new Name("SubscriptionTerminated"), sub.CorrelationID, null)
        {
            this._topicName = sub.Security;
            this._reason = new ElementMarketSubscriptionCancelReason();
        }

        public override int NumElements { get { return 1; } }
        public override IEnumerable<Element> Elements { get { yield return this._reason; } }
        public override string TopicName { get { return this._topicName; } }

        public override object this[string name, int index] { get { return null; } }
        
        public override Element AsElement
        {
            get
            {
                return base.AsElement;
            }
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("{0} = {{{1}", this.MessageType.ToString(), Environment.NewLine);
            result.Append(this._reason.PrettyPrint(1));
            result.AppendLine("}");

            return result.ToString();
        }
    }
}
