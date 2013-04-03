//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/ElementReference.cs" company="Jordan Robinson">
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

    internal class ElementReference : Element
    {
        private readonly ElementReferenceSecurityDataArray _securities;

        internal ElementReference(MessageReference arg)
        {
            this._securities = new ElementReferenceSecurityDataArray((ElementReferenceSecurityDataArray)arg.Elements.First());
        }

        public override int NumElements { get { return 1; } }
        public override int NumValues { get { return 1; } }
        public override Name Name { get { return new Name("securityData"); } }
        public override IEnumerable<Element> Elements { get { yield return this._securities; } }
        public override bool IsNull { get { return false; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return true; } }

        public override Element this[string name]
        {
            get
            {
                if (name.ToUpper() == this._securities.Name.ToString().ToUpper())
                    return this._securities;
                else
                    return base[name];
            }
        }

        public override object this[string name, int index]
        {
            get
            {
                ElementReferenceSecurityDataArray elm = (ElementReferenceSecurityDataArray)this[name]; //checks name

                int elmIndex = 0;
                foreach (var item in elm.Elements)
                {
                    if (elmIndex == index)
                        return item;
                    elmIndex++;
                }

                return base[name, index];
            }
        }

        public override Element GetElement(string name)
        {
            return this[name];
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("ReferenceDataResponse (choice) = {{{0}", Environment.NewLine);
            result.Append(this._securities.PrettyPrint(1));
            result.Append("}" + Environment.NewLine);
            return result;
        }

    }
}
