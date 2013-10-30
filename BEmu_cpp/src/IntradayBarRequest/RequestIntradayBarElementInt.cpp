//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/RequestIntradayBarElementInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "IntradayBarRequest/RequestIntradayBarElementInt.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		RequestIntradayBarElementInt::RequestIntradayBarElementInt(const std::string& elementName, int ivalue) : RequestIntradayBarElementString(elementName, "")
		{
			std::stringstream ss;
			ss << ivalue;
			this->_value = ss.str();

			this->_ivalue = ivalue;
		}

		RequestIntradayBarElementInt::~RequestIntradayBarElementInt()
		{
		}

		int RequestIntradayBarElementInt::getInt() const
		{
			return this->_ivalue;
		}

	}
}