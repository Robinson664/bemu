//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTickElementBool.h" company="Jordan Robinson">
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
		class RequestIntradayTickElementBool : public RequestIntradayTickElementString
		{
			private:
				bool _bvalue;

			public:
				RequestIntradayTickElementBool(std::string& elementName, bool bvalue);
				bool getBool();
		};
	}
}