//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/ElementReferenceFieldData.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.ReferenceDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementReferenceFieldData : Element
    {
        private readonly List<Element> _fields;

        internal ElementReferenceFieldData(Dictionary<string, object> values)
        {
            this._fields = new List<Element>();
            
            foreach (var item in values)
            {
                if (item.Value is double)
                {
                    Element elmDouble = new ElementReferenceDouble(item.Key.ToUpper(), (double)item.Value);
                    this._fields.Add(elmDouble);
                }
                else if (item.Value is int)
                {
                    Element elmInt = new ElementReferenceInt(item.Key.ToUpper(), (int)item.Value);
                    this._fields.Add(elmInt);
                }
                else if (item.Value is DateTime)
                {
                    Element elmDateTime = new ElementReferenceDateTime(item.Key.ToUpper(), (DateTime)item.Value);
                    this._fields.Add(elmDateTime);
                }
                else if (item.Value is string)
                {
                    Element elmString = new ElementReferenceString(item.Key.ToUpper(), (string)item.Value);
                    this._fields.Add(elmString);
                }
                else if (item.Value is ElementReferenceArrayChainTickers)
                    this._fields.Add((ElementReferenceArrayChainTickers)item.Value);
            }
        }

        public override IEnumerable<Element> Elements { get { return this._fields; } }

        public override Name Name { get { return new Name("fieldData"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return this._fields.Count; } }

        public override Element GetElement(int index)
        {
            return this._fields[index];
        }

        public override Element GetElement(string name)
        {
            return this[name];
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}fieldData = {{{1}", tabs, Environment.NewLine);
            foreach (var item in this._fields)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);
            return result;
        }

        public override bool HasElement(string name, bool excludeNullElements = false)
        {
            foreach (var item in this._fields)
            {
                if (item.Name.ToString().ToUpper() == name.ToUpper())
                    return true;
            }
            return false;
        }

        public override Element this[string name]
        {
            get
            {
                string strName = name.ToUpper();
                foreach (var item in this._fields)
                {
                    if (item.Name.ToString().ToUpper() == strName)
                        return item;
                }
                return base[name];
            }
        }

        public override double GetElementAsFloat64(string name)
        {
            return this[name].GetValueAsFloat64();
        }

        public override int GetElementAsInt32(string name)
        {
            return this[name].GetValueAsInt32();
        }

        public override long GetElementAsInt64(string name)
        {
            return this[name].GetValueAsInt64();
        }

        public override string GetElementAsString(string name)
        {
            return this[name].GetValueAsString();
        }

    }
}
