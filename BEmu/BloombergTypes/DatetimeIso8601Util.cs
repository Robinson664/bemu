//------------------------------------------------------------------------------
//  This code comes from Bloomberg.Blpapi.dll
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bloomberglp.Blpapi
{
    internal class DatetimeIso8601Util
    {
        private const long PICOSPERSEC = 1000000000000L;
        public static bool parseDatetimeTz(string strDatetime, Datetime datetime)
        {
            int num = strDatetime.IndexOf('T');
            return 
                num >= 0 && 
                DatetimeIso8601Util.parseDate(new StringCharacterIterator(strDatetime, 0, num, 0), datetime) && 
                DatetimeIso8601Util.parseTimeTz(new StringCharacterIterator(strDatetime, num + 1, strDatetime.Length, num + 1), datetime);
        }
        public static bool parseDatetime(string strDatetime, Datetime datetime)
        {
            int num = strDatetime.IndexOf('T');
            return num >= 0 && DatetimeIso8601Util.parseDate(new StringCharacterIterator(strDatetime, 0, num, 0), datetime) && DatetimeIso8601Util.parseTime(new StringCharacterIterator(strDatetime, num + 1, strDatetime.Length, num + 1), datetime);
        }
        public static bool parseDateTz(string strDate, Datetime date)
        {
            StringCharacterIterator iter = new StringCharacterIterator(strDate);
            return DatetimeIso8601Util.parseDateTz(iter, date);
        }
        public static bool parseDate(string strDate, Datetime date)
        {
            StringCharacterIterator iter = new StringCharacterIterator(strDate);
            return DatetimeIso8601Util.parseDate(iter, date);
        }
        public static bool parseTimeTz(string strTime, Datetime time)
        {
            StringCharacterIterator iter = new StringCharacterIterator(strTime);
            return DatetimeIso8601Util.parseTimeTz(iter, time);
        }
        public static bool parseTime(string strTime, Datetime time)
        {
            StringCharacterIterator iter = new StringCharacterIterator(strTime);
            return DatetimeIso8601Util.parseTime(iter, time);
        }
        public static string generateDatetimeTz(Datetime datetime)
        {
            StringBuilder stringBuilder = new StringBuilder(39);
            DatetimeIso8601Util.generateDatetimeTz(stringBuilder, datetime);
            return stringBuilder.ToString();
        }
        public static void generateDatetimeTz(StringBuilder sb, Datetime datetime)
        {
            DatetimeIso8601Util.generateDatetime(sb, datetime);
            DatetimeIso8601Util.generateTimezoneOffset(sb, datetime);
        }
        public static string generateDatetime(Datetime datetime)
        {
            StringBuilder stringBuilder = new StringBuilder(33);
            DatetimeIso8601Util.generateDatetime(stringBuilder, datetime);
            return stringBuilder.ToString();
        }
        public static void generateDatetime(StringBuilder sb, Datetime datetime)
        {
            DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)datetime.Year, 4);
            sb.Append('-');
            DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)datetime.Month, 2);
            sb.Append('-');
            DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)datetime.DayOfMonth, 2);
            sb.Append('T');
            DatetimeIso8601Util.generateTime(sb, datetime);
        }
        public static string generateDateTz(Datetime datetime)
        {
            StringBuilder stringBuilder = new StringBuilder(16);
            DatetimeIso8601Util.generateDateTz(stringBuilder, datetime);
            return stringBuilder.ToString();
        }
        public static void generateDateTz(StringBuilder sb, Datetime datetime)
        {
            DatetimeIso8601Util.generateDate(sb, datetime);
            DatetimeIso8601Util.generateTimezoneOffset(sb, datetime);
        }
        public static string generateDate(Datetime datetime)
        {
            StringBuilder stringBuilder = new StringBuilder(10);
            DatetimeIso8601Util.generateDate(stringBuilder, datetime);
            return stringBuilder.ToString();
        }
        public static void generateDate(StringBuilder sb, Datetime datetime)
        {
            DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)datetime.Year, 4);
            sb.Append('-');
            DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)datetime.Month, 2);
            sb.Append('-');
            DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)datetime.DayOfMonth, 2);
        }
        public static string generateTimeTz(Datetime datetime)
        {
            StringBuilder stringBuilder = new StringBuilder(19);
            DatetimeIso8601Util.generateTimeTz(stringBuilder, datetime);
            return stringBuilder.ToString();
        }
        public static void generateTimeTz(StringBuilder sb, Datetime datetime)
        {
            DatetimeIso8601Util.generateTime(sb, datetime);
            DatetimeIso8601Util.generateTimezoneOffset(sb, datetime);
        }
        public static string generateTime(Datetime datetime)
        {
            StringBuilder stringBuilder = new StringBuilder(10);
            DatetimeIso8601Util.generateTime(stringBuilder, datetime);
            return stringBuilder.ToString();
        }
        public static void generateTime(StringBuilder sb, Datetime datetime)
        {
            DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)datetime.Hour, 2);
            sb.Append(':');
            DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)datetime.Minute, 2);
            sb.Append(':');
            DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)datetime.Second, 2);
            sb.Append('.');
            long num = datetime.PicoSecond;
            int num2 = 12;
            while (num != 0L && num % 1000L == 0L)
            {
                num /= 1000L;
                num2 -= 3;
            }
            if (num == 0L)
            {
                num2 = 3;
            }
            DatetimeIso8601Util.appendUnsignedStringValue(sb, num, num2);
        }
        public static void generateTimezoneOffset(StringBuilder sb, Datetime datetime)
        {
            if (datetime.HasParts(Datetime.TIME_ZONE_OFFSET))
            {
                int num = datetime.TimezoneOffsetMinutes;
                if (num < 0)
                {
                    num = (int)((short)(-(short)num));
                    sb.Append('-');
                }
                else
                {
                    sb.Append('+');
                }
                DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)(num / 60), 2);
                sb.Append(':');
                DatetimeIso8601Util.appendUnsignedStringValue(sb, (long)(num % 60), 2);
            }
        }
        private static bool parseDateTz(StringCharacterIterator iter, Datetime datetimeTz)
        {
            return DatetimeIso8601Util.parseDate(iter, datetimeTz) && (iter.current() == '￿' || DatetimeIso8601Util.parseTimezoneOffset(iter, datetimeTz));
        }
        private static bool parseDate(StringCharacterIterator iter, Datetime datetime)
        {
            short num = (short)DatetimeIso8601Util.parseUnsigned(iter, 2147483647);
            if (iter.current() != '-')
            {
                return false;
            }
            iter.next();
            short num2 = (short)DatetimeIso8601Util.parseUnsigned(iter, 2147483647);
            if (iter.current() != '-')
            {
                return false;
            }
            iter.next();
            short num3 = (short)DatetimeIso8601Util.parseUnsigned(iter, 2147483647);
            if (num != 1 || num2 != 1 || num3 != 1)
            {
                datetime.Year = (int)num;
                datetime.Month = (int)num2;
                datetime.DayOfMonth = (int)num3;
            }
            return true;
        }
        private static bool parseTimeTz(StringCharacterIterator iter, Datetime timeTz)
        {
            return 
                DatetimeIso8601Util.parseTime(iter, timeTz) && 
                (iter.current() == '￿' || DatetimeIso8601Util.parseTimezoneOffset(iter, timeTz));
        }
        private static bool parseTime(StringCharacterIterator iter, Datetime time)
        {
            short num = (short)DatetimeIso8601Util.parseUnsigned(iter, 2147483647);
            if (iter.current() != ':')
            {
                return false;
            }
            iter.next();
            short num2 = (short)DatetimeIso8601Util.parseUnsigned(iter, 2147483647);
            if (iter.current() != ':')
            {
                return false;
            }
            iter.next();
            short num3 = (short)DatetimeIso8601Util.parseUnsigned(iter, 2147483647);
            long num4 = 0L;
            if (iter.current() == '.')
            {
                iter.next();
                num4 = DatetimeIso8601Util.parseUnsignedFixedWidth(iter, 12);
                char c = iter.current();
                while (c != '￿' && char.IsDigit(c))
                {
                    c = iter.next();
                }
            }
            if (num != 24 || num2 != 0 || num3 != 0 || num4 != 0L)
            {
                time.Hour = (int)num;
                time.Minute = (int)num2;
                time.Second = (int)num3;
                time.PicoSecond = num4;
            }
            return true;
        }
        private static bool parseTimezoneOffset(StringCharacterIterator iter, Datetime datetime)
        {
            short num;
            if (iter.current() == '+')
            {
                num = 1;
            }
            else
            {
                if (iter.current() == '-')
                {
                    num = -1;
                }
                else
                {
                    if (iter.current() == 'Z' || iter.current() == 'z')
                    {
                        datetime.TimezoneOffsetMinutes = 0;
                        return true;
                    }
                    return false;
                }
            }
            iter.next();
            short num2 = (short)DatetimeIso8601Util.parseUnsigned(iter, 2147483647);
            if (iter.current() != ':')
            {
                return false;
            }
            iter.next();
            short num3 = (short)DatetimeIso8601Util.parseUnsigned(iter, 2147483647);
            datetime.TimezoneOffsetMinutes = (int)(num * (num2 * 60 + num3));
            return true;
        }
        private static int parseUnsigned(StringCharacterIterator iter, int limit)
        {
            int num = 0;
            int num2 = 0;
            char c = iter.current();
            while (c != '￿' && num2 < limit && char.IsDigit(c))
            {
                num = num * 10 + (int)c - 48;
                c = iter.next();
                num2++;
            }
            return num;
        }
        private static long parseUnsignedFixedWidth(StringCharacterIterator iter, int limit)
        {
            long num = 0L;
            int i = 0;
            char c = iter.current();
            while (c != '￿')
            {
                if (i >= limit)
                {
                    break;
                }
                if (!char.IsDigit(c))
                {
                    break;
                }
                num = num * 10L + (long)((ulong)c) - 48L;
                c = iter.next();
                i++;
            }
            while (i < limit)
            {
                num *= 10L;
                i++;
            }
            return num;
        }
        private static bool appendUnsignedStringValue(StringBuilder sb, long value, int width)
        {
            for (int i = 0; i < width; i++)
            {
                sb.Append('0');
            }
            if (value < 0L)
            {
                return false;
            }
            int num = sb.Length - 1;
            while (width > 0)
            {
                sb[num] = (char)(value % 10L + 48L);
                value /= 10L;
                width--;
                num--;
            }
            return true;
        }
    }
}
