//------------------------------------------------------------------------------
// <copyright project="BEmu" file="HistoricalDataRequest/ElementHistoricDouble.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.HistoricalDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementHistoricDouble : Element
    {
        private readonly double _value;
        private readonly string _name;

        internal ElementHistoricDouble(string name, double value)
        {
            this._name = name;
            this._value = value;
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return false; } }

        public override object this[int index]
        {
            get
            {
                if (index == 0)
                    return this._value;
                else
                    return base[index];
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return base.PrettyPrintHelper(tabIndent, this._value.ToString());
        }

        public override object GetValue()
        {
            return this._value;
        }

        public override double GetValueAsFloat64()
        {
            return this._value;
        }

        public override int GetValueAsInt32()
        {
            return (int)this._value;
        }

        public override long GetValueAsInt64()
        {
            return (long)this._value;
        }

        public override string GetValueAsString()
        {
            return this._value.ToString();
        }
                
    }
}
