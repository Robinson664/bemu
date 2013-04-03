//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/ElementMarketDatetime.cs" company="Jordan Robinson">
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

    internal class ElementMarketDatetime : Element
    {
        private readonly Datetime _datetime;
        private readonly string _name;

        internal ElementMarketDatetime(string name, DateTime datetime)
        {
            this._name = name;
            this._datetime = new Datetime(datetime, Datetime.DateTimeTypeEnum.both);
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsNull { get { return false; } }

        public override object this[int index]
        {
            get
            {
                if (index == 0)
                    return this._datetime;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return base.PrettyPrintHelper(tabIndent, this._datetime.ToString());
        }

        public override object GetValue()
        {
            return this._datetime;
        }

        public override Datetime GetValueAsDatetime()
        {
            return this._datetime;
        }

        public override Datetime GetValueAsDate() //note that this does not truncate the value to date-only, it still returns both the date and the time
        {
            return this._datetime;
        }

        public override Datetime GetValueAsTime() //note that this does not truncate the value to time-only, it still returns both the date and the time
        {
            return this._datetime;
        }
    }
}
