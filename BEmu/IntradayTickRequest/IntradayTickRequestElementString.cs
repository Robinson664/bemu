//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayTickRequest/IntradayTickRequestElementString.cs" company="Jordan Robinson">
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

    internal class IntradayTickRequestElementString : Element
    {
        private readonly string _elementName, _value;

        internal IntradayTickRequestElementString(string elementName, string value)
        {
            this._elementName = elementName;
            this._value = value;
        }

        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return 1; } }
        public override Name Name { get { return new Name(this._elementName); } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.STRING; } }

        internal string Security { get { return this._value; } }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            StringBuilder result = new StringBuilder();

            string tabs = Types.IndentType.Indent(tabIndent);
            string valueToUse = surroundValueWithQuotes ? string.Format("\"{0}\"", this._value) : this._value;

            result.AppendFormat("{0}{1} = {2}{3}", tabs, this._elementName, valueToUse, Environment.NewLine);

            return result;
        }
    }
}
