//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayBarRequest/EventIntradayBar.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayBarRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

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

            string security = ireq.Security;
            bool securityError = Types.Rules.IsSecurityError(security);

            if (securityError)
            {
                MessageIntradayBar msg = new MessageIntradayBar(base._request.correlationId, ireq.Service, security);
                result.Add(msg);
            }
            else
            {
                var barData = new List<BarTickDataType>();
                if (ireq.DtStart.HasValue)
                {
                    foreach (var dtCurrent in ireq.GetDateTimes())
                    {
                        var value = Types.RandomDataGenerator.GenerateBarData(dtCurrent);
                        barData.Add(value);
                    }
                }
                MessageIntradayBar msg = new MessageIntradayBar(base._request.correlationId, ireq.Service, barData);
                result.Add(msg);
            }

            return result;
        }

        public override IEnumerable<Message> GetMessages()
        {
            return this._messages;
        }

    }
}
