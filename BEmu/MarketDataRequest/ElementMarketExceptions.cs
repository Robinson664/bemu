//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/ElementMarketExceptions.cs" company="Jordan Robinson">
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

    internal class ElementMarketExceptions : Element
    {
        private readonly ElementMarketString _fieldId;
        private readonly ElementMarketReason _reason;

        public ElementMarketExceptions(string badField)
        {
            this._fieldId = new ElementMarketString("fieldId", badField);
            this._reason = new ElementMarketReason(ElementMarketReason.ReasonTypeEnum.badField);
        }

        public override int NumElements { get { return 2; } }
        public override int NumValues { get { return 1; } }
        public override Name Name { get { return new Name("exceptions"); } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsNull { get { return false; } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._fieldId;
                yield return this._reason;
            }
        }

        public override Element GetElement(string name)
        {
            return this[name];
        }

        public override string GetElementAsString(string name)
        {
            return this[name].GetValueAsString();
        }

        public override Element this[string name]
        {
            get
            {
                string strName = name.ToUpper();
                foreach (var item in this.Elements)
                {
                    if (item.Name.ToString().ToUpper() == strName)
                        return item;
                }
                return base[name];
            }
        }

        public override bool HasElement(string name, bool excludeNullElements = false)
        {
            foreach (var item in this.Elements)
            {
                if (item.Name.ToString().ToUpper() == name.ToUpper())
                    return true;
            }
            return false;
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{2} = {{{1}", tabs, Environment.NewLine, this.Name.ToString());
            foreach (var item in this.Elements)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);
            return result;
        }

    }
}
