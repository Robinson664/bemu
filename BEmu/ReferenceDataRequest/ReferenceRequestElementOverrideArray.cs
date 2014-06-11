//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceRequestElementOverrideArray.cs" company="Jordan Robinson">
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

    internal class ReferenceRequestElementOverrideArray : Element
    {
        private readonly List<ReferenceRequestElementOverride> _overrides;

        internal ReferenceRequestElementOverrideArray()
        {
            this._overrides = new List<ReferenceRequestElementOverride>();
        }

        public override Name Name { get { return new Name("overrides"); } }
        public override int NumValues { get { return this._overrides.Count; } }
        public override int NumElements { get { return 0; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return true; } }
        public override bool IsNull { get { return false; } }
        public override object this[int index] { get { return this._overrides[index]; } }

        public override object GetValue()
        {
            return this.GetValue(0);
        }

        public override object GetValue(int index)
        {
            return this._overrides[index];
        }

        public override Element GetValueAsElement()
        {
            return this.GetValueAsElement(0);
        }

        public override Element GetValueAsElement(int index)
        {
            return (Element)this.GetValue(index);
        }

        public override Element AppendElement()
        {
            ReferenceRequestElementOverride result = new ReferenceRequestElementOverride();
            this._overrides.Add(result);
            return result;
        }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1}[] = {{{2}", tabs, this.Name, Environment.NewLine);
            foreach (var item in this._overrides)
            {
                result.Append(item.PrettyPrint(tabIndent + 1, true));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }

    }
}
