//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceRequest.cs" company="Jordan Robinson">
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

    internal class ReferenceRequest : Request
    {
        private readonly ReferenceRequestElementStringArray _securities, _fields;
        private readonly ReferenceRequestElementOverrideArray _overrides;

        public ReferenceRequest()
        {
            this._securities = new ReferenceRequestElementStringArray("securities");
            this._fields = new ReferenceRequestElementStringArray("fields");
            this._overrides = new ReferenceRequestElementOverrideArray();
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
            if (this._securities.Name.ToString() == name)
                return this._securities.Values.Any();
            else if (this._fields.Name.ToString() == name)
                return this._fields.Values.Any();
            else if (this._overrides.Name.ToString() == name)
                return this._overrides.NumValues > 0;
            else
                return false;
        }

        public override Element this[string elementName]
        {
            get
            {
                if (this._securities.Name.ToString() == elementName)
                    return this._securities;
                else if (this._fields.Name.ToString() == elementName)
                    return this._fields;
                else if (this._overrides.Name.ToString() == elementName)
                    return this._overrides;
                else
                    throw new NotImplementedException("BEmu.ReferenceDataRequest.RequestReference: public Element this[string elementName] not supported.  ElementName is case-sensitive");
            }
        }

        public override void Append(string name, string elementValue)
        {
            switch (name)
            {
                case "securities":
                    this._securities.AppendValue(elementValue);
                    break;
                case "fields":
                    this._fields.AppendValue(elementValue);
                    break;
                default:
                    throw new ArgumentException(string.Format("BEmu.RequestReference.Append: Element name {0} not supported. Names are case-sensitive", name));
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

            result.AppendLine("}");
            return result.ToString();
        }

    }
}
