//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayTickRequest/ElementIntradayTickDataArray.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayTickRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementIntradayTickDataArray : Element
    {
        private readonly List<ElementIntradayTickData> _tickData;

        internal ElementIntradayTickDataArray(Dictionary<DateTime, Tuple<string, double, int>> ticks, bool includeConditionCodes)
        {
            this._tickData = new List<ElementIntradayTickData>();

            foreach (var dtDate in ticks)
	        {
                ElementIntradayTickData elmFieldData = new ElementIntradayTickData(dtDate.Key, dtDate.Value, includeConditionCodes);
                this._tickData.Add(elmFieldData);
	        }
        }

        public override Element GetValueAsElement(int index) { return (Element)this._tickData[index]; }
        public override object this[int index] { get { return this._tickData[index]; } }

        public override Name Name { get { return new Name("tickData"); } }
        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return this._tickData.Count; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return true; } }
        public override bool IsNull { get { return false; } }
        public override IEnumerable<Element> Elements { get { if (this._tickData.Count < -1) yield return null; } } //This is the only way I can think to have the compiler output "Enumeration yielded no results"

        public override object GetValue(int index)
        {
            return this._tickData[index];
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1}[] = {{{2}", tabs, this.Name, Environment.NewLine);
            foreach (var item in this._tickData)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }
    }
}
