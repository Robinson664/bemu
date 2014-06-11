//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="MarketDataRequest/MarketElementExceptionsArray.cs" company="Jordan Robinson">
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

    internal class MarketElementExceptionsArray : Element
    {
        private readonly List<MarketElementExceptions> _exceptions;

        public MarketElementExceptionsArray(IEnumerable<string> badFields)
        {
            this._exceptions = new List<MarketElementExceptions>();
            foreach (var item in badFields)
            {
                this._exceptions.Add(new MarketElementExceptions(item));
            }
        }

        public override Element GetValueAsElement(int index) { return (Element)this._exceptions[index]; }
        public override object this[int index] { get { return this._exceptions[index]; } }

        public override SchemaTypeDefinition TypeDefinition { get { return new SchemaTypeDefinition(this.Datatype, new Name("SubscriptionException")); } }
        public override Name Name { get { return new Name("exceptions"); } }
        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return this._exceptions.Count; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return true; } }
        public override bool IsNull { get { return false; } }
        public override IEnumerable<Element> Elements { get { if (this._exceptions.Count < -1) yield return null; } } //This is the only way I can think to have the compiler output "Enumeration yielded no results"

        public override object GetValue(int index)
        {
            return this._exceptions[index];
        }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1}[] = {{{2}", tabs, this.Name, Environment.NewLine);
            foreach (var item in this._exceptions)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }


    }
}
