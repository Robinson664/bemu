//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="MarketDataRequest/MarketElementSubscriptionStarted.cs" company="Jordan Robinson">
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

    internal class MarketElementSubscriptionStarted : Element
    {
        private readonly MarketElementNull _exceptions;

        internal MarketElementSubscriptionStarted(MarketMessageSubscriptionStarted arg)
        {
            this._exceptions = (MarketElementNull)arg.Elements.First();
        }

        public override Name Name { get { return new Name("SubscriptionStarted"); } }
        public override int NumElements { get { return 1; } }
        public override int NumValues { get { return 1; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsNull { get { return false; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.SEQUENCE; } }

        public override object this[int index] { get { return null; } }
        public override Element this[string name]
        {
            get
            {
                if (name == this._exceptions.Name.ToString())
                    return this._exceptions;
                else
                    return base[name];
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            return new StringBuilder();
        }

        public override string ToString()
        {
            return string.Format("SubscriptionStarted = {{{0}}}{0}", Environment.NewLine);
        }

    }
}
