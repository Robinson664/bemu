//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/RequestIntradayBarElementBool.h" company="Jordan Robinson">
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
		class RequestIntradayBarElementBool : public RequestIntradayBarElementString
		{
			private:
				bool _bvalue;

			public:
				RequestIntradayBarElementBool(const std::string& elementName, bool bvalue);
				~RequestIntradayBarElementBool();
				bool getBool() const;
		};
	}
}