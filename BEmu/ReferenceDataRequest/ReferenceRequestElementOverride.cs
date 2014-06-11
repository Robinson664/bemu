//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceRequestElementOverride.cs" company="Jordan Robinson">
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

    internal class ReferenceRequestElementOverride : Element
    {
        private ReferenceElementString _fieldId;
        private ReferenceElementObject _value;

        internal ReferenceRequestElementOverride()
        {
            this._fieldId = new ReferenceElementString("fieldId", "");
            this._value = new ReferenceElementObject("value", "");
        }

        public override void SetElement(string name, object value)
        {
            switch (name)
            {
                case "fieldId":
                    this._fieldId = new ReferenceElementString(name, value.ToString());
                    break;
                case "value":
                    this._value = new ReferenceElementObject(name, value);
                    break;
                default:
                    throw new ArgumentException();
            }            
        }

        public override Name Name { get { return new Name("overrides"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 2; } }
        public override object this[int index] { get { return null; } }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1} = {{{2}", tabs, this.Name, Environment.NewLine);
            result.Append(this._fieldId.PrettyPrint(tabIndent + 1, surroundValueWithQuotes));
            result.Append(this._value.PrettyPrint(tabIndent + 1, surroundValueWithQuotes));
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._fieldId;
                yield return this._value;
            }
        }
        
        public override Element this[string name]
        {
            get
            {
                switch (name)
                {
                    case "fieldId":
                        return this._fieldId;
                    case "value":
                        return this._value;
                }
                return base[name];
            }
        }

        public override object this[string name, int index]
        {
            get
            {
                if (index == 0)
                    return this[name].GetValue();
                return base[name, index];
            }
        }

    }
}
