//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="MarketDataRequest/MarketElementDouble.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.MarketDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class MarketElementDouble : Element
    {
        private readonly double _value;
        private readonly string _name;

        internal MarketElementDouble(string name, double value)
        {
            this._name = name;
            this._value = value;
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsNull { get { return false; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return base.IsComplexType; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.FLOAT64; } }

        public override object this[int index]
        {
            get
            {
                if (index == 0)
                    return this._value;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            return base.PrettyPrintHelper(tabIndent, Types.DisplayFormats.FormatNumberNoSeparators(this._value, 2));
        }

        public override object GetValue()
        {
            return this._value;
        }

        public override double GetValueAsFloat64()
        {
            return this._value;
        }
    }
}
