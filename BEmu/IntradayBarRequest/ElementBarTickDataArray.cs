//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayBarRequest/ElementBarTickDataArray.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayBarRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementBarTickDataArray : Element
    {
        private readonly List<ElementBarTickData> _elements;

        internal ElementBarTickDataArray(IEnumerable<BarTickDataType> bars)
        {
            this._elements = new List<ElementBarTickData>();
            foreach (var item in bars)
            {
                this._elements.Add(new ElementBarTickData(item));
            }
        }

        public override Element GetValueAsElement(int index) { return (Element)this._elements[index]; }
        public override object this[int index] { get { return this._elements[index]; } }

        public override Name Name { get { return new Name("barTickData"); } }
        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return this._elements.Count; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return true; } }
        public override bool IsNull { get { return false; } }
        public override IEnumerable<Element> Elements { get { if (this._elements.Count < -1) yield return null; } } //This is the only way I can think to have the compiler output "Enumeration yielded no results"

        public override object GetValue(int index)
        {
            return this._elements[index];
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1}[] = {{{2}", tabs, this.Name, Environment.NewLine);
            foreach (var item in this._elements)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }



    }
}
