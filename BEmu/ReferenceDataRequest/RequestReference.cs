//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/RequestReference.cs" company="Jordan Robinson">
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

    internal class RequestReference : Request
    {
        private readonly RequestReferenceElementStringArray _securities, _fields;
        private readonly RequestReferenceElementOverrideArray _overrides;

        public RequestReference()
        {
            this._securities = new RequestReferenceElementStringArray("securities");
            this._fields = new RequestReferenceElementStringArray("fields");
            this._overrides = new RequestReferenceElementOverrideArray();
        }

        internal List<string> Securities { get { return this._securities.Values; } }
        internal List<string> Fields { get { return this._fields.Values; } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._securities;
                yield return this._fields;

                if (this._overrides.NumValues > 0)
                    yield return this._overrides;
            }
        }

        public override bool HasElement(string name)
        {
            string strName = name.ToUpper();

            if (this._securities.Name.ToString().ToUpper() == strName)
                return this._securities.Values.Any();
            else if (this._fields.Name.ToString().ToUpper() == strName)
                return this._fields.Values.Any();
            else if (this._overrides.Name.ToString().ToUpper() == strName)
                return this._overrides.NumValues > 0;
            else
                return false;
        }

        public override Element this[string elementName]
        {
            get
            {
                string strName = elementName.ToUpper();

                if (this._securities.Name.ToString().ToUpper() == strName)
                    return this._securities;
                else if (this._fields.Name.ToString().ToUpper() == strName)
                    return this._fields;
                else if (this._overrides.Name.ToString().ToUpper() == strName)
                    return this._overrides;
                else
                    throw new NotImplementedException("BEmu.ReferenceDataRequest.RequestReference: public Element this[string elementName] not supported");
            }
        }

        public override void Append(string name, string elementValue)
        {
            switch (name.ToLower())
            {
                case "securities":
                    this._securities.AddValue(elementValue);
                    break;
                case "fields":
                    this._fields.AddValue(elementValue);
                    break;
                default:
                    throw new ArgumentException(string.Format("BEmu.RequestReference.Append: Element name {0} not supported", name));
            }
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("ReferenceDataRequest = {{{0}", Environment.NewLine);

            if (this._securities.NumValues > 0)
                result.Append(this._securities.PrettyPrint(1));

            if (this._fields.NumValues > 0)
                result.Append(this._fields.PrettyPrint(1));

            if (this._overrides.NumValues > 0)
                result.Append(this._overrides.PrettyPrint(1));

            result.Append("}");

            return result.ToString();
        }

    }
}
