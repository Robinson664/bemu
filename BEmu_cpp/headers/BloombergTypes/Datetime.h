//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/Datetime.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost\date_time\gregorian\gregorian.hpp>

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class EventIntradayTick;
	}
	
	class Datetime
	{
		private:
			boost::posix_time::ptime *_instance;
			enum DateTimeTypeEnum { neither = 0, date = 1, time = 2, both = 3 };
			DateTimeTypeEnum _dateTimeType;

		public:
			DLL_EXPORT Datetime::Datetime(int year, int month, int day);
			DLL_EXPORT Datetime::Datetime(int year, int month, int day, int hours, int minutes, int seconds);
			DLL_EXPORT Datetime::Datetime(int hours, int minutes, int seconds, int milleseconds);
			DLL_EXPORT Datetime::Datetime(int year, int month, int day, int hours, int minutes, int seconds, int milleseconds);
			DLL_EXPORT Datetime::Datetime(const Datetime& arg);
			//DLL_EXPORT Datetime::Datetime(boost::posix_time::ptime arg);
			DLL_EXPORT Datetime& operator=(const Datetime &rhs);

			DLL_EXPORT Datetime::~Datetime();
		
			DLL_EXPORT unsigned year() const;
			DLL_EXPORT unsigned month() const;
			DLL_EXPORT unsigned day() const;
			DLL_EXPORT unsigned hours() const;
			DLL_EXPORT unsigned minutes() const;
			DLL_EXPORT unsigned seconds() const;

			friend DLL_EXPORT bool operator<(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator<=(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator>(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator>=(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator==(const Datetime& lhs, const Datetime& rhs);
			friend DLL_EXPORT bool operator!=(const Datetime& lhs, const Datetime& rhs);
			
			friend DLL_EXPORT std::ostream& operator<<(std::ostream& os, const Datetime& datetime);

			friend class IntradayTickRequest::EventIntradayTick;
	};

	DLL_EXPORT bool operator<(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT bool operator<=(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT bool operator>(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT bool operator>=(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT bool operator==(const Datetime& lhs, const Datetime& rhs);
	DLL_EXPORT std::ostream& operator<<(std::ostream& os, const Datetime& datetime);
}