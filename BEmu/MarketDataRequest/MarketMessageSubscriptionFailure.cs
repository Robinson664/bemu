//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="MarketDataRequest/MarketMessageSubscriptionFailure.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------


namespace Bloomberglp.Blpapi.MarketDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class MarketMessageSubscriptionFailure : Message
    {
        private readonly CorrelationID _correlationId;
        private readonly string _topicName;
        private readonly MarketElementReason _reason;

        internal MarketMessageSubscriptionFailure(Subscription sub) : base(new Name("SubscriptionFailure"), sub.CorrelationID, null)
        {
            this._correlationId = sub.CorrelationID;
            this._topicName = sub.Security;
            this._reason = new MarketElementReason(MarketElementReason.ReasonTypeEnum.badSecurity);
        }

        public override int NumElements { get { return 1; } }
        public override IEnumerable<Element> Elements { get { yield return this._reason; } }
        //public override Element AsElement { get { return new ElementMarketSubscriptionStarted(this); } }

        public override string TopicName { get { return this._topicName; } }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendLine("SubscriptionFailure = {");
            result.Append(this._reason.PrettyPrint(1).ToString());
            result.AppendLine("}");
            return result.ToString();
        }
    }
}
