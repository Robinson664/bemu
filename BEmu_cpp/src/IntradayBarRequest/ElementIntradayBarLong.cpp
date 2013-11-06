//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/ElementIntradayBarLong.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayBarRequest/ElementIntradayBarLong.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementIntradayBarLong::ElementIntradayBarLong(const std::string& name, long value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementIntradayBarLong::~ElementIntradayBarLong()
		{
		}

		Name ElementIntradayBarLong::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}

		size_t ElementIntradayBarLong::numValues() const
		{
			return 1;
		}

		size_t ElementIntradayBarLong::numElements() const
		{
			return 0;
		}

		bool ElementIntradayBarLong::isArray() const
		{
			return false;
		}

		bool ElementIntradayBarLong::isComplexType() const
		{
			return false;
		}

		long ElementIntradayBarLong::getValueAsInt64(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementIntradayBarLong::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}



	}
}