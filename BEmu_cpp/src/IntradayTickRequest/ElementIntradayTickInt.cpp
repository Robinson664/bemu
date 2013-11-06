//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementIntradayTickInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/ElementIntradayTickInt.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		ElementIntradayTickInt::ElementIntradayTickInt(const std::string& name, int value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementIntradayTickInt::~ElementIntradayTickInt()
		{
		}

		Name ElementIntradayTickInt::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}

		size_t ElementIntradayTickInt::numValues() const
		{
			return 1;
		}

		size_t ElementIntradayTickInt::numElements() const
		{
			return 0;
		}

		bool ElementIntradayTickInt::isArray() const
		{
			return false;
		}

		bool ElementIntradayTickInt::isComplexType() const
		{
			return false;
		}
		
		bool ElementIntradayTickInt::hasElement(const char* name, bool excludeNullElements) const
		{
			return false;
		}

		std::ostream& ElementIntradayTickInt::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

		int ElementIntradayTickInt::getValueAsInt32(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		long ElementIntradayTickInt::getValueAsInt64(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}
		
		float ElementIntradayTickInt::getValueAsFloat32(int index) const
		{
			if(index == 0)
				return (float)this->_value;
			else
				throw elementPtrEx;
		}

		double ElementIntradayTickInt::getValueAsFloat64(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		const char * ElementIntradayTickInt::getValueAsString(int index) const
		{
			if(index == 0)
			{
				const char * result = ElementPtr::toCharPointer(this->_value);
				return result;
			}
			else
				throw elementPtrEx;
		}



	}
}