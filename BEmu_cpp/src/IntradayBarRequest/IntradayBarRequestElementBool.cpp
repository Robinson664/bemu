//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/IntradayBarRequestElementBool.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "IntradayBarRequest/IntradayBarRequestElementBool.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		IntradayBarRequestElementBool::IntradayBarRequestElementBool(const std::string& elementName, bool bvalue) : IntradayBarRequestElementString(elementName, "")
		{
			this->_value = bvalue ? "true" : "false";
			this->_bvalue = bvalue;
		}

		IntradayBarRequestElementBool::~IntradayBarRequestElementBool()
		{
		}

		bool IntradayBarRequestElementBool::getBool() const
		{
			return this->_bvalue;
		}

	}
}