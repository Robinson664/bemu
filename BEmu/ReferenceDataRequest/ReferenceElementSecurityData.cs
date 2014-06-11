//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceElementSecurityData.cs" company="Jordan Robinson">
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

    internal class ReferenceElementSecurityData : Element
    {
        private readonly ReferenceElementString _elmSecurityName;
        private readonly ReferenceElementInt _elmSequenceNumber;
        private readonly ReferenceElementFieldData _elmFieldData;
        private readonly ReferenceElementFieldExceptionsArray _elmFieldExceptions;
        private readonly ReferenceElementSecurityError _elmSecError;
        private readonly bool _isSecurityError;

        internal ReferenceElementSecurityData(string securityName, Dictionary<string, object> fieldData, int sequenceNumber)
        {
            this._isSecurityError = Types.Rules.IsSecurityError(securityName);

            { //find bad field names
                List<string> badFields = new List<string>();
                foreach (var item in fieldData)
                {
                    if (Types.Rules.IsBadField(item.Key))
                        badFields.Add(item.Key);
                }

                //remove bad field names from the dictionary
                foreach (var item in badFields)
                {
                    fieldData.Remove(item);
                }

                if (badFields.Count == 0)
                    this._elmFieldExceptions = null;
                else
                    this._elmFieldExceptions = new ReferenceElementFieldExceptionsArray(badFields);
            }

            this._elmSecurityName = new ReferenceElementString("security", securityName);
            if (this._isSecurityError)
            {
                this._elmSequenceNumber = new ReferenceElementInt("sequenceNumber", sequenceNumber);
                this._elmSecError = new ReferenceElementSecurityError(securityName);
                this._elmFieldData = new ReferenceElementFieldData(new Dictionary<string, object>());
            }
            else
            {
                this._elmSequenceNumber = new ReferenceElementInt("sequenceNumber", sequenceNumber);
                this._elmSecError = null;
                this._elmFieldData = new ReferenceElementFieldData(fieldData);
            }
        }

        public override int NumElements { get { return this.Elements.Count(); } }
        public override int NumValues { get { return 0; } }
        public override Name Name { get { return new Name("securityData"); } }
        public override SchemaTypeDefinition TypeDefinition { get { return new SchemaTypeDefinition(this.Datatype, new Name("ReferenceSecurityData")); } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._elmSecurityName;

                if (this._elmFieldExceptions != null)
                    yield return this._elmFieldExceptions;

                if (this._isSecurityError)
                    yield return this._elmSecError;

                yield return this._elmSequenceNumber;
                yield return this._elmFieldData; 
            }
        }

        public override string GetElementAsString(string name)
        {
            if (name == this._elmSecurityName.Name.ToString())
                return (string)this._elmSecurityName.GetValue();
            else
                return base.GetElementAsString(name);
        }

        public override object this[int index] { get { return null; } }

        public override Element GetElement(string name)
        {
            return this[name];
        }

        public override Element this[string name]
        {
            get
            {
                switch (name)
                {
                    case "fieldData":
                        if (!this._isSecurityError)
                            return this._elmFieldData;
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
                return base[name];
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

        public override object this[string name, int index]
        {
            get
            {
                if (name == this._elmFieldData.Name.ToString())
                    return base[name, index];
                else if (index == 0)
                    return this[name].GetValue();
                else
                    return null;
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1} = {{{2}", tabs, this.Name, Environment.NewLine);
            result.Append(this._elmSecurityName.PrettyPrint(tabIndent + 1));

            if(this._elmFieldExceptions != null)
                result.Append(this._elmFieldExceptions.PrettyPrint(tabIndent + 1));

            result.Append(this._elmSequenceNumber.PrettyPrint(tabIndent + 1));

            if (this._isSecurityError)
                result.Append(this._elmSecError.PrettyPrint(tabIndent + 1));
            else
                result.Append(this._elmFieldData.PrettyPrint(tabIndent + 1));

            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }
    }
}
