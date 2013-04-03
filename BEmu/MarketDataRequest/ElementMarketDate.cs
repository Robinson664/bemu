//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/ElementMarketDate.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.MarketDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementMarketDate : Element
    {
        private readonly Datetime _date;
        private readonly string _name;

        internal ElementMarketDate(string name, DateTime date)
        {
            this._name = name;
            this._date = new Datetime(date, Datetime.DateTimeTypeEnum.date);
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsNull { get { return false; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return base.IsComplexType; } }

        public override object this[int index]
        {
            get
            {
                if (index == 0)
                    return this._date;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return base.PrettyPrintHelper(tabIndent, this._date.ToString());
        }

        public override object GetValue()
        {
            return this._date;
        }

        public override Datetime GetValueAsDate()
        {
            return this._date;
        }
    }
}
