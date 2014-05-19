//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/IntradayBarRequestElementInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "IntradayBarRequest/IntradayBarRequestElementInt.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		IntradayBarRequestElementInt::IntradayBarRequestElementInt(const std::string& elementName, int ivalue) : IntradayBarRequestElementString(elementName, "")
		{
			std::stringstream ss;
			ss << ivalue;
			this->_value = ss.str();

			this->_ivalue = ivalue;
		}

		IntradayBarRequestElementInt::~IntradayBarRequestElementInt()
		{
		}

		int IntradayBarRequestElementInt::getInt() const
		{
			return this->_ivalue;
		}

	}
}