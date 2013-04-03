//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/ElementReferenceInt.cs" company="Jordan Robinson">
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

    internal class ElementReferenceInt : Element
    {
        private readonly int _value;
        private readonly string _name;

        internal ElementReferenceInt(string name, int value)
        {
            this._name = name;
            this._value = value;
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return base.IsComplexType; } }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return base.PrettyPrintHelper(tabIndent, this._value.ToString());
        }

        public override object GetValue()
        {
            return this._value;
        }

        public override int GetValueAsInt32()
        {
            return this._value;
        }

        public override long GetValueAsInt64()
        {
            return this._value;
        }
        
    }
}
