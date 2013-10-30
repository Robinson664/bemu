//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/ElementIntradayBarString.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayBarRequest/ElementIntradayBarString.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementIntradayBarString::ElementIntradayBarString(const std::string& name, const std::string& value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementIntradayBarString::~ElementIntradayBarString()
		{
		}

		Name ElementIntradayBarString::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}

		int ElementIntradayBarString::numValues() const
		{
			return 1;
		}

		int ElementIntradayBarString::numElements() const
		{
			return 0;
		}

		bool ElementIntradayBarString::isArray() const
		{
			return false;
		}

		bool ElementIntradayBarString::isComplexType() const
		{
			return false;
		}

		char* ElementIntradayBarString::getValueAsString(int index) const
		{
			if(index == 0)
				return ElementPtr::toCharPointer(this->_value);
			else
				throw elementPtrEx;
		}

		std::ostream& ElementIntradayBarString::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}



	}
}