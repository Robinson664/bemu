//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/ElementReferenceArray.cs" company="Jordan Robinson">
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

    internal class ElementReferenceArray : Element
    {
        protected readonly List<Element> _values;
        private readonly string _name;

        internal ElementReferenceArray(string name, List<Element> elements)
        {
            this._name = name;
            this._values = elements;
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return this._values.Count; } }
        public override int NumElements { get { return 0; } }
        public override bool IsArray { get { return true; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsNull { get { return false; } }

        public override object this[int index] { get { return this._values[index]; } }

        public override object GetValue(int index)
        {
            return this._values[index];
        }

        public override Element GetValueAsElement(int index)
        {
            return this._values[index];
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{2}[] = {{{1}", tabs, Environment.NewLine, this._name);
            foreach (var item in this._values)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);
            return result;
        }

    }
}
