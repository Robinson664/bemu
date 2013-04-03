//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/ElementMarketSubscriptionStarted.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.MarketDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementMarketSubscriptionStarted : Element
    {
        private readonly ElementMarketNull _exceptions;

        internal ElementMarketSubscriptionStarted(MessageMarketSubscriptionStarted arg)
        {
            this._exceptions = (ElementMarketNull)arg.Elements.First();
        }

        public override Name Name { get { return new Name("SubscriptionStarted"); } }
        public override int NumElements { get { return 1; } }
        public override int NumValues { get { return 1; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsNull { get { return false; } }

        public override object this[int index] { get { return null; } }
        public override Element this[string name]
        {
            get
            {
                if (name.ToUpper() == this._exceptions.Name.ToString().ToUpper())
                    return this._exceptions;
                else
                    return base[name];
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return new StringBuilder();
        }

        public override string ToString()
        {
            return string.Format("SubscriptionStarted = {{{0}}}{0}", Environment.NewLine);
        }

    }
}
