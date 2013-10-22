//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTickElementInt.h" company="Jordan Robinson">
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
		class RequestIntradayTickElementInt : private RequestIntradayTickElementString
		{
			private:
				int _ivalue;
				RequestIntradayTickElementInt(std::string& elementName, int ivalue);
				int getInt();
		};
	}
}