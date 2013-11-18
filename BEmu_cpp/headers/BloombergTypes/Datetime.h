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
		private:
			boost::posix_time::ptime _instance;
			enum DateTimeTypeEnum { neither = 0, date = 1, time = 2, both = 3 };
			DateTimeTypeEnum _dateTimeType;

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
			DLL_EXPORT Datetime(int year, int month, int day);
			DLL_EXPORT Datetime(int year, int month, int day, int hours, int minutes, int seconds);
			DLL_EXPORT Datetime(int hours, int minutes, int seconds, int milleseconds);
			DLL_EXPORT Datetime(int year, int month, int day, int hours, int minutes, int seconds, int milleseconds);
			
			DLL_EXPORT Datetime& operator=(const Datetime &rhs);
			DLL_EXPORT Datetime(const Datetime& arg);

			DLL_EXPORT Datetime::~Datetime();
		
			DLL_EXPORT unsigned year() const;
			DLL_EXPORT unsigned month() const;
			DLL_EXPORT unsigned day() const;
			DLL_EXPORT unsigned hours() const;
			DLL_EXPORT unsigned minutes() const;
			DLL_EXPORT unsigned seconds() const;

			//These are not exported to the DLL.  The actual Bloomberg API doesn't have these functions.
			void addYears(int years);
			void addMonths(int months);
			void addDays(long days);
			void addHours(long hours);
			void addMinutes(long minutes);
			void addSeconds(long seconds);
			
			static Datetime Today();
			static Datetime Now();
			static Datetime FromYYYYMMDD(const std::string& str);
			static Datetime FromYYMMDD(const std::string& str);
			std::string ToYYYYMMDD() const;
			std::string ToMMddYY() const;

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