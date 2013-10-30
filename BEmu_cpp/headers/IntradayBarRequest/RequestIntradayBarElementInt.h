//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/RequestIntradayBarElementInt.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "IntradayBarRequest/RequestIntradayBarElementString.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		class RequestIntradayBarElementInt : public RequestIntradayBarElementString
		{
			private:
				int _ivalue;

			public:
				RequestIntradayBarElementInt(const std::string& elementName, int ivalue);
				~RequestIntradayBarElementInt();
				int getInt() const;
		};
	}
}