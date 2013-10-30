//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTickElementInt.h" company="Jordan Robinson">
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
	namespace IntradayTickRequest
	{
		class RequestIntradayTickElementInt : public RequestIntradayTickElementString
		{
			private:
				int _ivalue;

			public:
				RequestIntradayTickElementInt(std::string& elementName, int ivalue);
				int getInt();
		};
	}
}