//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayTickRequest/ElementIntradayTickSecurityError.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayTickRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementIntradayTickResponseError : Element
    {
        private readonly ElementIntradayTickString _source, _category, _message, _subCategory;
        private readonly ElementIntradayTickInt _code;

        internal ElementIntradayTickResponseError()
        {
            int code = Types.RandomDataGenerator.RandomInt(99);
            string sourceGibberish = Types.RandomDataGenerator.RandomString(5).ToLower();

            this._source = new ElementIntradayTickString("source", string.Format("{0}::{1}{2}", code, sourceGibberish, Types.RandomDataGenerator.RandomInt(99)));
            this._code = new ElementIntradayTickInt("code", code);
            this._category = new ElementIntradayTickString("category", "BAD_SEC");
            this._message = new ElementIntradayTickString("message", string.Format("Unknown/Invalid security [nid:{0}]", code));
            this._subCategory = new ElementIntradayTickString("subcategory", "INVALID_SECURITY");
        }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._source;
                yield return this._code;
                yield return this._category;
                yield return this._message;
                yield return this._subCategory;
            }
        }

        public override Name Name { get { return new Name("responseError"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 5; } }

        public override string GetElementAsString(string name)
        {
            return this[name].GetValueAsString();
        }

        public override int GetElementAsInt32(string name)
        {
            return this[name].GetValueAsInt32();
        }

        public override Element GetElement(string name)
        {
            return this[name];
        }

        public override object GetValue()
        {
            return null;
        }

        public override object GetValue(int index)
        {
            return null;
        }

        public override bool IsArray
        {
            get
            {
                return false;
            }
        }

        public override bool IsComplexType
        {
            get
            {
                return true;
            }
        }

        public override bool IsNull
        {
            get
            {
                return false;
            }
        }

        public override object this[int index]
        {
            get
            {
                return null;
            }
        }

        public override Element this[string name]
        {
            get
            {
                string strName = name.ToUpper();
                foreach (var item in this.Elements)
                {
                    if (item.Name.ToString().ToUpper() == strName)
                        return item;
                }
                return base[name];
            }
        }

        public override object this[string name, int index]
        {
            get
            {
                if (index == 0)
                    return this[name];
                else
                    throw new IndexOutOfRangeException();
            }
        }

        public override bool HasElement(string name, bool excludeNullElements = false)
        {
            foreach (var item in this.Elements)
            {
                if (item.Name.ToString().ToUpper() == name.ToUpper())
                    return true;
            }
            return false;
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}responseError = {{{1}", tabs, Environment.NewLine);
            foreach (var item in this.Elements)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);
            return result;
        }

    }
}
