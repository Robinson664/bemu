//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/IntradayTickRequestElementBool.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/IntradayTickRequestElementBool.h"
#include "IntradayTickRequest/IntradayTickRequestElementString.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		IntradayTickRequestElementBool::IntradayTickRequestElementBool(std::string& elementName, bool bvalue) : IntradayTickRequestElementString(elementName, bvalue ? "True" : "False")
		{
			this->_bvalue = bvalue;
		}

		bool IntradayTickRequestElementBool::getBool()
		{
			return this->_bvalue;
		}
	}
}