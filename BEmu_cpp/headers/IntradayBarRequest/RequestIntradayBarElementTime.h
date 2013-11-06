//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/RequestIntradayBarElementTime.h" company="Jordan Robinson">
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
	class Datetime;

	namespace IntradayBarRequest
	{
		class RequestIntradayBarElementTime : public RequestIntradayBarElementString
		{
			private:
				Datetime _dtvalue;

			public:
				RequestIntradayBarElementTime(const std::string& elementName);
				RequestIntradayBarElementTime(const std::string& elementName, const Datetime& dtvalue);
				~RequestIntradayBarElementTime();
				Datetime getDatetime() const;
		};
	}
}