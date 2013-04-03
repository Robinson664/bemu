//------------------------------------------------------------------------------
// <copyright project="BEmu" file="HistoricalDataRequest/ElementHistoricFieldData.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.HistoricalDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementHistoricFieldData : Element
    {
        private readonly Dictionary<string, Element> _fields; //make a dic

        public ElementHistoricFieldData(DateTime date, Dictionary<string, object> values)
        {
            this._fields = new Dictionary<string, Element>();

            Element elmDate = new ElementHistoricDateTime(date);
            this._fields.Add(elmDate.Name.ToString().ToUpper(), elmDate);

            foreach (var item in values)
            {
                if (item.Value is double)
                {
                    Element elmDouble = new ElementHistoricDouble(item.Key.ToUpper(), (double)item.Value);
                    this._fields.Add(elmDouble.Name.ToString(), elmDouble);
                }
            }
        }

        public override IEnumerable<Element> Elements { get { return this._fields.Values; } }

        public override Name Name { get { return new Name("fieldData"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return this._fields.Count; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsArray { get { return false; } }

        public override object this[int index] { get { return null; } }

        public override Element this[string name]
        {
            get
            {
                return this._fields[name.ToUpper()];
            }
        }

        public override object this[string name, int index]
        {
            get
            {
                if (index == 0)
                    return this[name].GetValue();
                else
                    return base[name, index];
            }
        }

        public override int GetElementAsInt32(string name)
        {
            return this[name].GetValueAsInt32();
        }

        public override Datetime GetElementAsDatetime(string name)
        {
            return this[name].GetValueAsDatetime();
        }

        public override Datetime GetElementAsDate(string name)
        {
            return this[name].GetValueAsDate();
        }

        public override Datetime GetElementAsTime(string name)
        {
            return this[name].GetValueAsTime();
        }

        public override string GetElementAsString(string name)
        {
            return this[name].GetValueAsString();
        }

        public override float GetElementAsFloat32(string name)
        {
            return this[name].GetValueAsFloat32();
        }

        public override double GetElementAsFloat64(string name)
        {
            return this[name].GetValueAsFloat64();
        }

        public override long GetElementAsInt64(string name)
        {
            return this[name].GetValueAsInt64();
        }

        public override bool HasElement(string name, bool excludeNullElements = false)
        {
            return this._fields.ContainsKey(name.ToUpper());
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}fieldData = {{{1}", tabs, Environment.NewLine);
            foreach (var item in this._fields.Values)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);
            return result;
        }
    }
}
