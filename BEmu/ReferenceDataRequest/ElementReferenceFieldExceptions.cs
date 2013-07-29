//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/ElementReferenceFieldExceptions.cs" company="Jordan Robinson">
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

    internal class ElementReferenceFieldExceptions : Element
    {
        private readonly ElementReferenceString _fieldId;
        private readonly ElementReferenceErrorInfo _errorInfo;

        public ElementReferenceFieldExceptions(string badField)
        {
            this._fieldId = new ElementReferenceString("fieldId", badField);
            this._errorInfo = new ElementReferenceErrorInfo();
        }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._fieldId;
                yield return this._errorInfo;
            }
        }

        public override Name Name { get { return new Name("fieldExceptions"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 2; } }

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

            result.AppendFormat("{0}fieldExceptions = {{{1}", tabs, Environment.NewLine);
            foreach (var item in this.Elements)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);
            return result;
        }






    }
}
