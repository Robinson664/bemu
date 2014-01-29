//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/Types/DisplayFormats.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include <iosfwd>
#include <string>
#include "BloombergTypes\Datetime.h"

using namespace std;

namespace BEmu
{
	class DisplayFormats
	{
		private:
			static string Format(Datetime dt, const char * format);

		public:
			static string ToMMddYYWithSlashes(Datetime date);
			static string ToYYYYMMDDWithDashes(Datetime date);

			static string FormatNumberNoSeparators(double dbl, int numDecimals = 0);
			static string FormatDate(Datetime date);
			static string FormatTimeZone(Datetime time);
			static string FormatDatetimeZone(Datetime datetime);

			static string MarketDataRequests_FormatDateZone(Datetime date);

			static string HistoricalOrReferenceRequests_FormatDate(Datetime date);
			static bool HistoricalOrReferenceRequests_TryParseInput(string str, Datetime & dt);

			static string IntradayRequests_FormatDatetime(Datetime datetime);
	};
}