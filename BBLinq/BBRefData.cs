using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BBLinq.Types;

using Bloomberglp.Blpapi;

namespace BBLinq
{
    public static class BBRefDataType
    {
        /// <summary>
        /// Static security data.
        /// </summary>
        /// <param name="bbKeys">Bloomberg Yellow Key identifiers for securities</param>
        /// <param name="fields">Static data fields for bulk or simple data.</param>
        /// <param name="overrides">Optional: overrides for fields.</param>
        /// <returns></returns>
        public static IEnumerable<FieldType> BBRefData(this IEnumerable<string> bbKeys, IEnumerable<string> fields, IDictionary<string, string> overrides = null)
        {
            return BBRefDataHelpers.SendRequest(bbKeys, fields, overrides);
        }

        private static class BBRefDataHelpers
        {
            static BBRefDataHelpers()
            {
                BBRefDataHelpers.OpenSession();
            }

            private static Service _service;
            private static Session _session;
            private static void OpenSession()
            {
                SessionOptions sessionOptions = new SessionOptions();
                sessionOptions.ServerHost = "127.0.0.1";
                sessionOptions.ServerPort = 8194;

                BBRefDataHelpers._session = new Session(sessionOptions);
                BBRefDataHelpers._session.Start();
                BBRefDataHelpers._session.OpenService("//blp/refdata");

                BBRefDataHelpers._service = BBRefDataHelpers._session.GetService("//blp/refdata");
            }

            public static IEnumerable<FieldType> SendRequest(IEnumerable<string> bbKeys, IEnumerable<string> fields, IDictionary<string, string> overrides = null)
            {
                Request request = BBRefDataHelpers._service.CreateRequest("ReferenceDataRequest");

                foreach (var item in bbKeys)
                {
                    request.Append(Names.SECURITIES, item);
                }

                foreach (var item in fields)
                {
                    request.Append(Names.FIELDS, item);
                }

                if (overrides != null && overrides.Count > 0)
                {
                    Element elmOverrides = request[Names.OVERRIDES];
                    foreach (var item in overrides)
                    {
                        Element elm = elmOverrides.AppendElement();
                        elm.SetElement(Names.FIELDID, item.Key);
                        elm.SetElement(Names.VALUE, item.Value);
                    }
                }

                CorrelationID corr = new CorrelationID(NextCorrelationId.Get());
                BBRefDataHelpers._session.SendRequest(request, corr);

                bool continueToLoop = true;
                while (continueToLoop) //wait for a complete response
                {
                    IEnumerable<FieldType> current = null;
                    Event eventObj = BBRefDataHelpers._session.NextEvent();

                    switch (eventObj.Type)
                    {
                        case Event.EventType.RESPONSE: // final event
                            continueToLoop = false;
                            current = BBRefDataHelpers.ProcessResponse(eventObj, corr, fields);
                            break;
                        case Event.EventType.PARTIAL_RESPONSE:
                            current = BBRefDataHelpers.ProcessResponse(eventObj, corr, fields);
                            break;
                    }

                    if (current != null)
                    {
                        foreach (var item in current)
                        {
                            yield return item;
                        }
                    }
                }
            }

            private static IEnumerable<FieldType> ProcessResponse(Event eventObj, CorrelationID corr, IEnumerable<string> fields)
            {
                foreach (var message in eventObj.GetMessages()) //loop through each message
                {
                    if (message.CorrelationID.Value == corr.Value)
                    {
                        Element elmSecDataArr = message.GetElement(Names.SECURITYDATA);
                        for (int i = 0; i < elmSecDataArr.NumValues; i++) //loop through each security
                        {
                            Element elmSecData = elmSecDataArr.GetValueAsElement(i);
                            Element elmSecurity = elmSecData.GetElement(Names.SECURITY);
                            string bbkey = elmSecurity.GetValueAsString(0);
                            Element elmFieldData = elmSecData.GetElement(Names.FIELDDATA);

                            foreach (var field in fields)
                            {
                                if (elmFieldData.HasElement(field, true)) //check if the given field exists (ignoring null elements)
                                {
                                    Element elmField = elmFieldData.GetElement(field);

                                    if (elmField.IsArray) //some fields like "OPT_CHAIN" return bulk data (as arrays)
                                    {
                                        for (int j = 0; j < elmField.NumValues; j++)
                                        {
                                            Element elmArrayItem = elmField.GetValueAsElement(j);
                                            for (int k = 0; k < elmArrayItem.NumElements; k++)
                                            {
                                                Element elmK = elmArrayItem.GetElement(k);
                                                FieldType ftype = new FieldType(bbkey, elmK.Name.ToString(), BBTypeConverter.GetValue(elmK));
                                                yield return ftype;
                                            }
                                        }
                                    }
                                    else //most fields return simple data, like "BID" and "ASK"
                                    {
                                        FieldType ftype = new FieldType(bbkey, field, BBTypeConverter.GetValue(elmField));
                                        yield return ftype;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
