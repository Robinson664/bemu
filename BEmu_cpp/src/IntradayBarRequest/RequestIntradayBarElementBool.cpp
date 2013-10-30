//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/RequestIntradayBarElementBool.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "IntradayBarRequest/RequestIntradayBarElementBool.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		RequestIntradayBarElementBool::RequestIntradayBarElementBool(const std::string& elementName, bool bvalue) : RequestIntradayBarElementString(elementName, "")
		{
			this->_value = bvalue ? "true" : "false";
			this->_bvalue = bvalue;
		}

		RequestIntradayBarElementBool::~RequestIntradayBarElementBool()
		{
		}

		bool RequestIntradayBarElementBool::getBool() const
		{
			return this->_bvalue;
		}

	}
}