//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="HistoricalDataRequest/HistoricElementSecurityData.cs" company="Jordan Robinson">
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

    internal class HistoricElementSecurityData : Element
    {
        private readonly HistoricElementString _elmSecurityName;
        private readonly HistoricElementFieldDataArray _elmFieldDataArray;
        private readonly HistoricElementInt _elmSequenceNumber;
        private readonly HistoricElementFieldExceptionsArray _elmFieldExceptions;
        private readonly HistoricElementSecurityError _elmSecError;
        private readonly bool _isSecurityError;

        internal HistoricElementSecurityData(string securityName, List<string> badFields, Dictionary<DateTime, Dictionary<string, object>> fieldData, int sequenceNumber)
        {
            this._isSecurityError = Types.Rules.IsSecurityError(securityName);

            //remove bad field names from the dictionary
            if (badFields.Count == 0)
                this._elmFieldExceptions = null;
            else
                this._elmFieldExceptions = new HistoricElementFieldExceptionsArray(badFields);

            this._elmSecurityName = new HistoricElementString("security", securityName);
            this._elmSequenceNumber = new HistoricElementInt("sequenceNumber", sequenceNumber);
            if (this._isSecurityError)
            {
                this._elmSecError = new HistoricElementSecurityError(securityName);
                this._elmFieldDataArray = null;
            }
            else
            {
                this._elmSecError = null;
                this._elmFieldDataArray = new HistoricElementFieldDataArray(fieldData);
            }
        }

        public override Name Name { get { return new Name("securityData"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return this.Elements.Count(); } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsArray { get { return false; } }
        public override object this[int index] { get { return null; } }

        public override SchemaTypeDefinition TypeDefinition { get { return new SchemaTypeDefinition(this.Datatype, new Name("HistoricalDataTable")); } }

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
                switch (name)
                {
                    case "fieldData":
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
                if (item.Name.ToString().Equals(name))
                    return true;
            }
            return false;
        }

        public override Element GetElement(string name)
        {
            switch (name) //case-sensitive
            {
                case "fieldData":
                    if (!this._isSecurityError)
                        return this._elmFieldDataArray;
                    else
                        break;

                case "security":
                    return this._elmSecurityName;

                case "sequenceNumber":
                    return this._elmSequenceNumber;

                case "fieldExceptions":
                    if (this._elmFieldExceptions == null)
                        break;
                    else
                        return this._elmFieldExceptions;

                case "securityError":
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

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
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
