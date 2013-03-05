using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.HistoricalDataRequest
{
    internal class EventHistoric : Event
    {
        private readonly List<Message> _messages;

        internal EventHistoric(RequestHistoric request)
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
            var hreq = (RequestHistoric)base._request;
            
            foreach (var security in hreq.Securities)
            {
                var fieldData = new Dictionary<DateTime, Dictionary<string, object>>();

                if (hreq.DtStart.HasValue)
                {
                    foreach (var dtCurrent in hreq.GetDates())
                    {
                        if ((dtCurrent.DayOfWeek != DayOfWeek.Sunday) && (dtCurrent.DayOfWeek != DayOfWeek.Saturday))
                        {
                            var fields = new Dictionary<string, object>();
                            fieldData.Add(dtCurrent, fields);

                            foreach (var field in hreq.Fields)
                            {
                                fields.Add(field, Types.RandomDataGenerator.RandomDouble());
                            }
                        }
                    }
                }

                MessageHistoric msg = new MessageHistoric(base._request.correlationId, security, fieldData, result.Count);
                result.Add(msg);
            }

            return result;
        }

    }
}
