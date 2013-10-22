//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/RequestIntradayTickElementTime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "IntradayTickRequest/RequestIntradayTickElementTime.h"
#include "IntradayTickRequest/RequestIntradayTickElementString.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		RequestIntradayTickElementTime::RequestIntradayTickElementTime(const std::string& elementName) : RequestIntradayTickElementString(elementName, "")
		{
			this->_instance = 0;
		}

		RequestIntradayTickElementTime::RequestIntradayTickElementTime(const std::string& elementName, const Datetime& date) : RequestIntradayTickElementString(elementName, ElementPtr::toCharPointer(date))
		{	
			this->_instance = new Datetime(date);
		}

		RequestIntradayTickElementTime::~RequestIntradayTickElementTime()
		{
			delete this->_instance;
			this->_instance = 0;
		}

		Datetime* RequestIntradayTickElementTime::getDate()
		{
			return this->_instance;
		}

	}
}