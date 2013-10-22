//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/RequestIntradayTickElementBool.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "IntradayTickRequest/RequestIntradayTickElementBool.h"
#include "IntradayTickRequest/RequestIntradayTickElementString.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		RequestIntradayTickElementBool::RequestIntradayTickElementBool(std::string& elementName, bool bvalue) : RequestIntradayTickElementString(elementName, bvalue ? "True" : "False")
		{
			this->_bvalue = bvalue;
		}

		bool RequestIntradayTickElementBool::getBool()
		{
			return this->_bvalue;
		}
	}
}