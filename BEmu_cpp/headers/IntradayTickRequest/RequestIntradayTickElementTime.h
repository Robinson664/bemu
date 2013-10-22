//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTickElementTime.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\ElementPtr.h"
#include "BloombergTypes\Datetime.h"
#include "IntradayTickRequest/RequestIntradayTickElementString.h"

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class RequestIntradayTick;

		class RequestIntradayTickElementTime : private RequestIntradayTickElementString
		{
			private:
				Datetime* _instance;
				RequestIntradayTickElementTime(const std::string& elementName);
				RequestIntradayTickElementTime(const std::string& elementName, const Datetime& date);
				~RequestIntradayTickElementTime();
				Datetime* getDate();

			public:
				friend class RequestIntradayTick; //RequestIntradayTick::getDates needs access to getDate()
		};
	}
}