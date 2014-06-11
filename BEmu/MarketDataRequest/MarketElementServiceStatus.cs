//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="MarketDataRequest/MarketElementServiceStatus.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.MarketDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class MarketElementServiceStatus : Element
    {
        private readonly MarketElementString _serviceName;

        internal MarketElementServiceStatus(MarketMessageServiceStatus arg)
        {
            this._serviceName = (MarketElementString)arg.Elements.First();
        }

        public override int NumElements { get { return 1; } }
        public override int NumValues { get { return 1; } }
        public override Name Name { get { return new Name("ServiceOpened"); } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsNull { get { return false; } }
        public override object this[int index] { get { return null; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.SEQUENCE; } }

        

        public override Element GetElement(int index)
        {
            if (index == 0)
                return this._serviceName;
            else
                return base.GetElement(index);
        }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("{0} = {{{1}", this.Name.ToString(), Environment.NewLine);
            result.Append(this._serviceName.PrettyPrint(1));
            result.Append("}" + Environment.NewLine);
            return result;
        }
    }
}
