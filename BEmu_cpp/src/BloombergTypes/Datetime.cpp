//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/Datetime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Datetime.h"
#include "Types/DisplayFormats.h"
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/date_duration.hpp>

namespace BEmu
{
	Datetime::Datetime() //this constructor is not visible
	{
	}

	Datetime::Datetime(int year, int month, int day)
	{
		this->_instance = boost::posix_time::ptime(boost::gregorian::date(year, month, day));

		this->setDateTimeType(date);
	}

	Datetime::Datetime(int year, int month, int day, int hours, int minutes, int seconds)
	{
		this->_instance = boost::posix_time::ptime(
			boost::gregorian::date(year, month, day),
			boost::posix_time::time_duration(hours, minutes, seconds));

		this->setDateTimeType(both);
	}

	Datetime::Datetime(int hours, int minutes, int seconds, int milleseconds)
	{
		this->_instance = boost::posix_time::ptime(
			boost::posix_time::second_clock::local_time().date(),
			boost::posix_time::time_duration(hours, minutes, seconds, milleseconds));

		this->setDateTimeType(time);
	}

	Datetime::Datetime(int year, int month, int day, int hours, int minutes, int seconds, int milleseconds)
	{
		this->_instance = boost::posix_time::ptime(
			boost::gregorian::date(year, month, day),
			boost::posix_time::time_duration(hours, minutes, seconds, milleseconds));

		this->setDateTimeType(both);
	}

	Datetime::Datetime(const Datetime& arg)
	{
		this->_instance = boost::posix_time::ptime(arg._instance);
		this->_dateTimeType = arg._dateTimeType;
		this->_parts = arg._parts;
	}

	Datetime& Datetime::operator=(const Datetime &rhs)
	{
		if (this != &rhs)
		{
			this->_instance = boost::posix_time::ptime(rhs._instance);
			this->_dateTimeType = rhs._dateTimeType;
			this->_parts = rhs._parts;
		}
		return *this;
	}

	Datetime::~Datetime()
	{
	}

	Datetime Datetime::Today()
	{
		boost::posix_time::ptime today(boost::posix_time::second_clock::local_time().date());

		Datetime result(today.date().year(), today.date().month(), today.date().day());
		return result;
	}

	Datetime Datetime::Now()
	{
		boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

		Datetime result(
			now.date().year(), now.date().month(), now.date().day(),
			now.time_of_day().hours(), now.time_of_day().minutes(), now.time_of_day().seconds());


		return result;
	}

	Datetime Datetime::FromYYMMDD(const std::string& str)
	{
		return Datetime::FromYYYYMMDD("20" + str);
	}

	Datetime Datetime::FromYYYYMMDD(const std::string& str)
	{
		Datetime result;

		if(DisplayFormats::HistoricalOrReferenceRequests_TryParseInput(str, result))
		{
			return result;
		}
		else
		{
			throw result.datetimeEx; //I don't know how to throw a static exception, so I simply declare an instance
		}
	}

	void Datetime::setDateTimeType(DateTimeTypeEnum dateTimeType)	{		this->_dateTimeType = dateTimeType;		this->_parts = (int)dateTimeType;	}

	Datetime::WeekDayEnum Datetime::getWeekDay() const
	{
		boost::gregorian::greg_weekday wd = this->_instance.date().day_of_week();
		Datetime::WeekDayEnum result = (Datetime::WeekDayEnum)(int)wd;
		return result;
	}

	void Datetime::addYears(int years)
	{
		this->addDays(years * 365); //this is not the right way to add years
		this->_parts |= DatetimeParts::YEAR;
	}

	void Datetime::addMonths(int months)
	{
		this->addDays(months * 30); //this is not the right way to add months
		this->_parts |= DatetimeParts::MONTH;
	}

	void Datetime::addDays(long days)
	{
		if(this->_dateTimeType == Datetime::time)
			this->_dateTimeType = Datetime::both; //if the user is adjusting days, assume that the dateTime is both date and time

		this->_instance += boost::gregorian::date_duration(days);
		this->_parts |= DatetimeParts::DAY;
	}

	void Datetime::addHours(long hours)
	{
		if(this->_dateTimeType == Datetime::date)
			this->_dateTimeType = Datetime::both; //if the user is adjusting hours, assume that the dateTime is both date and time

		this->_instance += boost::posix_time::hours(hours);
		this->_parts |= DatetimeParts::HOURS;
	}

	void Datetime::addMinutes(long minutes)
	{
		if(this->_dateTimeType == Datetime::date)
			this->_dateTimeType = Datetime::both; //if the user is adjusting minutes, assume that the dateTime is both date and time

		this->_instance += boost::posix_time::minutes(minutes);
		this->_parts |= DatetimeParts::MINUTES;
	}

