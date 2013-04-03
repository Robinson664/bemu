//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/ElementMarketTime.cs" company="Jordan Robinson">
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

    internal class ElementMarketTime : Element
    {
        private readonly Datetime _time;
        private readonly string _name;

        internal ElementMarketTime(string name, DateTime time)
        {
            this._name = name;
            this._time = new Datetime(time, Datetime.DateTimeTypeEnum.time);
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
                    return this._time;
                else
                    throw new IndexOutOfRangeException();
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return base.PrettyPrintHelper(tabIndent, this._time.ToString());
        }

        public override object GetValue()
        {
            return this._time;
        }

        public override Datetime GetValueAsTime()
        {
            return this._time;
        }
    }
}
