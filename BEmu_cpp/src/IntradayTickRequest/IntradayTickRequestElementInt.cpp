//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/IntradayTickRequestElementInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/IntradayTickRequestElementInt.h"
#include "IntradayTickRequest/IntradayTickRequestElementString.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		IntradayTickRequestElementInt::IntradayTickRequestElementInt(std::string& elementName, int ivalue) : IntradayTickRequestElementString(elementName, ElementPtr::toCharPointer(ivalue))
		{
			this->_ivalue = ivalue;
		}

		int IntradayTickRequestElementInt::getInt()
		{
			return this->_ivalue;
		}
	}
}