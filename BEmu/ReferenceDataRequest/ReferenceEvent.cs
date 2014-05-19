//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceEvent.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.ReferenceDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Text.RegularExpressions;

    internal class ReferenceEvent : Event
    {
        private readonly List<Message> _messages;

        internal ReferenceEvent(ReferenceRequest request)
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
            var rreq = (ReferenceRequest)base._request;

            var securities = new Dictionary<string, Dictionary<string, object>>();
            foreach (var security in rreq.Securities)
            {
                if (!securities.ContainsKey(security))
                {
                    bool isOption = Regex.IsMatch(security.ToUpper(), @"[A-Z]{1,4}\s+\d{6}[CP]\d{8} EQUITY"); //options look like: AAPL 150117C00600000 EQUITY

                    var fieldData = new Dictionary<string, object>();

                    if (!securities.ContainsKey(security))
                        securities.Add(security, fieldData);
                    else
                    {
                    }

                    List<string> badFields = new List<string>();
                    foreach (var field in rreq.Fields)
                    {
                        object value = Types.RandomDataGenerator.ReferenceDataFromFieldName(field, security, isOption, rreq);
                        if (value != null && !fieldData.ContainsKey(field))
                        {
                            fieldData.Add(field, value);
                        }
                        else
                        {
                        }
                    }
                }
            }

            ReferenceMessage msg = new ReferenceMessage(base._request.correlationId, securities);
            result.Add(msg);

            return result;
        }
    }
}
