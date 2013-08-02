//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/ElementMarketReason.cs" company="Jordan Robinson">
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

    internal class ElementMarketReason : Element
    {
        private readonly ElementMarketString _source, _category, _description;
        private readonly ElementMarketInt _errorCode;

        public enum ReasonTypeEnum { badSecurity, badField }

        public ElementMarketReason(ReasonTypeEnum reasonType)
        {
            if (reasonType == ReasonTypeEnum.badSecurity)
            {
                this._source = new ElementMarketString("source", string.Format("{0}{1}@{2}", Types.RandomDataGenerator.RandomString(5).ToLower(), Types.RandomDataGenerator.RandomInt(9), Types.RandomDataGenerator.RandomInt(99)));
                this._errorCode = new ElementMarketInt("code", Types.RandomDataGenerator.RandomInt(99));
                this._category = new ElementMarketString("category", "BAD_SEC");
                this._description = new ElementMarketString("description", "Invalid security, rcode = -1");
            }
            else if (reasonType == ReasonTypeEnum.badField)
            {
                this._source = new ElementMarketString("source", string.Format("{0}@{1}", Types.RandomDataGenerator.RandomString(7).ToLower(), Types.RandomDataGenerator.RandomInt(999)));
                this._errorCode = new ElementMarketInt("errorCode", Types.RandomDataGenerator.RandomInt(99));
                this._category = new ElementMarketString("category", "BAD_FLD");
                this._description = new ElementMarketString("description", "Unknown Field");
            }
        }

        public override int NumElements { get { return 4; } }
        public override int NumValues { get { return 1; } }
        public override Name Name { get { return new Name("reason"); } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsNull { get { return false; } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._source;
                yield return this._errorCode;
                yield return this._category;
                yield return this._description;
            }
        }

        public override string GetElementAsString(string name)
        {
            return this[name].GetValueAsString();
        }

        public override int GetElementAsInt32(string name)
        {
            return this[name].GetValueAsInt32();
        }

        public override Element GetElement(string name)
        {
            return this[name];
        }

        public override object GetValue()
        {
            return null;
        }

        public override object GetValue(int index)
        {
            return null;
        }

        public override object this[int index]
        {
            get
            {
                return null;
            }
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

        public override object this[string name, int index]
        {
            get
            {
                if (index == 0)
                    return this[name];
                else
                    throw new IndexOutOfRangeException();
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
