//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayBarRequest/ElementIntradayBarLong.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayBarRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementIntradayBarLong : Element
    {
        private readonly long _value;
        private readonly string _name;

        internal ElementIntradayBarLong(string name, long value)
        {
            this._name = name;
            this._value = value;
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return false; } }
        public override bool IsNull { get { return false; } }
        public override IEnumerable<Element> Elements { get { if (this.NumValues < -1) yield return null; } } //This is the only way I can think to have the compiler output "Enumeration yielded no results"
        public override bool HasElement(string name, bool excludeNullElements = false) { return false; }

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

        public override object GetValue(int index)
        {
            if (index == 0)
                return this.GetValue();
            else
                return base.GetValue(index);
        }

        public override long GetValueAsInt64()
        {
            return (long)this._value;
        }

        public override long GetValueAsInt64(int index)
        {
            if (index == 0)
                return this.GetValueAsInt64();
            else
                return base.GetValueAsInt64(index);
        }
    }
}
