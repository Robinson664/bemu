//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayTickRequest/EventIntradayTick.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayTickRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

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

            string security = ireq.Security;
            bool isResponseError = Types.Rules.IsSecurityError(security);

            if (isResponseError)
            {
                MessageIntradayTick msg = new MessageIntradayTick(base._request.correlationId, ireq.Service);
                result.Add(msg);
            }
            else
            {
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

                MessageIntradayTick msg = new MessageIntradayTick(base._request.correlationId, ireq.Service, tickData, ireq.IncludeConditionCodes);
                result.Add(msg);
            }

            return result;
        }
    }
}
