//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayTickRequest/IntradayTickElementDataParent.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.IntradayTickRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class IntradayTickElementDataParent : Element
    {
        private readonly IntradayTickElementDataArray _array;

        internal IntradayTickElementDataParent(SortedDictionary<DateTime, Types.Tuple3<string, double, int>> ticks, bool includeConditionCodes)
        {
            this._array = new IntradayTickElementDataArray(ticks, includeConditionCodes);
        }

        public override SchemaTypeDefinition TypeDefinition { get { return new SchemaTypeDefinition(this.Datatype, new Name("TickData")); } }
        public override Name Name { get { return new Name("tickData"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 1; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsArray { get { return false; } }
        public override bool IsNull { get { return false; } }

        public override IEnumerable<Element> Elements { get { yield return this._array; } }

        public override Element GetElement(string name)
        {
            foreach (var item in this.Elements)
            {
                if (item.Name.ToString() == name)
                    return item;
            }
            return base.GetElement(name);
        }

        public override Element this[string name] { get { return this.GetElement(name); } }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1} = {{{2}", tabs, this.Name, Environment.NewLine);
            result.Append(this._array.PrettyPrint(tabIndent + 1));
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }
    }
}
