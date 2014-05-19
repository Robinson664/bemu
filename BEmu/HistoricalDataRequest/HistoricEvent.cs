//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="HistoricalDataRequest/HistoricEvent.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.HistoricalDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class HistoricEvent : Event
    {
        private readonly List<Message> _messages;

        internal HistoricEvent(HistoricRequest request)
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
            var hreq = (HistoricRequest)base._request;

            var badFields = new List<string>();
            for (int i = hreq.Fields.Count - 1; i >= 0; i--)
            {
                if (Types.Rules.IsBadField(hreq.Fields[i]))
                {
                    badFields.Add(hreq.Fields[i]);
                    hreq.Fields.RemoveAt(i);
                }
            }

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

                HistoricMessage msg = new HistoricMessage(base._request.correlationId, security, badFields, fieldData, result.Count);
                result.Add(msg);
            }

            return result;
        }

    }
}
