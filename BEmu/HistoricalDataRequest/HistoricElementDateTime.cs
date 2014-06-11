//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="HistoricalDataRequest/HistoricElementDateTime.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.HistoricalDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class HistoricElementDateTime : Element
    {
        private readonly Datetime _date;

        internal HistoricElementDateTime(DateTime date)
        {
            //this._date = new Datetime(date, Datetime.DateTimeTypeEnum.date);
            this._date = new Datetime(date);
        }

        public override Name  Name { get { return new Name("date"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 0; } }
        public override bool IsComplexType { get { return false; } }
        public override bool IsArray { get { return false; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.DATE; } }

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

        internal override StringBuilder PrettyPrint(int tabIndent, bool surroundValueWithQuotes = false)
        {
            return base.PrettyPrintHelper(tabIndent, Types.DisplayFormats.HistoricalOrReferenceRequests.FormatDate(this._date));
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
            return Types.DisplayFormats.HistoricalOrReferenceRequests.FormatDate(this._date);
        }
        
    }
}
