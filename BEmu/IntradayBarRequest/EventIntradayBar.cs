using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.IntradayBarRequest
{
    internal class EventIntradayBar : Event
    {
        private readonly List<Message> _messages;

        internal EventIntradayBar(RequestIntradayBar request)
        {
            base._request = request;
            this._messages = this.GenerateMessages();
        }

        private List<Message> GenerateMessages()
        {
            List<Message> result = new List<Message>();
            var ireq = (RequestIntradayBar)base._request;

            var barData = new List<BarTickDataType>();
            if (ireq.DtStart.HasValue)
            {
                foreach (var dtCurrent in ireq.GetDateTimes())
                {
                    var value = Types.RandomDataGenerator.GenerateBarData(dtCurrent);
                    barData.Add(value);
                }
            }

            MessageIntradayBar msg = new MessageIntradayBar(base._request.correlationId, barData, ireq.Service);
            result.Add(msg);

            return result;
        }

        public override IEnumerable<Message> GetMessages()
        {
            return this._messages;
        }

    }
}
