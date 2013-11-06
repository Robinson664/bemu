//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/RequestIntradayBarElementTime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/Datetime.h"
#include "BloombergTypes/ElementPtr.h"
#include "IntradayBarRequest/RequestIntradayBarElementTime.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		RequestIntradayBarElementTime::RequestIntradayBarElementTime(const std::string& elementName) : RequestIntradayBarElementString(elementName, "")
		{
			this->_value = "";
		}
		
		RequestIntradayBarElementTime::RequestIntradayBarElementTime(const std::string& elementName, const Datetime& dtvalue) : RequestIntradayBarElementString(elementName, "")
		{
			this->_value = dtvalue.ToYYYYMMDD();
			this->_dtvalue = dtvalue;
		}

		RequestIntradayBarElementTime::~RequestIntradayBarElementTime()
		{
		}

		Datetime RequestIntradayBarElementTime::getDatetime() const
		{
			return this->_dtvalue;
		}

	}
}