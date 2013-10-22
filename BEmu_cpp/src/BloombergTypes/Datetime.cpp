//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/Datetime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Datetime.h"
#include <boost/date_time/posix_time/posix_time_io.hpp>

namespace BEmu
{
	Datetime::Datetime(int year, int month, int day)
	{
		this->_instance = new boost::posix_time::ptime(boost::gregorian::date(year, month, day));
		this->_dateTimeType = date;
	}

	Datetime::Datetime(int year, int month, int day, int hours, int minutes, int seconds)
	{
		this->_instance = new boost::posix_time::ptime(
			boost::gregorian::date(year, month, day),
			boost::posix_time::time_duration(hours, minutes, seconds));
		this->_dateTimeType = both;
	}

	Datetime::Datetime(int hours, int minutes, int seconds, int milleseconds)
	{
		this->_instance = new boost::posix_time::ptime(
			boost::posix_time::second_clock::local_time().date(),
			boost::posix_time::time_duration(hours, minutes, seconds, milleseconds));
		this->_dateTimeType = time;
	}

	Datetime::Datetime(int year, int month, int day, int hours, int minutes, int seconds, int milleseconds)
	{
		this->_instance = new boost::posix_time::ptime(
			boost::gregorian::date(year, month, day),
			boost::posix_time::time_duration(hours, minutes, seconds, milleseconds));
		this->_dateTimeType = both;
	}

	Datetime::Datetime(const Datetime& arg)
	{
		this->_instance = new boost::posix_time::ptime(*arg._instance);
		this->_dateTimeType = arg._dateTimeType;
	}

	Datetime& Datetime::operator=(const Datetime &rhs)
	{
		if (this != &rhs)
		{
			this->_instance = new boost::posix_time::ptime(*rhs._instance);
			this->_dateTimeType = rhs._dateTimeType;
		}
		return *this;
	}

	//Datetime::Datetime(boost::posix_time::ptime arg)
	//{
	//	this->_instance = new boost::posix_time::ptime(arg);

	//	bool isDate = arg.date().year() != 0;
	//	bool isTime = arg.time_of_day().hours() != 0 || arg.time_of_day().minutes() != 0 || arg.time_of_day().seconds() != 0;

	//	if(isDate)
	//	{
	//		if(isTime)
	//			this->_dateTimeType = both;
	//		else
	//			this->_dateTimeType = date;
	//	}
	//	else if(isTime)
	//		this->_dateTimeType = time;
	//}

	Datetime::~Datetime()
	{
		delete this->_instance;
		this->_instance = 0;
	}

	unsigned Datetime::year() const
	{
		return this->_instance->date().year();
	}

	unsigned Datetime::month() const
	{
		return this->_instance->date().month();
	}

	unsigned Datetime::day() const
	{
		return this->_instance->date().day();
	}

	unsigned Datetime::hours() const
	{
		return this->_instance->time_of_day().hours();
	}

	unsigned Datetime::minutes() const
	{
		return this->_instance->time_of_day().minutes();
	}

	unsigned Datetime::seconds() const
	{
		return this->_instance->time_of_day().seconds();
	}

	std::ostream& operator<<(std::ostream& os, const Datetime& datetime)
	{
		//std::locale takes ownership of this "facet" pointer, so I don't have to delete it
		boost::posix_time::time_facet *facet;

		if(datetime._dateTimeType == BEmu::Datetime::date)
		{
			facet = new boost::posix_time::time_facet("%d-%b-%Y");
			os.imbue(std::locale(os.getloc(), facet));
			os << *(datetime._instance);
		}

		else if(datetime._dateTimeType == BEmu::Datetime::time)
		{
			facet = new boost::posix_time::time_facet("%H:%M:%S");
			os.imbue(std::locale(os.getloc(), facet));
			os << *(datetime._instance);
		}

		else if(datetime._dateTimeType == BEmu::Datetime::both)
		{
			facet = new boost::posix_time::time_facet("%d-%b-%YT%H:%M:%S");
			os.imbue(std::locale(os.getloc(), facet));
			os << *(datetime._instance);
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