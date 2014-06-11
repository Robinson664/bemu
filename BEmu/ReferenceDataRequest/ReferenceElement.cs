//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceElement.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.ReferenceDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ReferenceElement : Element
    {
        private readonly ReferenceElementSecurityDataArray _securities;

        internal ReferenceElement(ReferenceMessage arg)
        {
            this._securities = new ReferenceElementSecurityDataArray((ReferenceElementSecurityDataArray)arg.Elements.First());
        }

        public override int NumElements { get { return 1; } }
        public override int NumValues { get { return 1; } }
        public override Name Name { get { return new Name("securityData"); } }
        public override IEnumerable<Element> Elements { get { yield return this._securities; } }
        public override bool IsNull { get { return false; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return true; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.CHOICE; } }

        public override Element this[string name]
        {
            get
            {
                if (name == this._securities.Name.ToString())
                    return this._securities;
                else
                    return base[name];
            }
        }

        public override object this[string name, int index]
        {
            get
            {
                ReferenceElementSecurityDataArray elm = (ReferenceElementSecurityDataArray)this[name]; //checks name

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

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("ReferenceDataResponse (choice) = {{{0}", Environment.NewLine);
            result.Append(this._securities.PrettyPrint(1));
            result.Append("}" + Environment.NewLine);
            return result;
        }

    }
}
