//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/Datetime.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "bemu_headers.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time.hpp>
#include <exception>

namespace BEmu
{	
	class Datetime
	{
		public:
			struct DatetimeParts {
				// Bit flags and masks used to determine which parts of a Datetime are valid.

				enum Value {
					// Enumeration used to indicate which parts of the 'Datetime' object
					// have had their values set.  The actual enumeration constants are
					// thus *not* consecutive -- they are bit fields that can be combined
					// using bitwise operators.  Note that the constants themselves are
					// defined in 'blpapi_defs.h'.

					  YEAR            = 0x1            // year is set
					, MONTH           = 0x2           // month is set
					, DAY             = 0x4             // day is set
					, OFFSET          = 0x8          // offset is set
					, HOURS           = 0x10           // hours is set
					, MINUTES         = 0x20         // minutes is set
					, SECONDS         = 0x40         // seconds is set
					, FRACSECONDS     = 0x80     // fraction-of-second (both millisecond and picosecond) is set
					, MILLISECONDS    = 0x80    // 'MILLISECONDS' is a (legacy) synonym for 'FRACSECONDS'
					, DATE            = 0x7 // year, month, and day are set
					, TIME            = 0x70            // hours, minutes, and seconds are set
					, TIMEFRACSECONDS = 0xF0 // hours, minutes, seconds, and fraction-of-second are set
					, TIMEMILLI       = 0xF0       // 'TIMEMILLI' is a (legacy) synonym for 'TIMEFRACSECONDS'
				};
			};

		private:
			boost::posix_time::ptime _instance;
			enum DateTimeTypeEnum { neither = 0, date = DatetimeParts::DATE, time = DatetimeParts::TIME, both = DatetimeParts::DATE | DatetimeParts::TIME };
			DateTimeTypeEnum _dateTimeType;

			unsigned _parts;
			void setDateTimeType(DateTimeTypeEnum dateTimeType);

			//I'm surprised the BB API doens't have this call (this doesn't call setDateTimeType)
			void setDatetime(unsigned year, unsigned month, unsigned day, unsigned hours, unsigned minutes, unsigned seconds, unsigned milliseconds);

		public:
			enum WeekDayEnum
			{
				Sunday = boost::date_time::Sunday,
				Monday = boost::date_time::Monday, 
				Tuesday = boost::date_time::Tuesday, 
				Wednesday = boost::date_time::Wednesday, 
				Thursday = boost::date_time::Thursday, 
				Friday = boost::date_time::Friday, 
				Saturday = boost::date_time::Saturday
			};

			class DatetimeException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} datetimeEx;

			WeekDayEnum getWeekDay() const;

			DLL_EXPORT Datetime();
			DLL_EXPORT Datetime(unsigned year, unsigned month, unsigned day);
			DLL_EXPORT Datetime(unsigned year, unsigned month, unsigned day, unsigned hours, unsigned minutes, unsigned seconds);
			DLL_EXPORT Datetime(unsigned hours, unsigned minutes, unsigned seconds, unsigned milleseconds);
			DLL_EXPORT Datetime(unsigned year, unsigned month, unsigned day, unsigned hours, unsigned minutes, unsigned seconds, unsigned milleseconds);

			DLL_EXPORT static Datetime createDatetime(unsigned year, unsigned month, unsigned day, unsigned hours, unsigned minutes, unsigned seconds);
			DLL_EXPORT static Datetime createDate(unsigned year, unsigned month, unsigned day);
			DLL_EXPORT static Datetime createTime(unsigned hours, unsigned minutes, unsigned seconds);
			DLL_EXPORT static Datetime createTime(unsigned hours, unsigned minutes, unsigned seconds, unsigned milliseconds);
			
			DLL_EXPORT Datetime& operator=(const Datetime &rhs);
			DLL_EXPORT Datetime(const Datetime& arg);

			DLL_EXPORT ~Datetime();
		
			DLL_EXPORT unsigned parts() const;
			DLL_EXPORT bool hasParts(unsigned parts) const;
			DLL_EXPORT bool isValid() const; //Always true since the boost ptime type does not support invalid datetimes.

			DLL_EXPORT unsigned year() const;
			DLL_EXPORT unsigned month() const;
			DLL_EXPORT unsigned day() const;
			DLL_EXPORT unsigned hours() const;
			DLL_EXPORT unsigned minutes() const;
			DLL_EXPORT unsigned seconds() const;
			DLL_EXPORT unsigned milliseconds() const;

			DLL_EXPORT void setYear(unsigned value);
			DLL_EXPORT void setMonth(unsigned value);
			DLL_EXPORT void setDay(unsigned value);
			DLL_EXPORT void setHours(unsigned value);
			DLL_EXPORT void setMinutes(unsigned value);
			DLL_EXPORT void setSeconds(unsigned value);
			DLL_EXPORT void setMilliseconds(unsigned milliseconds);

			DLL_EXPORT void setDate(unsigned year, unsigned month, unsigned day);
			DLL_EXPORT void setTime(unsigned hours, unsigned minutes, unsigned seconds);
			DLL_EXPORT void setTime(unsigned hours, unsigned minutes, unsigned seconds, unsigned milliseconds);

			//These are not exported to the DLL.  The actual Bloomberg API doesn't have these functions.
			void addYears(int years);
			void addMonths(int months);
			void addDays(long days);
			void addHours(long hours);
			void addMinutes(long minutes);
			void addSeconds(long seconds);
			boost::posix_time::ptime getInstance() const;
			
			//These are not exported to the DLL.  The actual Bloomberg API doesn't have these functions.
			static Datetime Today();
			static Datetime Now();
			static Datetime FromYYYYMMDD(const std::string& str);
			static Datetime FromYYMMDD(const std::string& str);

			DLL_EXPORT static bool isLeapYear(int year);
			DLL_EXPORT static bool isValidDate(int year, int month, int day);
			DLL_EXPORT static bool isValidTime(int hours, int minutes, int seconds);
			DLL_EXPORT static bool isValidTime(int hours, int minutes, int seconds, int milliSeconds);

			friend DLL_EXPORT bool operator<(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator<=(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator>(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator>=(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator==(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator!=(const Datetime& lhs, const Datetime& rhs);
			
			friend DLL_EXPORT std::ostream& operator<<(std::ostream& os, const Datetime& datetime);
	};

	DLL_EXPORT bool operator<(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT bool operator<=(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT bool operator>(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT bool operator>=(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT bool operator==(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT std::ostream& operator<<(std::ostream& os, const Datetime& datetime);
}