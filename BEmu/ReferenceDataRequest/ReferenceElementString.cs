//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceElementString.cs" company="Jordan Robinson">
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

    internal class ReferenceElementString : Element
    {
        private readonly string _name, _value;

        internal ReferenceElementString(string name, string value)
        {
            this._name = name;
            this._value = value;
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return false; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.STRING; } }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            string valueToUse = surroundValueWithQuotes ? string.Format("\"{0}\"", this._value) : this._value;
            return base.PrettyPrintHelper(tabIndent, valueToUse);
        }

        public override object GetValue()
        {
            return this._value;
        }

        public override string GetValueAsString()
        {
            return this._value;
        }

        public override string GetValueAsString(int index)
        {
            if (index == 0)
                return this._value;
            else
                return base.GetValueAsString(index);
        }
        
    }
}
