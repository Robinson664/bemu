//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="HistoricalDataRequest/HistoricElementReference.cs" company="Jordan Robinson">
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

    internal class HistoricElementReference : Element
    {
        private readonly HistoricElementSecurityData _security;

        internal HistoricElementReference(HistoricMessage msg)
        {
            this._security = (HistoricElementSecurityData)msg.Elements.First();
        }

        public override Name Name
        {
            get { return new Name("securityData"); }
        }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 1; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsArray { get { return false; } }
        public override bool IsNull { get { return false; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.CHOICE; } }

        public override Element this[string name]
        {
            get
            {
                if (name.ToUpper() == this._security.Name.ToString().ToUpper())
                    return this._security;
                else
                    return base[name];
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("HistoricalDataResponse (choice) = {{{0}", Environment.NewLine);
            result.Append(this._security.PrettyPrint(1));
            result.Append("}" + Environment.NewLine);
            return result;
        }
        
    }
}
