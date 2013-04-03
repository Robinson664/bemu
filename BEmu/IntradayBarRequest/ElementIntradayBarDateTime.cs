//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayBarRequest/ElementIntradayBarDateTime.cs" company="Jordan Robinson">
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

    internal class ElementIntradayBarDateTime : Element
    {
        private readonly Datetime _date;

        internal ElementIntradayBarDateTime(DateTime date)
        {
            this._date = new Datetime(date, Datetime.DateTimeTypeEnum.both);
        }

        public override Name  Name { get { return new Name("time"); } }
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
                    return this._date;
                else
                    return base[index];
            }
        }

        public override object GetValue()
        {
            return this._date;
        }

        public override object GetValue(int index)
        {
            if (index == 0)
                return this.GetValue();
            else 
                return base.GetValue(index);
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            return base.PrettyPrintHelper(tabIndent, this._date.ToSystemDateTime().ToString("yyyy-MM-ddTHH:mm:ss.fff"));
        }

        public override Datetime GetValueAsDate()
        {
            return this._date;
        }

        public override Datetime GetValueAsDate(int index)
        {
            if (index == 0)
                return this.GetValueAsDate();
            else
                return base.GetValueAsDate(index);
        }

        public override Datetime GetValueAsDatetime(int index)
        {
            if (index == 0)
                return this.GetValueAsDatetime();
            else
                return base.GetValueAsDatetime(index);
        }

        public override Datetime GetValueAsDatetime()
        {
            return this._date;
        }

        public override Datetime GetValueAsTime()
        {
            return this._date;
        }

        public override Datetime GetValueAsTime(int i)
        {
            if (i == 0)
                return this.GetValueAsTime();
            else
                return base.GetValueAsTime(i);
        }

        public override string GetValueAsString()
        {
            return this._date.ToString();
        }

        public override string GetValueAsString(int i)
        {
            if (i == 0)
                return this.GetValueAsString();
            else
                return base.GetValueAsString(i);
        }
    }
}
