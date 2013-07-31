//------------------------------------------------------------------------------
// <copyright project="BEmu" file="HistoricalDataRequest/ElementHistoricFieldExceptionsArray.cs" company="Jordan Robinson">
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

    internal class ElementHistoricFieldExceptionsArray : Element
    {
        private readonly List<ElementHistoricFieldExceptions> _exceptions;

        public ElementHistoricFieldExceptionsArray(List<string> badFields)
        {
            this._exceptions = new List<ElementHistoricFieldExceptions>(badFields.Count);
            foreach (var item in badFields)
            {
                this._exceptions.Add(new ElementHistoricFieldExceptions(item));
            }
        }

        public override Name Name { get { return new Name("fieldExceptions"); } }
        public override int NumValues { get { return this._exceptions.Count; } }
        public override int NumElements { get { return 0; } }
        public override bool IsArray { get { return true; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsNull { get { return false; } }

        public override object this[int index] { get { return this._exceptions[index]; } }

        public override object GetValue(int index)
        {
            return this._exceptions[index];
        }

        public override Element GetValueAsElement(int index)
        {
            return this._exceptions[index];
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{2}[] = {{{1}", tabs, Environment.NewLine, this.Name);
            foreach (var item in this._exceptions)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);
            return result;
        }



    }
}
