//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayBarRequest/IntradayBarElementTickDataArray.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.IntradayBarRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class IntradayBarElementTickDataArray : Element
    {
        private readonly List<IntradayBarElementTickData> _elements;

        internal IntradayBarElementTickDataArray(IEnumerable<IntradayBarTickDataType> bars)
        {
            this._elements = new List<IntradayBarElementTickData>();
            foreach (var item in bars)
            {
                this._elements.Add(new IntradayBarElementTickData(item));
            }
        }

        public override Element GetValueAsElement(int index) { return (Element)this._elements[index]; }
        public override object this[int index] { get { return this._elements[index]; } }

        public override SchemaTypeDefinition TypeDefinition { get { return new SchemaTypeDefinition(this.Datatype, new Name("IntradayBarTickData")); } }
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

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
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
