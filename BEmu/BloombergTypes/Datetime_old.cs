//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/Datetime.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

//This is my own implementation of Datetime

//namespace Bloomberglp.Blpapi
//{
//    using System;
//    using System.Collections.Generic;
//    using System.Linq;
//    using System.Text;

//    /// <summary>
//    /// The BB API supports invalid dates (e.g., January 32, 2014)
//    ///   Since I'm using C#'s DateTime internally, and a C# DateTime doesn't support invalid dates, the emulator does not support invalid dates.
//    ///   The code will throw an Argument Out of Range Exception if given an invalid date.
//    /// </summary>
//    public class Datetime : ICloneable
//    {
//        private DateTime _instance;

//        public const byte TIME_ZONE_OFFSET = 1;
//        public const byte MILLISECOND = 2;
//        public const byte SECOND = 4;
//        public const byte MINUTE = 8;
//        public const byte HOUR = 16;

//        /// <summary>
//        /// Hour | Minute | Second
//        /// </summary>
//        public const short TIME = 28;

//        /// <summary>
//        /// Hour | Minute | Second | Millisecond
//        /// </summary>
//        public const short TIMEMILLI = 30;

//        public const byte DAY_OF_MONTH = 32;
//        public const byte MONTH = 64;
//        public const short YEAR = 128;

//        /// <summary>
//        /// Year | Month | DayOfMonth
//        /// </summary>
//        public const short DATE = 224;

//        /// <summary>
//        /// Year | Month | DayOfMonth | Hour | Minute | Second | Millisecond
//        /// </summary>
//        internal const int DATE_TIME = 254;

//        [Flags]
//        internal enum DateTimeTypeEnum { neither = 0, date = Datetime.DATE, time = Datetime.TIMEMILLI, both = Datetime.DATE_TIME }
//        private DateTimeTypeEnum _dateTimeType;
//        private void SetDateTimeType(DateTimeTypeEnum dateTimeType)
//        {
//            this._dateTimeType = dateTimeType;
//            this._parts = (int)dateTimeType;
//        }

//        #region CONSTRUCTORS
//        internal Datetime(DateTime datetime, DateTimeTypeEnum dateTimeType)
//        {
//            this._instance = datetime;
//            this.SetDateTimeType(dateTimeType);
//        }

//        public Datetime()
//        {
//            this._instance = new DateTime();
//            this.SetDateTimeType(DateTimeTypeEnum.neither);
//        }

//        public Datetime(DateTime datetime)
//        {
//            this._instance = datetime;
//            this.SetDateTimeType(DateTimeTypeEnum.both);
//        }

//        public Datetime(Datetime other)
//        {
//            this._instance = other._instance;
//            this.SetDateTimeType(other._dateTimeType);
//            this._parts = other._parts;
//        }

//        public Datetime(int year, int month, int dayOfMonth)
//        {
//            this._instance = new DateTime(year, month, dayOfMonth);
//            this.SetDateTimeType(DateTimeTypeEnum.date);
//        }

//        public Datetime(int hour, int minute, int second, int milliSecond)
//        {
//            DateTime dtToday = DateTime.Today;
//            this._instance = new DateTime(dtToday.Year, dtToday.Month, dtToday.Day, hour, minute, second, milliSecond);
//            this.SetDateTimeType(DateTimeTypeEnum.time);
//        }

//        public Datetime(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond)
//        {
//            this._instance = new DateTime(year, month, dayOfMonth, hour, minute, second, milliSecond);
//            this.SetDateTimeType(DateTimeTypeEnum.both);
//        }
//        #endregion

//        #region PROPERTIES
//        internal DateTimeTypeEnum DateTimeType { get { return this._dateTimeType; } }

//        private int _parts;
//        public int Parts { get { return this._parts; } }

//        public int DayOfMonth
//        {
//            get { return this._instance.Day; }
//            set
//            {
//                this._parts |= Datetime.DAY_OF_MONTH;
//                this._instance = this._instance.AddDays(value - this._instance.Day);
//            }
//        }

//        public int Hour
//        {
//            get { return this._instance.Hour; }
//            set
//            {
//                this._parts |= Datetime.HOUR;
//                this._instance = this._instance.AddHours(value - this._instance.Hour);
//            }
//        }

