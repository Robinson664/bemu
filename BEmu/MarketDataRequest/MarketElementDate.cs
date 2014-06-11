//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="MarketDataRequest/MarketElementDate.cs" company="Jordan Robinson">
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

    internal class MarketElementDate : Element
    {
        private readonly Datetime _date;
        private readonly string _name;

        internal MarketElementDate(string name, DateTime date)
        {
            this._name = name;
            //this._date = new Datetime(date, Datetime.DateTimeTypeEnum.date);
            this._date = new Datetime(date);
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsNull { get { return false; } }
        public override bool IsArray { get { return false; } }
        public override bool IsComplexType { get { return false; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.DATE; } }

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

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
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
