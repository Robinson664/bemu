//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/ElementReferenceSecurityDataArray.cs" company="Jordan Robinson">
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

    internal class ElementReferenceSecurityDataArray : Element
    {
        private readonly List<Element> _securities;

        internal ElementReferenceSecurityDataArray(Dictionary<string, Dictionary<string, object>> securities)
        {
            this._securities = new List<Element>();

            foreach (var item in securities)
            {
                ElementReferenceSecurityData secData = new ElementReferenceSecurityData(item.Key, item.Value, this._securities.Count);
                this._securities.Add(secData);
            }
        }

        internal ElementReferenceSecurityDataArray(ElementReferenceSecurityDataArray arg) //copy constructor
        {
            this._securities = new List<Element>(arg._securities);
        }

        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return this._securities.Count; } }
        public override Name Name { get { return new Name("securityData"); } }
        public override IEnumerable<Element> Elements { get { return this._securities; } }

        public override bool HasElement(string name, bool excludeNullElements = false)
        {
            foreach (var item in this._securities)
            {
                if (item.Name.ToString().Equals(name, StringComparison.OrdinalIgnoreCase))
                    return true;
            }
            return false;
        }

        public override Element GetValueAsElement(int index)
        {
            return this._securities[index];
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1}[] = {{{2}", tabs, this.Name, Environment.NewLine);
            foreach (var item in this._securities)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }

    }
}
