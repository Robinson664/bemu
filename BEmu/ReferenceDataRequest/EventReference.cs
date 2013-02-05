using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Text.RegularExpressions;

namespace BEmu.ReferenceDataRequest
{
    internal class EventReference : Event
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
                    bool isOption = Regex.IsMatch(security.ToUpper(), @"[A-Z]{1,4}\s+\d{6}[CP]\d{8} EQUITY"); //options look like: AAPL 150117C00600000 EQUITY

                    var fieldData = new Dictionary<string, object>();
                    securities.Add(security, fieldData);

                    foreach (var field in rreq.Fields)
                    {
                        object value = Types.RandomDataGenerator.ReferenceDataFromFieldName(field, security, isOption, rreq);
                        if (value != null)
                        {
                            fieldData.Add(field.ToUpper(), value);
                        }

                        //var upper = field.ToUpper();

                        //if (upper == "CHAIN_TICKERS") //this is the only array type I will code for.  It's just an example.
                        //{
                        //    if (!isOption)
                        //    {
                        //        uint numPoints = 1;
                        //        string dtExp = null;
                        //        var optionality = ElementReferenceArrayChainTickers.OptionalityEnum.call;

                        //        if (rreq.HasElement("overrides"))
                        //        {
                        //            var overrides = rreq["overrides"];
                        //            for (int i = 0; i < overrides.NumValues; i++)
                        //            {
                        //                var element = overrides.GetValueAsElement(i);

                        //                var fieldId = element["fieldId"].GetValueAsString();
                        //                var value = element["value"].GetValueAsString();

                        //                switch (fieldId.ToUpper())
                        //                {
                        //                    case "CHAIN_POINTS_OVRD":
                        //                        numPoints = uint.Parse(value);
                        //                        break;
                        //                    case "CHAIN_EXP_DT_OVRD":
                        //                        dtExp = value;
                        //                        break;
                        //                    case "CHAIN_PUT_CALL_TYPE_OVRD":
                        //                        if (value.ToUpper() == "P")
                        //                            optionality = ElementReferenceArrayChainTickers.OptionalityEnum.put;
                        //                        break;
                        //                }
                        //            }
                        //        }

                        //        ElementReferenceArrayChainTickers chain = new ElementReferenceArrayChainTickers(security, numPoints, dtExp, optionality);
                        //        fieldData.Add(upper, chain);
                        //    }
                        //}
                        //else if (upper.Contains("TICKER"))
                        //{
                        //    string ticker = security.Substring(0, security.IndexOf(' '));
                        //    fieldData.Add(upper, ticker);
                        //}
                        //else if (upper.Contains("OPT_EXPIRE_DT"))
                        //{
                        //    if (security.EndsWith("COMDTY") || security.EndsWith("INDEX"))
                        //    {
                        //        DateTime dtExp = DateTime.Today.AddMonths(3);
                        //        fieldData.Add(upper, dtExp);
                        //    }
                        //    else if (isOption)
                        //    {
                        //        string strDate = security.Substring(security.LastIndexOf(' ') - 15, 6);
                        //        DateTime dtExp = DateTime.ParseExact(strDate, "yyMMdd", null);
                        //        fieldData.Add(upper, dtExp);
                        //    }
                        //}
                        //else if (upper.Contains("TRADEABLE_DT")) //futures
                        //{
                        //    DateTime dtExp = DateTime.Today.AddMonths(3);
                        //    fieldData.Add(upper, dtExp);
                        //}
                        //else
                        //{
                        //    fieldData.Add(upper, Math.Round(rand.NextDouble() * 100d, 2));
                        //}
                    } //end inner foreach
                }
            } //end outer foreach

            MessageReference msg = new MessageReference(base._request.correlationId, securities);
            result.Add(msg);

            return result;
        }
    }
}
