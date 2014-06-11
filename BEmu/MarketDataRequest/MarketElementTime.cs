//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="MarketDataRequest/MarketElementTime.cs" company="Jordan Robinson">
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

    internal class MarketElementTime : Element
    {
        private readonly Datetime _time;
        private readonly string _name;

        internal MarketElementTime(string name, DateTime time)
        {
            this._name = name;
            //this._time = new Datetime(time, Datetime.DateTimeTypeEnum.time);
            this._time = new Datetime(time);
        }

        public override Name Name { get { return new Name(this._name); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsNull { get { return false; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.TIME; } }

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

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            return base.PrettyPrintHelper(tabIndent, Types.DisplayFormats.MarketDataRequests.FormatDateZone(this._time));
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
