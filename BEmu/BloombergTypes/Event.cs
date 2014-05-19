//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/Event.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    public abstract class Event
    {
        protected Event.EventType _type;
        public Event.EventType Type { get { return this._type; } }

        protected Request _request;

        internal static Event EventFactory(Request request, bool isLastRequest)
        {
            Event result;
            if (request is HistoricalDataRequest.HistoricRequest)
            {
                result = new HistoricalDataRequest.HistoricEvent((HistoricalDataRequest.HistoricRequest)request);
                result._type = isLastRequest ? EventType.RESPONSE : EventType.PARTIAL_RESPONSE;
                return result;
            }
            else if (request is ReferenceDataRequest.ReferenceRequest)
            {
                result = new ReferenceDataRequest.ReferenceEvent((ReferenceDataRequest.ReferenceRequest)request);
                result._type = isLastRequest ? EventType.RESPONSE : EventType.PARTIAL_RESPONSE;
                return result;
            }
            else if (request is IntradayTickRequest.IntradayTickRequest)
            {
                result = new IntradayTickRequest.IntradayTickEvent((IntradayTickRequest.IntradayTickRequest)request);
                result._type = isLastRequest ? EventType.RESPONSE : EventType.PARTIAL_RESPONSE;
                return result;
            }
            else if (request is IntradayBarRequest.IntradayBarRequest)
            {
                result = new IntradayBarRequest.IntradayBarEvent((IntradayBarRequest.IntradayBarRequest)request);
                result._type = isLastRequest ? EventType.RESPONSE : EventType.PARTIAL_RESPONSE;
                return result;
            }
            else
            {
                throw new NotImplementedException(string.Format("Request type {0} is not implemented", request.GetType()));
            }
        }


        public abstract IEnumerable<Message> GetMessages();

        public IEnumerator<Message> GetEnumerator()
        {
            return this.GetMessages().GetEnumerator();
        }

        public enum EventType
        {
            ADMIN = 1,
            SESSION_STATUS = 2,
            SUBSCRIPTION_STATUS = 3,
            REQUEST_STATUS = 4,
            SERVICE_STATUS = 5,
            RESPONSE = 6,
            PARTIAL_RESPONSE = 7,
            SUBSCRIPTION_DATA = 8,
            TIMEOUT = 9,
            AUTHORIZATION_STATUS = 10,
            RESOLUTION_STATUS = 11,
            TOPIC_STATUS = 12,
            TOKEN_STATUS = 13,
            REQUEST = 14,
        }
    }
}
