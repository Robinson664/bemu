//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceRequestElementString.cs" company="Jordan Robinson">
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

    internal class ReferenceRequestElementString : Element
    {
        private readonly string _elementName, _value;

        internal ReferenceRequestElementString(string elementName, string value)
        {
            this._elementName = elementName;
            this._value = value;
        }

        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return 1; } }
        public override Name Name { get { return new Name(this._elementName); } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.STRING; } }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1} = {2}{3}", tabs, this._elementName, this._value, Environment.NewLine);

            return result;
        }
    }
}
