//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayTickRequest/IntradayTickRequestElementStringArray.cs" company="Jordan Robinson">
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

    internal class IntradayTickRequestElementStringArray : Element
    {
        private readonly string _elementName;
        private readonly List<string> _values;

        internal IntradayTickRequestElementStringArray(string elementName)
        {
            this._elementName = elementName;
            this._values = new List<string>();
        }

        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return this._values.Count; } }
        public override Name Name { get { return new Name(this._elementName); } }
        public override bool IsArray { get { return true; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsNull { get { return false; } }

        private static readonly string[] _allowedEventTypes = { "TRADE", "BID", "ASK", "BID_BEST", "ASK_BEST", "MID_PRICE", "AT_TRADE", "BEST_BID", "BEST_ASK" };
        internal void AddValue(string value)
        {
            if (IntradayTickRequestElementStringArray._allowedEventTypes.Contains(value, StringComparer.Ordinal))
                this._values.Add(value);
            else
                throw new KeyNotFoundException("Keys are case-sensitive.  Capital letters only."); //yes, the BloombergAPI actually throws a KeyNotFoundException if the user requests a field that isn't supported.
        }

        internal List<string> Values { get { return this._values; } }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1}[] = {{{2}", tabs, this.Name, Environment.NewLine);

            string secs = string.Join(", ", this._values.ToArray());
            result.AppendFormat("{0}{1}{2}{3}", tabs, Types.IndentType.TAB, secs, Environment.NewLine);

            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }
    }
}
