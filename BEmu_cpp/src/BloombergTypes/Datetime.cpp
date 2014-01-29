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

		this->_dateTimeType = date;
	}

	Datetime::Datetime(int year, int month, int day, int hours, int minutes, int seconds)
	{
		this->_instance = boost::posix_time::ptime(
			boost::gregorian::date(year, month, day),
			boost::posix_time::time_duration(hours, minutes, seconds));

		this->_dateTimeType = both;
	}

	Datetime::Datetime(int hours, int minutes, int seconds, int milleseconds)
	{
		this->_instance = boost::posix_time::ptime(
			boost::posix_time::second_clock::local_time().date(),
			boost::posix_time::time_duration(hours, minutes, seconds, milleseconds));

		this->_dateTimeType = time;
	}

	Datetime::Datetime(int year, int month, int day, int hours, int minutes, int seconds, int milleseconds)
	{
		this->_instance = boost::posix_time::ptime(
			boost::gregorian::date(year, month, day),
			boost::posix_time::time_duration(hours, minutes, seconds, milleseconds));

		this->_dateTimeType = both;
	}

	Datetime::Datetime(const Datetime& arg)
	{
		this->_instance = boost::posix_time::ptime(arg._instance);

		this->_dateTimeType = arg._dateTimeType;
	}

	Datetime& Datetime::operator=(const Datetime &rhs)
	{
		if (this != &rhs)
		{
			this->_instance = boost::posix_time::ptime(rhs._instance);

			this->_dateTimeType = rhs._dateTimeType;
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

	Datetime::WeekDayEnum Datetime::getWeekDay() const
	{
		boost::gregorian::greg_weekday wd = this->_instance.date().day_of_week();
		Datetime::WeekDayEnum result = (Datetime::WeekDayEnum)(int)wd;
		return result;
	}

	void Datetime::addYears(int years)
	{
		this->addDays(years * 365); //this is not the right way to add years
	}

	void Datetime::addMonths(int months)
	{
		this->addDays(months * 30); //this is not the right way to add months
	}

	void Datetime::addDays(long days)
	{
		if(this->_dateTimeType == Datetime::time)
			this->_dateTimeType = Datetime::both; //if the user is adjusting days, assume that the dateTime is both date and time

		this->_instance += boost::gregorian::date_duration(days);
	}

	void Datetime::addHours(long hours)
	{
		if(this->_dateTimeType == Datetime::date)
			this->_dateTimeType = Datetime::both; //if the user is adjusting hours, assume that the dateTime is both date and time

		this->_instance += boost::posix_time::hours(hours);
	}

	void Datetime::addMinutes(long minutes)
	{
		if(this->_dateTimeType == Datetime::date)
			this->_dateTimeType = Datetime::both; //if the user is adjusting minutes, assume that the dateTime is both date and time

		this->_instance += boost::posix_time::minutes(minutes);
	}

	void Datetime::addSeconds(long seconds)
	{
		if(this->_dateTimeType == Datetime::date)
			this->_dateTimeType = Datetime::both; //if the user is adjusting seconds, assume that the dateTime is both date and time

		this->_instance += boost::posix_time::seconds(seconds);
	}

	boost::posix_time::ptime Datetime::getInstance() const
	{
		return this->_instance;
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
}