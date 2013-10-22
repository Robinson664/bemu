//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTickElementBool.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\ElementPtr.h"
#include "IntradayTickRequest/RequestIntradayTickElementString.h"

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class RequestIntradayTick;

		class RequestIntradayTickElementBool : private RequestIntradayTickElementString
		{
			private:
				bool _bvalue;
				RequestIntradayTickElementBool(std::string& elementName, bool bvalue);
				bool getBool();

			public:
				friend class RequestIntradayTick; //RequestIntradayTick::includeConditionCodes() needs access to getBool()
		};
	}
}