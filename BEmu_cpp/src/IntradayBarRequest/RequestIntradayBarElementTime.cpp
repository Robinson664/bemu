//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/IntradayBarRequestElementTime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/Datetime.h"
#include "BloombergTypes/ElementPtr.h"
#include "IntradayBarRequest/IntradayBarRequestElementTime.h"
#include "Types/DisplayFormats.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		IntradayBarRequestElementTime::IntradayBarRequestElementTime(const std::string& elementName) : IntradayBarRequestElementString(elementName, "")
		{
			this->_value = "";
		}
		
		IntradayBarRequestElementTime::IntradayBarRequestElementTime(const std::string& elementName, const Datetime& dtvalue) : IntradayBarRequestElementString(elementName, "")
		{
			this->_value = DisplayFormats::ToYYYYMMDDWithDashes(dtvalue);
			this->_dtvalue = dtvalue;
		}

		IntradayBarRequestElementTime::~IntradayBarRequestElementTime()
		{
		}

		Datetime IntradayBarRequestElementTime::getDatetime() const
		{
			return this->_dtvalue;
		}

	}
}