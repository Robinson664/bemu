//------------------------------------------------------------------------------
// <copyright project="BEmu" file="HistoricalDataRequest/ElementHistoricSecurityData.cs" company="Jordan Robinson">
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

    internal class ElementHistoricSecurityData : Element
    {
        private readonly ElementHistoricString _elmSecurityName;
        private readonly ElementHistoricFieldDataArray _elmFieldDataArray;
        private readonly ElementHistoricInt _elmSequenceNumber;
        private readonly ElementHistoricFieldExceptionsArray _elmFieldExceptions;
        private readonly ElementHistoricSecurityError _elmSecError;
        private bool _isSecurityError;

        internal ElementHistoricSecurityData(string securityName, List<string> badFields, Dictionary<DateTime, Dictionary<string, object>> fieldData, int sequenceNumber)
        {
            this._isSecurityError = Types.Rules.IsSecurityError(securityName);

            //remove bad field names from the dictionary
            if (badFields.Count == 0)
                this._elmFieldExceptions = null;
            else
                this._elmFieldExceptions = new ElementHistoricFieldExceptionsArray(badFields);

            this._elmSecurityName = new ElementHistoricString("security", securityName);
            this._elmSequenceNumber = new ElementHistoricInt("sequenceNumber", sequenceNumber);
            if (this._isSecurityError)
            {
                this._elmSecError = new ElementHistoricSecurityError(securityName);
                this._elmFieldDataArray = null;
            }
            else
            {
                this._elmSecError = null;
                this._elmFieldDataArray = new ElementHistoricFieldDataArray(fieldData);
            }
        }

        public override Name Name { get { return new Name("securityData"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return this.Elements.Count(); } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsArray { get { return false; } }
        public override object this[int index] { get { return null; } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._elmSecurityName;
                yield return this._elmSequenceNumber;

                if (this._elmFieldExceptions != null)
                    yield return this._elmFieldExceptions;

                if (this._isSecurityError)
                    yield return this._elmSecError;
                else
                    yield return this._elmFieldDataArray;
            }
        }

        public override object this[string name, int index]
        {
            get
            {
                switch (name.ToUpper())
                {
                    case "FIELDDATA":
                        return this._elmFieldDataArray[index];
                    default:
                        if (index == 0)
                            return this[name];
                        break;
                }

                return base[name, index];
            }
        }

        public override bool HasElement(string name, bool excludeNullElements = false)
        {
            foreach (var item in this.Elements)
            {
                if (item.Name.ToString().Equals(name, StringComparison.OrdinalIgnoreCase))
                    return true;
            }
            return false;
        }

        public override Element GetElement(string name)
        {
            switch (name.ToUpper())
            {
                case "FIELDDATA":
                    if (!this._isSecurityError)
                        return this._elmFieldDataArray;
                    else
                        break;

                case "SECURITY":
                    return this._elmSecurityName;

                case "SEQUENCENUMBER":
                    return this._elmSequenceNumber;

                case "FIELDEXCEPTIONS":
                    return this._elmFieldExceptions;

                case "SECURITYERROR":
                    if (this._isSecurityError) //this element doesn't exist if the security exists
                        return this._elmSecError;
                    else
                        break;
            }
            return base.GetElement(name);
        }

        public override string GetElementAsString(string name)
        {
            if (name.ToUpper() == this._elmSecurityName.Name.ToString().ToUpper())
                return (string)this._elmSecurityName.GetValue();
            else
                return base.GetElementAsString(name);
        }

        public override int GetElementAsInt32(string name)
        {
            if (name.ToUpper() == this._elmSequenceNumber.Name.ToString().ToUpper())
                return (int)this._elmSequenceNumber.GetValue();
            else
                return base.GetElementAsInt32(name);
        }

        public override Element this[string name] { get { return this.GetElement(name); } }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1} = {{{2}", tabs, this.Name, Environment.NewLine);

            result.Append(this._elmSecurityName.PrettyPrint(tabIndent + 1));
            result.Append(this._elmSequenceNumber.PrettyPrint(tabIndent + 1));

            if (this._elmFieldExceptions != null)
                result.Append(this._elmFieldExceptions.PrettyPrint(tabIndent + 1));

            if (this._isSecurityError)
                result.Append(this._elmSecError.PrettyPrint(tabIndent + 1));
            else
                result.Append(this._elmFieldDataArray.PrettyPrint(tabIndent + 1));

            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }
    }
}
