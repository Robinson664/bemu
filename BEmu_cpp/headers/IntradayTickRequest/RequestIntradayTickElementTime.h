//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTickElementTime.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "IntradayTickRequest/RequestIntradayTickElementString.h"

namespace BEmu
{
	class Datetime;

	namespace IntradayTickRequest
	{
		class RequestIntradayTickElementTime : public RequestIntradayTickElementString
		{
			private:
				Datetime _instance;

			public:
				RequestIntradayTickElementTime(const std::string& elementName);
				RequestIntradayTickElementTime(const std::string& elementName, const Datetime& date);
				~RequestIntradayTickElementTime();
				Datetime getDate();
		};
	}
}