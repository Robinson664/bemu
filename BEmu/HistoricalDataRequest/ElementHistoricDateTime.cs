//------------------------------------------------------------------------------
// <copyright project="BEmu" file="HistoricalDataRequest/ElementHistoricDateTime.cs" company="Jordan Robinson">
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

    internal class ElementHistoricDateTime : Element
    {
        private readonly Datetime _date;

        internal ElementHistoricDateTime(DateTime date)
        {
            this._date = new Datetime(date, Datetime.DateTimeTypeEnum.date);
        }

        public override Name  Name { get { return new Name("date"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return false; } }

        public override object this[int index]
        {
            get
            {
                if (index == 0)
                    return this._date;
                else
                    return base[index];
            }
        }

        public override object GetValue()
        {
            return this._date;
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return base.PrettyPrintHelper(tabIndent, this._date.ToSystemDateTime().ToString("yyyy-MM-dd"));
        }

        public override Datetime GetValueAsDate()
        {
            return this._date;
        }

        public override Datetime GetValueAsDatetime()
        {
            return this._date;
        }

        public override Datetime GetValueAsTime()
        {
            return this._date;
        }

        public override string GetValueAsString()
        {
            return this._date.ToSystemDateTime().ToString("yyyy-MM-dd");
        }
        
    }
}
