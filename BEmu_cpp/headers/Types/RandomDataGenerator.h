//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/Types/RandomDataGenerator.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include <random>
#include <map>
#include <list>
#include "Types/ObjectType.h"
#include "IntradayBarRequest/BarTickDataType.h"
#include "BloombergTypes/Datetime.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		class RequestReference;
	}

	class RandomDataGenerator
	{
		public:
			static int RandomInt(int max);
			static int RandomInt(int min, int max);
		
			static bool ShouldIncludeQuote();
			static boost::posix_time::ptime::time_duration_type TimeBetweenMarketDataEvents();
			static int IntradayTickTradeSize();
			static int Strike();
			static Datetime RandomDate();
			static Datetime RandomTime();
			static Datetime RandomDatetime();
			static double RandomDouble();
			static double RandomDouble(double min, double max);
			static char RandomChar();
			static std::string RandomString();
			static std::string RandomString(int length);
			static bool RandomBool();
			static std::map<std::string, ObjectType> GetMarketDataFields(const std::list<std::string>& arg);
			static ObjectType MarketDataFromFieldName(std::string* arg);

			static IntradayBarRequest::BarTickDataType * GenerateBarData(const Datetime& date);

			static int IntradayTickIntervalInMinutes();

			static ObjectType ReferenceDataFromFieldName(const std::string& fieldName, const std::string& security, bool isOption, ReferenceDataRequest::RequestReference * rreq);
	};
}