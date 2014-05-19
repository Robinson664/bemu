//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayBarRequest/IntradayBarEvent.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.IntradayBarRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class IntradayBarEvent : Event
    {
        private readonly List<Message> _messages;

        internal IntradayBarEvent(IntradayBarRequest request)
        {
            base._request = request;
            this._messages = this.GenerateMessages();
        }

        private List<Message> GenerateMessages()
        {
            List<Message> result = new List<Message>();
            var ireq = (IntradayBarRequest)base._request;

            string security = ireq.Security;
            bool securityError = Types.Rules.IsSecurityError(security);

            if (securityError)
            {
                IntradayBarMessage msg = new IntradayBarMessage(base._request.correlationId, ireq.Service, security);
                result.Add(msg);
            }
            else
            {
                var barData = new List<IntradayBarTickDataType>();
                if (ireq.DtStart.HasValue)
                {
                    foreach (var dtCurrent in ireq.GetDateTimes())
                    {
                        var value = Types.RandomDataGenerator.GenerateBarData(dtCurrent);
                        barData.Add(value);
                    }
                }
                IntradayBarMessage msg = new IntradayBarMessage(base._request.correlationId, ireq.Service, barData);
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
