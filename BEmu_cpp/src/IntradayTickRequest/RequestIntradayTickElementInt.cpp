//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/RequestIntradayTickElementInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/RequestIntradayTickElementInt.h"
#include "IntradayTickRequest/RequestIntradayTickElementString.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		RequestIntradayTickElementInt::RequestIntradayTickElementInt(std::string& elementName, int ivalue) : RequestIntradayTickElementString(elementName, ElementPtr::toCharPointer(ivalue))
		{
			this->_ivalue = ivalue;
		}

		int RequestIntradayTickElementInt::getInt()
		{
			return this->_ivalue;
		}
	}
}