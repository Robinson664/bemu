//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="HistoricalDataRequest/HistoricRequestElementDate.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.HistoricalDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class HistoricRequestElementDate : Element
    {
        private readonly DateTime? _instance;
        private readonly string _elementName;

        internal HistoricRequestElementDate(string elementName)
        {
            this._instance = null;
            this._elementName = elementName;
        }

        internal HistoricRequestElementDate(string elementName, DateTime date)
        {
            this._instance = date;
            this._elementName = elementName;
        }

        internal HistoricRequestElementDate(string elementName, Datetime date)
        {
            this._instance = date.ToSystemDateTime();
            this._elementName = elementName;
        }

        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return 1; } }
        public override Name Name { get { return new Name(this._elementName); } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.STRING; } }

        //I can't override GetElementAsDatetime here because the Bloomberg Request object stores dates as strings, not Datetimes.  You can't convert the string to a Datetime
        internal DateTime? GetDate { get { return this._instance; } }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            if (this._instance.HasValue)
                result.AppendFormat("{0}{1} = \"{2}\"{3}", tabs, this._elementName, this._instance.Value.ToString("yyyyMMdd"), Environment.NewLine);

            return result;
        }

    }
}
