using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.ReferenceDataRequest
{
    public class EventReference : Event
    {
        private readonly List<Message> _messages;

        internal EventReference(RequestReference request)
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
            var rreq = (RequestReference)base._request;
            Random rand = new Random(64);

            var securities = new Dictionary<string, Dictionary<string, object>>();
            foreach (var security in rreq.Securities)
            {
                if (!securities.ContainsKey(security))
                {
                    var fieldData = new Dictionary<string, object>();
                    securities.Add(security, fieldData);

                    foreach (var field in rreq.Fields)
                    {
                        try
                        {

                            if (field.ToUpper().Contains("TICKER"))
                            {
                                string ticker = security.Substring(0, security.IndexOf(' '));
                                fieldData.Add(field, ticker);
                            }
                            else if (field.ToUpper().Contains("EXPIRE_DT"))
                            {
                                if (security.EndsWith("COMDTY") || security.EndsWith("INDEX"))
                                {
                                    DateTime dtExp = DateTime.Today.AddMonths(3);
                                    fieldData.Add(field, dtExp);
                                }
                                else
                                {
                                    string strDate = security.Substring(security.LastIndexOf(' ') - 15, 6);
                                    DateTime dtExp = DateTime.ParseExact(strDate, "yyMMdd", null);
                                    fieldData.Add(field, dtExp);
                                }
                            }
                            else if (field.ToUpper().Contains("TRADEABLE_DT")) //futures
                            {
                                DateTime dtExp = DateTime.Today.AddMonths(3);
                                fieldData.Add(field, dtExp);
                            }
                            else
                            {
                                fieldData.Add(field, Math.Round(rand.NextDouble() * 100d, 2));
                            }


                        }
                        catch (Exception ex)
                        {
                            throw ex;
                        }
                    }
                }
            }

            MessageReference msg = new MessageReference(base._request.correlationId, securities);
            result.Add(msg);

            return result;
        }
    }
}
