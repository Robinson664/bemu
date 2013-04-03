//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/MessageMarketSubscriptionStarted.cs" company="Jordan Robinson">
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

    internal class MessageMarketSubscriptionStarted : Message
    {
        private readonly CorrelationID _correlationId;
        private readonly string _topicName;
        private readonly ElementMarketNull _exceptions;

        internal MessageMarketSubscriptionStarted(Subscription sub) : base(new Name("SubscriptionStarted"), sub.CorrelationID, null)
        {
            this._correlationId = sub.CorrelationID;
            this._topicName = sub.Security;
            this._exceptions = new ElementMarketNull("exceptions");
        }

        public override int NumElements { get { return 1; } }
        public override IEnumerable<Element> Elements { get { yield return this._exceptions; } }
        public override Element AsElement { get { return new ElementMarketSubscriptionStarted(this); } }

        public override string TopicName { get { return this._topicName; } }

        public override string ToString()
        {
            return string.Format("SubscriptionStarted = {{{0}}}{0}", Environment.NewLine);
        }
    }
}
