//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayTickRequest/IntradayTickEvent.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.IntradayTickRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class IntradayTickEvent : Event
    {
        private readonly List<Message> _messages;

        internal IntradayTickEvent(IntradayTickRequest request)
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
            var ireq = (IntradayTickRequest)base._request;

            string security = ireq.Security;
            bool isResponseError = Types.Rules.IsSecurityError(security);

            if (isResponseError)
            {
                IntradayTickMessage msg = new IntradayTickMessage(base._request.correlationId, ireq.Service);
                result.Add(msg);
            }
            else
            {
                var tickData = new SortedDictionary<DateTime, Types.Tuple3<string, double, int>>();

                if (ireq.DtStart.HasValue)
                {
                    foreach (var dtCurrent in ireq.GetDates())
                    {
                        if ((dtCurrent.DayOfWeek != DayOfWeek.Sunday) && (dtCurrent.DayOfWeek != DayOfWeek.Saturday))
                        {
                            var value = new Types.Tuple3<string, double, int>("TRADE", Types.RandomDataGenerator.RandomDouble(), Types.RandomDataGenerator.IntradayTickTradeSize());
                            tickData.Add(dtCurrent, value);
                        }
                    }
                }

                IntradayTickMessage msg = new IntradayTickMessage(base._request.correlationId, ireq.Service, tickData, ireq.IncludeConditionCodes);
                result.Add(msg);
            }

            return result;
        }
    }
}
