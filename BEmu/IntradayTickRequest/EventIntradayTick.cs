using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.IntradayTickRequest
{
    internal class EventIntradayTick : Event
    {
        private readonly List<Message> _messages;

        internal EventIntradayTick(RequestIntradayTick request)
        {
            base._request = request;
            this._messages = this.GenerateMessages();
        }

        public override IEnumerable<Message> GetMessages()
        {
            return this._messages;
        }

        private List<Message> GenerateMessages()
        {
            List<Message> result = new List<Message>();
            var ireq = (RequestIntradayTick)base._request;

            var tickData = new Dictionary<DateTime, Tuple<string, double, int>>();

            if (ireq.DtStart.HasValue)
            {
                foreach (var dtCurrent in ireq.GetDates())
                {
                    if ((dtCurrent.DayOfWeek != DayOfWeek.Sunday) && (dtCurrent.DayOfWeek != DayOfWeek.Saturday))
                    {
                        var value = new Tuple<string, double, int>("TRADE", Types.RandomDataGenerator.RandomDouble(), Types.RandomDataGenerator.IntradayTickTradeSize());
                        tickData.Add(dtCurrent, value);
                    }
                }
            }

            MessageIntradayTick msg = new MessageIntradayTick(base._request.correlationId, tickData, ireq.IncludeConditionCodes, ireq.Service);
            result.Add(msg);

            return result;
        }
    }
}
