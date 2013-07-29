//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/ElementReferenceSecurityData.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.ReferenceDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementReferenceSecurityData : Element
    {
        private readonly ElementReferenceString _elmSecurityName;
        private readonly ElementReferenceInt _elmSequenceNumber;
        private readonly ElementReferenceFieldData _elmFieldData;
        private readonly ElementReferenceFieldExceptionsArray _elmFieldExceptions;
        private readonly ElementReferenceSecurityError _elmSecError;
        private bool _isSecurityError;

        internal ElementReferenceSecurityData(string securityName, Dictionary<string, object> fieldData, int sequenceNumber)
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
                    this._elmFieldExceptions = new ElementReferenceFieldExceptionsArray(badFields);
            }

            this._elmSecurityName = new ElementReferenceString("security", securityName);
            if (this._isSecurityError)
            {
                this._elmSequenceNumber = new ElementReferenceInt("sequenceNumber", sequenceNumber);
                this._elmSecError = new ElementReferenceSecurityError(securityName);
                this._elmFieldData = new ElementReferenceFieldData(new Dictionary<string, object>());
            }
            else
            {
                this._elmSequenceNumber = new ElementReferenceInt("sequenceNumber", sequenceNumber);
                this._elmSecError = null;
                this._elmFieldData = new ElementReferenceFieldData(fieldData);
            }
        }

        public override int NumElements { get { return this.Elements.Count(); } }
        public override int NumValues { get { return 0; } }
        public override Name Name { get { return new Name("securityData"); } }

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
            if (name.ToUpper() == this._elmSecurityName.Name.ToString().ToUpper())
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
                switch (name.ToUpper())
                {
                    case "FIELDDATA":
                        return this._elmFieldData;
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
                return base[name];
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

        public override object this[string name, int index]
        {
            get
            {
                string strName = name.ToUpper();
                if (name == this._elmFieldData.Name.ToString().ToUpper())
                    return base[name, index];
                else if (index == 0)
                    return this[name].GetValue();
                else
                    return null;
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
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
