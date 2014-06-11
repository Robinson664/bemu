//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceElementArrayChainTickersItem.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.ReferenceDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ReferenceElementArrayChainTickersItem : Element
    {
        private readonly ReferenceElementString _element;

        internal ReferenceElementArrayChainTickersItem(string ticker, DateTime dtExp, ReferenceElementArrayChainTickers.OptionalityEnum optionality, int strike)
        {
            string optionTicker = string.Format("{0} US {1:MM/dd/yy} {2}{3}", ticker, dtExp, (char)optionality, strike);
            this._element = new ReferenceElementString("Ticker", optionTicker);
        }

        public override Name Name { get { return new Name("Ticker"); } }
        public override int NumValues { get { return 0; } }
        public override int NumElements { get { return 1; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return false; } }
        public override IEnumerable<Element> Elements { get { yield return this._element; } }
        public override string GetElementAsString(string name) { return this[name].GetValueAsString(); }
        public override SchemaTypeDefinition TypeDefinition { get { return new SchemaTypeDefinition(this.Datatype, new Name("CHAIN_TICKERS")); } }

        //public override string GetElementAsString(string name)
        public override Element this[string name]
        {
            get
            {
                foreach (var item in this.Elements)
                {
                    if (item.Name.ToString() == name)
                        return item;
                }
                return base[name];
            }
        }


        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}CHAIN_TICKERS = {{{1}", tabs, Environment.NewLine);

            result.Append(this._element.PrettyPrint(tabIndent + 1));
            
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);
            return result;
        }
    }
}
