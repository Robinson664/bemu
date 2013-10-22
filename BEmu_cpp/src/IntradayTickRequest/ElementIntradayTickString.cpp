//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementIntradayTickString.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "IntradayTickRequest/ElementIntradayTickString.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		ElementIntradayTickString::ElementIntradayTickString(const std::string& name, const std::string& value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementIntradayTickString::~ElementIntradayTickString()
		{
		}

		Name ElementIntradayTickString::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}
		
		bool ElementIntradayTickString::hasElement(const char* name, bool excludeNullElements) const
		{
			return false;
		}

		std::ostream& ElementIntradayTickString::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

		char* ElementIntradayTickString::getValueAsString(int index = 0) const
		{
			if(index == 0)
			{
				char* result = ElementPtr::toCharPointer(this->_value);
				return result;
			}
			else
				throw elementPtrEx;
		}
	}
}