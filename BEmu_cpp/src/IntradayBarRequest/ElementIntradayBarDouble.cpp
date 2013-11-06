//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/ElementIntradayBarDouble.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayBarRequest/ElementIntradayBarDouble.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementIntradayBarDouble::ElementIntradayBarDouble(const std::string& name, double value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementIntradayBarDouble::~ElementIntradayBarDouble()
		{
		}

		Name ElementIntradayBarDouble::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}

		size_t ElementIntradayBarDouble::numValues() const
		{
			return 1;
		}

		size_t ElementIntradayBarDouble::numElements() const
		{
			return 0;
		}

		bool ElementIntradayBarDouble::isArray() const
		{
			return false;
		}

		bool ElementIntradayBarDouble::isComplexType() const
		{
			return false;
		}

		double ElementIntradayBarDouble::getValueAsFloat64(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		int ElementIntradayBarDouble::getValueAsInt32(int index) const
		{
			if(index == 0)
				return (int)this->_value;
			else
				throw elementPtrEx;
		}

		const char * ElementIntradayBarDouble::getValueAsString(int index) const
		{
			if(index == 0)
				return ElementPtr::toCharPointer(this->_value);
			else
				throw elementPtrEx;
		}

		std::ostream& ElementIntradayBarDouble::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}



	}
}