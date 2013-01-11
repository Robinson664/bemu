using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.HistoricalDataRequest
{
    internal class MessageHistoric : Message
    {
        private readonly ElementHistoricSecurityData _security;

        internal MessageHistoric(CorrelationID corr, string securityName, Dictionary<DateTime, Dictionary<string, object>> fieldData, int sequenceNumber) : base(new Name("TBD"), corr)
        {
            this._security = new ElementHistoricSecurityData(securityName, fieldData, sequenceNumber);
        }

        public override IEnumerable<Element> Elements { get { yield return this._security; } }
        public override object this[string name, int index] { get { return null; } }
        public override BEmu.Element AsElement { get { return new ElementReference(this); } }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.Append("HistoricalDataResponse (choice) = {" + Environment.NewLine);
            result.Append(this._security.PrettyPrint(1));
            result.Append("}");

            return result.ToString();
        }

    }
}
