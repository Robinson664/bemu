//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/ElementMarketSubscriptionCancelReason.cs" company="Jordan Robinson">
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

    internal class ElementMarketSubscriptionCancelReason : Element
    {
        private readonly ElementMarketString _source, _category, _description, _subCategory;
        private readonly ElementMarketInt _errorCode;

        internal ElementMarketSubscriptionCancelReason()
        {
            this._source = new ElementMarketString("source", "Session");
            this._errorCode = new ElementMarketInt("errorCode", 0);
            this._category = new ElementMarketString("category", "CANCELED");
            this._description = new ElementMarketString("description", "Subscription canceled");
            this._subCategory = new ElementMarketString("subcategory", "");
        }

        public override Name Name { get { return new Name("reason"); } }
        public override int NumElements { get { return 5; } }
        public override int NumValues { get { return 1; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsNull { get { return false; } }

        public override object this[int index] { get { return null; } }

        public override Element this[string name]
        {
            get
            {
                foreach (var item in this.Elements)
                {
                    if (item.Name.ToString().ToUpper() == name.ToUpper())
                        return item;
                }
                return base[name];
            }
        }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._source;
                yield return this._errorCode;
                yield return this._category;
                yield return this._description;
                yield return this._subCategory;
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}reason = {{{1}", tabs, Environment.NewLine);
            foreach (var item in this.Elements)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);
            return result;
        }
    }
}
