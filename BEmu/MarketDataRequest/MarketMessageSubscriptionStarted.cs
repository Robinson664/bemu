//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="MarketDataRequest/MarketMessageSubscriptionStarted.cs" company="Jordan Robinson">
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

    internal class MarketMessageSubscriptionStarted : Message
    {
        private readonly CorrelationID _correlationId;
        private readonly string _topicName;
        private readonly MarketElementNull _exceptionsNull;
        private readonly MarketElementExceptionsArray _exceptionsBadFields;

        internal MarketMessageSubscriptionStarted(Subscription sub) : base(new Name("SubscriptionStarted"), sub.CorrelationID, null)
        {
            this._correlationId = sub.CorrelationID;
            this._topicName = sub.Security;

            { //deal with bad fields
                List<string> badFields = new List<string>(sub.Fields.Count);
                for (int i = sub.Fields.Count - 1; i >= 0; i--)
                {
                    if (Types.Rules.IsBadField(sub.Fields[i]))
                    {
                        badFields.Add(sub.Fields[i]);
                        sub.Fields.RemoveAt(i);
                    }
                }

                if (badFields.Count == 0)
                    this._exceptionsNull = new MarketElementNull("exceptions");
                else
                    this._exceptionsBadFields = new MarketElementExceptionsArray(badFields);
            }
        }

        public override int NumElements { get { return 1; } }
        public override Element AsElement { get { return new MarketElementSubscriptionStarted(this); } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                if (this._exceptionsNull != null)
                    yield return this._exceptionsNull;

                if (this._exceptionsBadFields != null)
                    yield return this._exceptionsBadFields;
            }
        }


        public override string TopicName { get { return this._topicName; } }

        public override string ToString()
        {
            string result;

            if (this._exceptionsNull != null)
                result = string.Format("SubscriptionStarted = {{{0}}}{0}", Environment.NewLine);

            else if (this._exceptionsBadFields != null)
            {
                StringBuilder strb = new StringBuilder();
                strb.AppendFormat("SubscriptionStarted = {{{0}", Environment.NewLine);
                strb.Append(this._exceptionsBadFields.PrettyPrint(1));
                strb.Append("}");
                result = strb.ToString();
            }
            else
                result = "";

            return result;
        }
    }
}
