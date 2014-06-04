//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/IntradayTickRequestElementTime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/IntradayTickRequestElementTime.h"
#include "IntradayTickRequest/IntradayTickRequestElementString.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		IntradayTickRequestElementTime::IntradayTickRequestElementTime(const std::string& elementName) : IntradayTickRequestElementString(elementName, "")
		{
		}

		IntradayTickRequestElementTime::IntradayTickRequestElementTime(const std::string& elementName, const Datetime& date) : IntradayTickRequestElementString(elementName, ElementPtr::toCharPointer(date))
		{
			this->_instance = date;
		}

		IntradayTickRequestElementTime::~IntradayTickRequestElementTime()
		{
		}

		Datetime IntradayTickRequestElementTime::getDate()
		{
			return this->_instance;
		}

	}
}