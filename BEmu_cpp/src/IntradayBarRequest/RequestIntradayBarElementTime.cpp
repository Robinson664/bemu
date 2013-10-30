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
			this->_dtvalue = 0;
		}
		
		RequestIntradayBarElementTime::RequestIntradayBarElementTime(const std::string& elementName, const Datetime& dtvalue) : RequestIntradayBarElementString(elementName, "")
		{
			std::stringstream ss;
			ss << dtvalue.year();

			if(dtvalue.month() < 10)
				ss << '0';
			ss << dtvalue.month();

			if(dtvalue.day() < 10)
				ss << '0';
			ss << dtvalue.day();

			this->_value = ss.str();

			this->_dtvalue = new Datetime(dtvalue);
		}

		RequestIntradayBarElementTime::~RequestIntradayBarElementTime()
		{
			delete this->_dtvalue;
			this->_dtvalue = 0;
		}

		Datetime * RequestIntradayBarElementTime::getDatetime() const
		{
			return this->_dtvalue;
		}

	}
}