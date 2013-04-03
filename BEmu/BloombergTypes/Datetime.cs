//------------------------------------------------------------------------------
// <copyright project="BEmu" file="BloombergTypes/Datetime.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    public class Datetime : ICloneable
    {
        private DateTime _instance;

        [Flags]
        internal enum DateTimeTypeEnum { neither = 0, date = 1, time = 2, both = 3 }
        private DateTimeTypeEnum _dateTimeType;
        
        #region CONSTRUCTORS
        internal Datetime(DateTime datetime, DateTimeTypeEnum dateTimeType)
        {
            this._instance = datetime;
            this._dateTimeType = dateTimeType;
        }

        public Datetime()
        {
            this._instance = new DateTime();
            this._dateTimeType = DateTimeTypeEnum.neither;
        }

        public Datetime(DateTime datetime)
        {
            this._instance = datetime;
            this._dateTimeType = DateTimeTypeEnum.both;
        }

        public Datetime(Datetime other)
        {
            this._instance = other._instance;
            this._dateTimeType = other._dateTimeType;
        }

        public Datetime(int year, int month, int dayOfMonth)
        {
            this._instance = new DateTime(year, month, dayOfMonth);
            this._dateTimeType = DateTimeTypeEnum.date;
        }

        public Datetime(int hour, int minute, int second, int milliSecond)
        {
            DateTime dtToday = DateTime.Today;
            this._instance = new DateTime(dtToday.Year, dtToday.Month, dtToday.Day, hour, minute, second, milliSecond);
            this._dateTimeType = DateTimeTypeEnum.time;
        }

        public Datetime(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond)
        {
            this._instance = new DateTime(year, month, dayOfMonth, hour, minute, second, milliSecond);
            this._dateTimeType = DateTimeTypeEnum.both;
        }
        #endregion

        #region PROPERTIES
        internal DateTimeTypeEnum DateTimeType { get { return this._dateTimeType; } }

        public int DayOfMonth
        {
            get { return this._instance.Day; }
            set { this._instance = this._instance.AddDays(-this._instance.Day).AddDays(value); }
        }

        public int Hour
        {
            get { return this._instance.Hour; }
            set { this._instance = this._instance.AddHours(-this._instance.Hour).AddHours(value); }
        }

        public int MilliSecond
        {
            get { return this._instance.Millisecond; }
            set { this._instance = this._instance.AddMilliseconds(-this._instance.Millisecond).AddMilliseconds(value); }
        }

        public int Minute
        {
            get { return this._instance.Minute; }
            set { this._instance = this._instance.AddMinutes(-this._instance.Minute).AddMinutes(value); }
        }

        public int Month
        {
            get { return this._instance.Month; }
            set { this._instance = this._instance.AddMonths(-this._instance.Month).AddMonths(value); }
        }

        public int Second
        {
            get { return this._instance.Second; }
            set { this._instance = this._instance.AddSeconds(-this._instance.Second).AddSeconds(value); }
        }

        public int Year
        {
            get { return this._instance.Year; }
            set { this._instance = this._instance.AddYears(-this._instance.Year).AddYears(value); }
        }

        public int Parts { get { throw new NotImplementedException(); } }

        public int TimezoneOffsetMinutes
        {
            get { throw new NotImplementedException(); }
            set { throw new NotImplementedException(); }
        }
        #endregion

        #region METHODS
        public void Clear()
        {
            this._instance = new DateTime();
            this._dateTimeType = DateTimeTypeEnum.neither;
        }

        public object Clone()
        {
            return new Datetime(this);
        }

        public override bool Equals(object obj)
        {
            return this._instance == ((Datetime)obj)._instance;
        }

        public override int GetHashCode()
        {
            throw new IndexOutOfRangeException(); //I don't get it, but calling GetHashCode on a Bloomberg Datetime object seems to always throw an IndexOutOfRangeException.
        }

        public void SetDate(int year, int month, int dayOfMonth)
        {
            this.Year = year;
            this.Month = month;
            this.DayOfMonth = dayOfMonth;
        }

        public void SetDatetime(DateTime datetime)
        {
            this._instance = datetime;
        }

        public void SetDatetime(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond)
        {
            this._instance = new DateTime(year, month, dayOfMonth, hour, minute, second, milliSecond);
        }

        public void SetDatetimeTz(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond, int timezoneOffsetMinutes)
        {
            throw new NotImplementedException();
        }

        public void SetDateTz(int year, int month, int dayOfMonth, int timezoneOffsetMinutes)
        {
            throw new NotImplementedException();
        }

        public void SetTime(int hour, int minute, int second, int milliSecond)
        {
            this.Hour = hour;
            this.Minute = minute;
            this.Second = second;
            this.MilliSecond = milliSecond;
        }

        public void SetTimeTz(int hour, int minute, int second, int milliSecond, int timezoneOffsetMinutes)
        {
            throw new NotImplementedException();
        }

        public override string ToString()
        {
            switch (this._dateTimeType)
            {
                case DateTimeTypeEnum.neither:
                    throw new NotImplementedException();
                case DateTimeTypeEnum.date:
                    return this._instance.ToString("yyyy-MM-dd%K");
                case DateTimeTypeEnum.time:
                    return this._instance.ToString("hh:mm:ss.fff%K");
                case DateTimeTypeEnum.both:
                    return this._instance.ToString("yyyy-MM-dd hh:mm:ss.fff%K");
                default:
                    throw new NotImplementedException();
            }
        }

        public DateTime ToSystemDateTime()
        {
            return this._instance;
        }
        #endregion
    }
}
