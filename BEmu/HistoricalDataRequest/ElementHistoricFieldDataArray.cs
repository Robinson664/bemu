//------------------------------------------------------------------------------
// <copyright project="BEmu" file="HistoricalDataRequest/ElementHistoricFieldDataArray.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.HistoricalDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementHistoricFieldDataArray : Element
    {
        private readonly List<ElementHistoricFieldData> _fieldData;

        internal ElementHistoricFieldDataArray(Dictionary<DateTime, Dictionary<string, object>> fieldData)
        {
            this._fieldData = new List<ElementHistoricFieldData>();

            foreach (var dtDate in fieldData)
	        {
                ElementHistoricFieldData elmFieldData = new ElementHistoricFieldData(dtDate.Key, dtDate.Value);
                this._fieldData.Add(elmFieldData);
	        }
        }

        public override Element GetValueAsElement(int index) { return this._fieldData[index]; }
        public override object this[int index] { get { return this._fieldData[index]; } }

        public override Name Name { get { return new Name("fieldData"); } }
        public override int NumElements { get { return 0; } }
        public override int NumValues { get { return this._fieldData.Count; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return true; } }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1}[] = {{{2}", tabs, this.Name, Environment.NewLine);
            foreach (var item in this._fieldData)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }
    }
}
