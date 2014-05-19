//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/ElementIntradayBarInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayBarRequest/ElementIntradayBarInt.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementIntradayBarInt::ElementIntradayBarInt(const std::string& name, int value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementIntradayBarInt::~ElementIntradayBarInt()
		{
		}

		Name ElementIntradayBarInt::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}

		size_t ElementIntradayBarInt::numValues() const
		{
			return 1;
		}

		size_t ElementIntradayBarInt::numElements() const
		{
			return 0;
		}

		bool ElementIntradayBarInt::isArray() const
		{
			return false;
		}

		bool ElementIntradayBarInt::isComplexType() const
		{
			return false;
		}

		int ElementIntradayBarInt::getValueAsInt32(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementIntradayBarInt::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}
	}
}