//        public int MilliSecond
//        {
//            get { return this._instance.Millisecond; }
//            set
//            {
//                this._parts |= Datetime.MILLISECOND;
//                this._instance = this._instance.AddMilliseconds(value - this._instance.Millisecond);
//            }
//        }

//        public int Minute
//        {
//            get { return this._instance.Minute; }
//            set
//            {
//                this._parts |= Datetime.MINUTE;
//                this._instance = this._instance.AddMinutes(value - this._instance.Minute);
//            }
//        }

//        public int Month
//        {
//            get { return this._instance.Month; }
//            set
//            {
//                this._parts |= Datetime.MONTH;
//                this._instance = this._instance.AddMonths(value - this._instance.Month);
//            }
//        }

//        public int Second
//        {
//            get { return this._instance.Second; }
//            set
//            {
//                this._parts |= Datetime.SECOND;
//                this._instance = this._instance.AddSeconds(value - this._instance.Second);
//            }
//        }

//        public int Year
//        {
//            get { return this._instance.Year; }
//            set
//            {
//                this._parts |= Datetime.YEAR;
//                this._instance = this._instance.AddYears(value - this._instance.Year);
//            }
//        }

//        public int TimezoneOffsetMinutes
//        {
//            get { throw new NotImplementedException(); }
//            set { throw new NotImplementedException(); }
//        }
//        #endregion

//        #region METHODS
//        public void Clear()
//        {
//            this._instance = new DateTime();
//            this.SetDateTimeType(DateTimeTypeEnum.neither);
//        }

//        public object Clone()
//        {
//            return new Datetime(this);
//        }

//        /// <summary>
//        /// Always true since the C# DateTime type does not support invalid datetimes.
//        /// </summary>
//        /// <returns></returns>
//        public bool IsValid()
//        {
//            return true;
//        }

//        public override bool Equals(object obj)
//        {
//            return this._instance == ((Datetime)obj)._instance;
//        }

//        public override int GetHashCode()
//        {
//            unchecked
//            {
//                int hash = 17;
//                hash = hash * 23 + this._instance.GetHashCode();
//                hash = hash * 23 + this._dateTimeType.GetHashCode();
//                return hash;
//            }
//        }

//        public void SetDate(int year, int month, int dayOfMonth)
//        {
//            this.Year = year;
//            this.Month = month;
//            this.DayOfMonth = dayOfMonth;
//        }

//        public void SetDatetime(DateTime datetime)
//        {
//            this._instance = datetime;
//        }

//        public void SetDatetime(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond)
//        {
//            this._instance = new DateTime(year, month, dayOfMonth, hour, minute, second, milliSecond);
//        }

//        public void SetDatetimeTz(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond, int timezoneOffsetMinutes)
//        {
//            throw new NotImplementedException();
//        }

//        public void SetDateTz(int year, int month, int dayOfMonth, int timezoneOffsetMinutes)
//        {
//            throw new NotImplementedException();
//        }

//        public void SetTime(int hour, int minute, int second, int milliSecond)
//        {
//            this.Hour = hour;
//            this.Minute = minute;
//            this.Second = second;
//            this.MilliSecond = milliSecond;
//        }

//        public void SetTimeTz(int hour, int minute, int second, int milliSecond, int timezoneOffsetMinutes)
//        {
//            throw new NotImplementedException();
//        }

//        public override string ToString()
//        {
//            switch (this._dateTimeType)
//            {
//                case DateTimeTypeEnum.neither:
//                    throw new NotImplementedException();

//                case DateTimeTypeEnum.date:
//                    return Types.DisplayFormats.FormatDate(this);

//                case DateTimeTypeEnum.time:
//                    return Types.DisplayFormats.FormatTimeZone(this);

//                case DateTimeTypeEnum.both:
//                    return Types.DisplayFormats.FormatDatetimeZone(this);

//                default:
//                    throw new NotImplementedException();
//            }
//        }

//        public DateTime ToSystemDateTime()
//        {
//            return this._instance;
//        }
//        #endregion
//    }
//}
