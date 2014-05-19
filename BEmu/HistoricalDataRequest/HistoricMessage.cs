//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="HistoricalDataRequest/HistoricMessage.cs" company="Jordan Robinson">
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

    internal class HistoricMessage : Message
    {
        private readonly HistoricElementSecurityData _security;

        internal HistoricMessage(CorrelationID corr, string securityName, List<string> badFields, Dictionary<DateTime, Dictionary<string, object>> fieldData, int sequenceNumber)
            : base(new Name("HistoricalDataResponse"), corr, null)
        {
            this._security = new HistoricElementSecurityData(securityName, badFields, fieldData, sequenceNumber);
        }

        public override IEnumerable<Element> Elements { get { yield return this._security; } }
        public override object this[string name, int index] { get { return null; } }
        public override Element AsElement { get { return new HistoricElementReference(this); } }

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
