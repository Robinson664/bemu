//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/Types/DisplayFormats.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "Types/DisplayFormats.h"
#include <boost/date_time/gregorian_calendar.hpp>
#include <sstream>

namespace BEmu
{
	string DisplayFormats::FormatNumberNoSeparators(double dbl, int numDecimals)
	{
		stringstream ss;
		ss << std::fixed << std::setprecision(numDecimals) << dbl << endl;

		string result(ss.str());
		return result;
	}

	string DisplayFormats::Format(const Datetime& dt, const char * format)
	{
		//std::locale takes ownership of this "facet" pointer, so I don't have to delete it http://rhubbarb.wordpress.com/2009/10/17/boost-datetime-locales-and-facets/
		boost::posix_time::time_facet * facet = new boost::posix_time::time_facet(format);

		stringstream ss;		
		ss.imbue(std::locale(ss.getloc(), facet));
		ss << dt.getInstance();

		string result(ss.str());
		return result;
	}

	string DisplayFormats::ToYYYYMMddNoSeparatorsWithQuotes(const Datetime& date)
	{
		string result(DisplayFormats::Format(date, "\"%Y%m%d\"")); // "20130514"
		return result;
	}

	string DisplayFormats::ToMMddYYWithSlashes(const Datetime& date)
	{
		string result(DisplayFormats::Format(date, "%m/%d/%y")); //obviously US format
		return result;
	}

	string DisplayFormats::ToYYYYMMDDWithDashes(const Datetime& date)
	{
		string result(DisplayFormats::Format(date, "%Y-%m-%d"));
		return result;
	}

	string DisplayFormats::FormatDate(const Datetime& date)  //mkt data has time zone information, but the other requests don't
	{
		string result(DisplayFormats::Format(date, "%Y-%m-%d"));
		return result;
	}

	string DisplayFormats::FormatTimeZone(const Datetime& time)
	{
		string result(DisplayFormats::Format(time, "%H:%M:%S.%f%q"));
		return result;
	}

	string DisplayFormats::FormatDatetimeZone(const Datetime& datetime)
	{
		string result(DisplayFormats::Format(datetime, "%Y-%m-%dT%H:%M:%S.%f%q"));
		return result;
	}

	string DisplayFormats::MarketDataRequests_FormatDateZone(const Datetime& date)
	{
		string result(DisplayFormats::Format(date, "%Y-%m-%d%q"));
		return result;
	}

	string DisplayFormats::HistoricalOrReferenceRequests_FormatDate(const Datetime& date)
	{
		string result(DisplayFormats::Format(date, "%Y-%m-%d"));
		return result;
	}

	bool DisplayFormats::HistoricalOrReferenceRequests_TryParseInput(const string& str, Datetime & dt)
	{
		try
		{
			boost::gregorian::date date(boost::gregorian::from_undelimited_string(str));
			dt = Datetime(date.year(), date.month(), date.day());
			return true;
		}
		catch(...)
		{
			return false;
		}
	}

	string DisplayFormats::IntradayRequests_FormatDatetime(const Datetime& datetime)
	{
		string result(DisplayFormats::Format(datetime, "%Y-%m-%dT%H:%M:%S.%f"));
		return result;
	}

	string DisplayFormats::IntradayRequests_FormatDatetime_SecondsLast(const Datetime& datetime)
	{
		string result(DisplayFormats::Format(datetime, "%Y-%m-%dT%H:%M:%S"));
		return result;
	}
}