//------------------------------------------------------------------------------
//  This code comes from Bloomberg.Blpapi.dll
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bloomberglp.Blpapi
{
    public class Datetime
    {
        #region CONSTANTS
        public const short YEAR_PART = 128;
        public const byte MONTH_PART = 64;
        public const byte DAY_OF_MONTH_PART = 32;
        public const byte HOUR_PART = 16;
        public const byte MINUTE_PART = 8;
        public const byte SECOND_PART = 4;
        public const byte MILLISECOND_PART = 2;
        public const byte TIME_ZONE_OFFSET = 1;
        public const short DATE = 224;
        public const short TIME = 28;
        public const short TIMEMILLI = 30;
        public const short MICROSECOND_PART = 258;
        public const short NANOSECOND_PART = 770;
        public const short PICOSECOND_PART = 1794;
        private const int IDX_YEAR = 0;
        private const int IDX_MONTH = 1;
        private const int IDX_DAY_OF_MONTH = 2;
        private const int IDX_HOUR = 3;
        private const int IDX_MINUTE = 4;
        private const int IDX_SECOND = 5;
        private const int IDX_MILLISECOND = 6;
        private const int IDX_TIME_ZONE_OFFSET = 7;
        private const int NUM_FIELDS = 8;
        private const int MILLISECONDS_TO_MINUTES = 60000;
        private const byte PART_MASK = 255;
        private const long PICOPERSEC = 1000000000000L;
        private const long PICOPERMILLISEC = 1000000000L;
        private const long PICOPERMICROSEC = 1000000L;
        private const long PICOPERNANOSEC = 1000L;
        private const int MILLIPERSEC = 1000;
        private const int MICROPERSEC = 1000000;
        private const long MICROPERMILLISEC = 1000L;
        private const long NANOPERSEC = 1000000000L;
        private const long NANOPERMILLISEC = 1000000L;
        #endregion

        private int d_parts;
        private short[] d_datetimeFieldValues;
        private long d_picoSeconds;

        #region ACCESSORS
        public int Year
        {
            get
            {
                return (int)this.d_datetimeFieldValues[0];
            }
            set
            {
                this.d_datetimeFieldValues[0] = (short)value;
                this.d_parts |= 128;
            }
        }
        public int Month
        {
            get
            {
                return (int)this.d_datetimeFieldValues[1];
            }
            set
            {
                this.d_datetimeFieldValues[1] = (short)((byte)value);
                this.d_parts |= 64;
            }
        }
        public int DayOfMonth
        {
            get
            {
                return (int)this.d_datetimeFieldValues[2];
            }
            set
            {
                this.d_datetimeFieldValues[2] = (short)((byte)value);
                this.d_parts |= 32;
            }
        }
        public int Hour
        {
            get
            {
                return (int)this.d_datetimeFieldValues[3];
            }
            set
            {
                this.d_datetimeFieldValues[3] = (short)((byte)value);
                this.d_parts |= 16;
            }
        }
        public int Minute
        {
            get
            {
                return (int)this.d_datetimeFieldValues[4];
            }
            set
            {
                this.d_datetimeFieldValues[4] = (short)((byte)value);
                this.d_parts |= 8;
            }
        }
        public int Second
        {
            get
            {
                return (int)this.d_datetimeFieldValues[5];
            }
            set
            {
                this.d_datetimeFieldValues[5] = (short)((byte)value);
                this.d_parts |= 4;
            }
        }
        public int MilliSecond
        {
            get
            {
                return (int)this.d_datetimeFieldValues[6];
            }
            set
            {
                this.d_datetimeFieldValues[6] = (short)value;
                this.d_parts |= 2;
            }
        }
        public int MicroSecond
        {
            get
            {
                return (int)((this.d_picoSeconds + (long)this.MilliSecond * 1000000000L) / 1000000L);
            }
            set
            {
                this.MilliSecond = (int)((long)value / 1000L % 1000L);
                this.d_picoSeconds = (long)value % 1000L * 1000000L;
                this.d_parts |= 258;
            }
        }
        public int NanoSecond
        {
            get
            {
                return (int)((this.d_picoSeconds + (long)this.MilliSecond * 1000000000L) / 1000L);
            }
            set
            {
                this.MilliSecond = (int)((long)value / 1000000L % 1000L);
                this.d_picoSeconds = (long)value % 1000000L * 1000L;
                this.d_parts |= 770;
            }
        }
        public long PicoSecond
        {
            get
            {
                return this.d_picoSeconds + (long)this.MilliSecond * 1000000000L;
            }
            set
            {
                this.MilliSecond = (int)(value / 1000000000L % 1000L);
                this.d_picoSeconds = value % 1000000000L;
                this.d_parts |= 1794;
            }
        }
        public int Parts
        {
            get
            {
                return this.d_parts;
            }
        }
        public int TimezoneOffsetMinutes
        {
            get
            {
                return (int)this.d_datetimeFieldValues[7];
            }
            set
            {
                this.d_datetimeFieldValues[7] = (short)value;
                this.d_parts |= 1;
            }
        }
        #endregion

        #region CONSTRUCTORS
		public Datetime()
		{
			this.init();
		}
		public Datetime(Datetime other)
		{
			this.init();
			this.d_parts = other.d_parts;
			Array.Copy(other.d_datetimeFieldValues, 0, this.d_datetimeFieldValues, 0, this.d_datetimeFieldValues.Length);
			this.d_picoSeconds = other.d_picoSeconds;
		}
		public Datetime(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond)
		{
			this.init();
			this.SetDatetime(year, month, dayOfMonth, hour, minute, second, milliSecond);
		}
		public Datetime(int year, int month, int dayOfMonth)
		{
			this.init();
			this.SetDate(year, month, dayOfMonth);
		}
		public Datetime(int hour, int minute, int second, int milliSecond)
		{
			this.init();
			this.SetTime(hour, minute, second, milliSecond);
		}
        public Datetime(DateTime datetime)
		{
			this.init();
			this.SetDatetime(datetime.Year, datetime.Month, datetime.Day, datetime.Hour, datetime.Minute, datetime.Second, datetime.Millisecond);
			switch (datetime.Kind)
			{
			case DateTimeKind.Utc:
				this.TimezoneOffsetMinutes = 0;
				return;
			case DateTimeKind.Local:
				this.TimezoneOffsetMinutes = TimeZone.CurrentTimeZone.GetUtcOffset(datetime).Hours * 60;
				return;
			default:
				return;
			}
		}
        #endregion

        private void init()
        {
            this.d_datetimeFieldValues = new short[8];
            this.Clear();
        }

        public bool HasParts(int parts)
        {
            return parts == (this.d_parts & parts);
        }
        public void SetDatetime(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond)
        {
            this.Year = year;
            this.Month = month;
            this.DayOfMonth = dayOfMonth;
            this.Hour = hour;
            this.Minute = minute;
            this.Second = second;
            this.MilliSecond = milliSecond;
        }
        public void SetDatetime(DateTime datetime)
        {
            this.Year = datetime.Year;
            this.Month = datetime.Month;
            this.DayOfMonth = datetime.Day;
            this.Hour = datetime.Hour;
            this.Minute = datetime.Minute;
            this.Second = datetime.Second;
            this.MilliSecond = datetime.Millisecond;
        }
        public void SetDatetimeTz(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond, int timezoneOffsetMinutes)
        {
            this.SetDatetime(year, month, dayOfMonth, hour, minute, second, milliSecond);
            this.TimezoneOffsetMinutes = timezoneOffsetMinutes;
        }
        public void SetDate(int year, int month, int dayOfMonth)
        {
            this.Year = year;
            this.Month = month;
            this.DayOfMonth = dayOfMonth;
        }
        public void SetDateTz(int year, int month, int dayOfMonth, int timezoneOffsetMinutes)
        {
            this.SetDate(year, month, dayOfMonth);
            this.TimezoneOffsetMinutes = timezoneOffsetMinutes;
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
            this.SetTime(hour, minute, second, milliSecond);
            this.TimezoneOffsetMinutes = timezoneOffsetMinutes;
        }
        public void Clear()
        {
            this.d_parts = 0;
            this.d_datetimeFieldValues[0] = 1;
            this.d_datetimeFieldValues[1] = 1;
            this.d_datetimeFieldValues[2] = 1;
            this.d_datetimeFieldValues[3] = 24;
            this.d_datetimeFieldValues[4] = 0;
            this.d_datetimeFieldValues[5] = 0;
            this.d_datetimeFieldValues[6] = 0;
            this.d_datetimeFieldValues[7] = 0;
            this.d_picoSeconds = 0L;
        }
        public override bool Equals(object obj)
        {
            if (this == obj)
            {
                return true;
            }
            if (obj is Datetime)
            {
                Datetime datetime = (Datetime)obj;
                if ((this.d_parts & 255) == (datetime.d_parts & 255) && this.d_picoSeconds == datetime.d_picoSeconds)
                {
                    for (int i = 0; i < this.d_datetimeFieldValues.Length; i++)
                    {
                        if (this.d_datetimeFieldValues[i] != datetime.d_datetimeFieldValues[i])
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
            return false;
        }
        public bool IsValid()
        {
            return ((!this.HasParts(128) && !this.HasParts(64) && !this.HasParts(this.DayOfMonth)) || this.isValidDate(this.Year, this.Month, this.DayOfMonth)) && ((!this.HasParts(16) && !this.HasParts(8) && !this.HasParts(4) && !this.HasParts(2)) || this.isValidTime(this.Hour, this.Minute, this.Second, this.MilliSecond));
        }
        [Obsolete("Please use HasParts(int parts) instead")]
        public bool IsValidField(int fieldId)
        {
            return this.HasParts(fieldId);
        }
        [Obsolete("Please use Parts instead")]
        public int parts()
        {
            return this.d_parts;
        }
        [Obsolete("Please use HasParts(int parts) instead")]
        public bool hasParts(int parts)
        {
            return parts == (this.d_parts & parts);
        }
        public object Clone()
        {
            return new Datetime(this);
        }
        public override string ToString()
        {
            StringBuilder stringBuilder = new StringBuilder(10);
            char c = '\0';
            if (this.HasParts(128) || this.HasParts(64) || this.HasParts(32))
            {
                stringBuilder.Append(DatetimeIso8601Util.generateDate(this));
                c = 'T';
            }
            if (this.HasParts(16) || this.HasParts(8) || this.HasParts(4) || this.HasParts(2))
            {
                if (c != '\0')
                {
                    stringBuilder.Append(c);
                }
                stringBuilder.Append(DatetimeIso8601Util.generateTime(this));
            }
            if (this.HasParts(1))
            {
                DatetimeIso8601Util.generateTimezoneOffset(stringBuilder, this);
            }
            return stringBuilder.ToString();
        }
        public DateTime ToSystemDateTime()
        {
            DateTimeKind kind;
            if (this.HasParts(1))
            {
                if (this.TimezoneOffsetMinutes == 0)
                {
                    kind = DateTimeKind.Utc;
                }
                else
                {
                    if ((double)this.TimezoneOffsetMinutes == TimeZone.CurrentTimeZone.GetUtcOffset(DateTime.Now).TotalMinutes)
                    {
                        kind = DateTimeKind.Local;
                    }
                    else
                    {
                        kind = DateTimeKind.Unspecified;
                    }
                }
            }
            else
            {
                kind = DateTimeKind.Unspecified;
            }
            if (this.HasParts(128) || this.HasParts(64) || this.HasParts(32))
            {
                return new DateTime(this.Year, this.Month, this.DayOfMonth, this.HasParts(16) ? this.Hour : 0, this.Minute, this.Second, this.MilliSecond, kind);
            }
            DateTime now = DateTime.Now;
            return new DateTime(now.Year, now.Month, now.Day, this.HasParts(16) ? this.Hour : 0, this.Minute, this.Second, this.MilliSecond, kind);
        }
        public override int GetHashCode()
        {
            return ((long)this.d_datetimeFieldValues[0] + (long)this.d_datetimeFieldValues[1] + (long)this.d_datetimeFieldValues[2] * 3600000L + (long)this.d_datetimeFieldValues[3] * 3600000L + (long)this.d_datetimeFieldValues[4] * 60000L + (long)(this.d_datetimeFieldValues[5] * 1000) + (long)this.d_datetimeFieldValues[6] + (long)this.d_datetimeFieldValues[7] + this.d_picoSeconds).GetHashCode();
        }
        private bool isLeapYear(int y)
        {
            return y % 4 == 0 && (y <= 1752 || y % 100 != 0 || 0 == y % 400);
        }
        private bool isValidDate(int year, int month, int day)
        {
            if (year <= 0 || year > 9999 || month <= 0 || month > 12 || day <= 0 || day > 31)
            {
                return false;
            }
            if (day < 29)
            {
                return true;
            }
            if (year == 1752 && month == 9 && day > 2 && day < 14)
            {
                return false;
            }
            switch (month)
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    return true;
                case 2:
                    if (this.isLeapYear(year))
                    {
                        return day <= 29;
                    }
                    return day <= 28;
                case 4:
                case 6:
                case 9:
                case 11:
                    return day <= 30;
                default:
                    return true;
            }
        }
        private bool isValidTime(int hour, int minute, int second, int milliSecond)
        {
            if (hour == 24)
            {
                return minute == 0 && second == 0 && milliSecond == 0;
            }
            return hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60 && milliSecond >= 0 && milliSecond < 1000;
        }


    }
}
