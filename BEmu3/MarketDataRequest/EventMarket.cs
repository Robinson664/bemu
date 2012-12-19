using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.MarketDataRequest
{
    public class EventMarket : Event
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
                        MessageMarketSubscriptionStarted msgSubStatus = new MessageMarketSubscriptionStarted(item);
                        this._messages.Add(msgSubStatus);
                    }
                    break;

                case EventType.SUBSCRIPTION_DATA:
                    base._type = evtType;
                    foreach (var item in subscriptions)
                    {
                        MessageMarketSubscriptionData msgSubData = new MessageMarketSubscriptionData(item, EventMarket.GenerateFakeMessageData(item));
                        this._messages.Add(msgSubData);
                    }
                    break;

                default:
                    throw new NotImplementedException(string.Format("BEmu3.MarketDataRequest.EventMarket.EventMarket: doesn't expect EventType {1}", evtType.ToString()));
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

        private static readonly Random _random = new Random(100);
        private static Dictionary<string, object> GenerateFakeMessageData(Subscription sub)
        {
            var result = new Dictionary<string, object>();
            foreach (var item in sub.Fields)
            {
                string upper = item.ToUpper();

                if (upper.Contains("TIME"))
                    result.Add(item, new Types.TimeType(DateTime.Now.AddMinutes(-1d * EventMarket._random.NextDouble() * 100d)));
                else if (upper.Contains("DATE"))
                    result.Add(item, new Types.DateType(DateTime.Now.AddDays(-1d * EventMarket._random.NextDouble() * 100d)));
                else
                    result.Add(item, Math.Round(EventMarket._random.NextDouble() * 100d, 2));
            }
            return result;
        }

        public override IEnumerable<Message> GetMessages()
        {
            return this._messages;
        }
    }
}
