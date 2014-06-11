//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ReferenceDataRequest/ReferenceElementDateTime.cs" company="Jordan Robinson">
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

    internal class ReferenceElementDateTime : Element
    {
        private readonly Datetime _value;
        private readonly string _name;

        internal ReferenceElementDateTime(string name, DateTime value)
        {
            this._name = name;
            //this._value = new Datetime(value, Datetime.DateTimeTypeEnum.date);
            this._value = new Datetime(value);
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return false; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.DATE; } }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            return base.PrettyPrintHelper(tabIndent, this._value.ToString());
        }

        public override object GetValue()
        {
            return this._value;
        }

        public override Datetime GetValueAsDate()
        {
            return this._value;
        }

        public override Datetime GetValueAsDatetime()
        {
            return this._value;
        }

        public override Datetime GetValueAsTime()
        {
            return this._value;
        }

    }
}