	void Datetime::addSeconds(long seconds)
	{
		if(this->_dateTimeType == Datetime::date)
			this->_dateTimeType = Datetime::both; //if the user is adjusting seconds, assume that the dateTime is both date and time

		this->_instance += boost::posix_time::seconds(seconds);
		this->_parts |= DatetimeParts::SECONDS;
	}

	boost::posix_time::ptime Datetime::getInstance() const
	{
		return this->_instance;
	}

	unsigned Datetime::parts() const
	{
		return this->_parts;
	}

	bool Datetime::hasParts(unsigned parts) const
	{
		return (this->_parts & parts) > 0;
	}

	bool Datetime::isValid() const
	{
		return true;
	}

	bool Datetime::isLeapYear(int y)
	{
		return 0 == y % 4 && (y <= 1752 || 0 != y % 100 || 0 == y % 400); //Taken right from the BB API header file
	}

	unsigned Datetime::year() const
	{
		return this->_instance.date().year();
	}

	unsigned Datetime::month() const
	{
		return this->_instance.date().month();
	}

	unsigned Datetime::day() const
	{
		return this->_instance.date().day();
	}

	unsigned Datetime::hours() const
	{
		return this->_instance.time_of_day().hours();
	}

	unsigned Datetime::minutes() const
	{
		return this->_instance.time_of_day().minutes();
	}

	unsigned Datetime::seconds() const
	{
		return this->_instance.time_of_day().seconds();
	}

	unsigned Datetime::milliseconds() const
	{
		return (unsigned)this->_instance.time_of_day().total_milliseconds();
	}

	std::ostream& operator<<(std::ostream& os, const Datetime& datetime)
	{
		if(datetime._dateTimeType == BEmu::Datetime::date)
		{
			os << DisplayFormats::FormatDate(datetime);
		}

		else if(datetime._dateTimeType == BEmu::Datetime::time)
		{
			os << DisplayFormats::FormatTimeZone(datetime);
		}

		else if(datetime._dateTimeType == BEmu::Datetime::both)
		{
			os << DisplayFormats::FormatDatetimeZone(datetime);
		}

		return os;
	}

	bool operator==(const Datetime& lhs, const Datetime& rhs)
	{
		return 
			( lhs.year() == rhs.year() ) &&
			( lhs.month() == rhs.month() ) &&
			( lhs.day() == rhs.day() ) &&
			( lhs.hours() == rhs.hours() ) &&
			( lhs.minutes() == rhs.minutes() ) &&
			( lhs.seconds() == rhs.seconds() );
	}

	bool operator!=(const Datetime& lhs, const Datetime& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<(const Datetime& lhs, const Datetime& rhs)
	{
		if( lhs.year() == rhs.year() )
		{
			if( lhs.month() == rhs.month() )
			{
				if(lhs.day() == rhs.day())
				{
					if(lhs.hours() == rhs.hours())
					{
						if(lhs.minutes() == rhs.minutes())
							return lhs.seconds() < rhs.seconds();
						else
							return lhs.minutes() < rhs.minutes();
					}
					else
						return lhs.hours() < rhs.hours();
				}
				else
					return lhs.day() < rhs.day();
			}
			else
				return lhs.month() < rhs.month();
		}
		else
			return lhs.year() < rhs.year();

		//return lhs._instance < rhs._instance; //I can't get this to work
	}

	bool operator<=(const Datetime& lhs, const Datetime& rhs)
	{
		return (lhs < rhs) || (lhs == rhs);
	}
	
	bool operator>(const Datetime& lhs, const Datetime& rhs)
	{
		return !(lhs <= rhs);
	}
	
	bool operator>=(const Datetime& lhs, const Datetime& rhs)
	{
		return !(lhs < rhs);
	}

	bool Datetime::isValidDate(int year, int month, int day) //Taken from the BB API Datetime header file (I cleaned it up a little)
	{
		if ((year <= 0) || (year > 9999) || (month <= 0) || (month > 12) || (day <= 0) || (day > 31) )
		{
			return false;
		}
		if (day < 29)
		{
			return true;
		}
		if (year == 1752)
		{
			if (month == 9 && day > 2 && day < 14)
			{
				return false;
			}
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

			case 4:
			case 6:
			case 9:
			case 11:
				return day <= 30;

			case 2:
				return isLeapYear(year) ? (day <= 29) : (day <= 28);

			default: //control will never reach here
				return true;
		}
	}

	bool Datetime::isValidTime(int hours, int minutes, int seconds)
	{
		return (hours >= 0) && (hours < 24) && (minutes >= 0) && (minutes < 60) && (seconds >= 0) && (seconds < 60);
	}

	bool Datetime::isValidTime(int hours, int minutes, int seconds, int milliSeconds)
	{
		return (hours >= 0) && (hours < 24) && (minutes >= 0) && (minutes < 60) && (seconds >= 0) && (seconds < 60) && (milliSeconds >= 0) && (milliSeconds < 1000);
	}
}