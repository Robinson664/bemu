//------------------------------------------------------------------------------
// <copyright project="BEmu" file="HistoricalDataRequest/MessageHistoric.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.HistoricalDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class MessageHistoric : Message
    {
        private readonly ElementHistoricSecurityData _security;

        internal MessageHistoric(CorrelationID corr, string securityName, List<string> badFields, Dictionary<DateTime, Dictionary<string, object>> fieldData, int sequenceNumber)
            : base(new Name("HistoricalDataResponse"), corr, null)
        {
            this._security = new ElementHistoricSecurityData(securityName, badFields, fieldData, sequenceNumber);
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
