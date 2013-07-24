//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/EventMarket.cs" company="Jordan Robinson">
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

    internal class EventMarket : Event
    {
        private readonly List<Message> _messages;

        internal EventMarket(EventType evtType, CorrelationID corr, IEnumerable<Subscription> subscriptions) //use for subscribing
        {
            this._messages = new List<Message>();

            switch (evtType)
            {
                case EventType.SESSION_STATUS:
                    base._type = evtType;
                    MessageMarketSessionOpened msgSessionOpened = new MessageMarketSessionOpened();
                    this._messages.Add(msgSessionOpened);
                    break;

                case EventType.SERVICE_STATUS:
                    base._type = evtType;
                    MessageMarketServiceStatus msgServiceStatus = new MessageMarketServiceStatus(corr);
                    this._messages.Add(msgServiceStatus);
                    break;

                case EventType.SUBSCRIPTION_STATUS:
                    base._type = evtType;
                    foreach (var item in subscriptions)
                    {
                        bool securityError = Types.Rules.IsSecurityError(item.Security);
                        if (securityError)
                        {
                            MessageMarketSubscriptionFailure msgError = new MessageMarketSubscriptionFailure(item);
                            this._messages.Add(msgError);
                        }
                        else
                        {
                            MessageMarketSubscriptionStarted msgSubStatus = new MessageMarketSubscriptionStarted(item);
                            this._messages.Add(msgSubStatus);
                        }
                    }
                    break;

                case EventType.SUBSCRIPTION_DATA:
                    base._type = evtType;
                    foreach (var item in subscriptions)
                    {
                        bool securityError = Types.Rules.IsSecurityError(item.Security);
                        if (!securityError)
                        {
                            MessageMarketSubscriptionData msgSubData = new MessageMarketSubscriptionData(item, EventMarket.GenerateFakeMessageData(item));
                            this._messages.Add(msgSubData);
                        }
                    }
                    break;

                default:
                    throw new NotImplementedException(string.Format("BEmu.MarketDataRequest.EventMarket.EventMarket: doesn't expect EventType {0}", evtType.ToString()));
            }
        }

        internal EventMarket(EventType evtType, Subscription subscription) //use for unsubscribing
        {
            this._messages = new List<Message>();

            switch (evtType)
            {
                case EventType.SUBSCRIPTION_STATUS:
                    base._type = evtType;
                    MessageMarketSubscriptionCanceled msgCancel = new MessageMarketSubscriptionCanceled(subscription);
                    this._messages.Add(msgCancel);
                    break;
                default:
                    break;
            }
        }

        private static Dictionary<string, object> GenerateFakeMessageData(Subscription sub)
        {
            return Types.RandomDataGenerator.GetMarketDataFields(sub.Fields);
        }

        public override IEnumerable<Message> GetMessages()
        {
            return this._messages;
        }
    }
}
