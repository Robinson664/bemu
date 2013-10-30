//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementIntradayTickDouble.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/ElementIntradayTickDouble.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		ElementIntradayTickDouble::ElementIntradayTickDouble(const std::string& name, double value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementIntradayTickDouble::~ElementIntradayTickDouble()
		{
		}

		Name ElementIntradayTickDouble::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}
		
		bool ElementIntradayTickDouble::hasElement(const char* name, bool excludeNullElements) const
		{
			return false;
		}

		std::ostream& ElementIntradayTickDouble::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

		int ElementIntradayTickDouble::getValueAsInt32(int index) const
		{
			if(index == 0)
				return (int)this->_value;
			else
				throw elementPtrEx;
		}

		long ElementIntradayTickDouble::getValueAsInt64(int index) const
		{
			if(index == 0)
				return (long)this->_value;
			else
				throw elementPtrEx;
		}
		
		float ElementIntradayTickDouble::getValueAsFloat32(int index) const
		{
			if(index == 0)
				return (float)this->_value;
			else
				throw elementPtrEx;
		}

		double ElementIntradayTickDouble::getValueAsFloat64(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		char* ElementIntradayTickDouble::getValueAsString(int index = 0) const
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