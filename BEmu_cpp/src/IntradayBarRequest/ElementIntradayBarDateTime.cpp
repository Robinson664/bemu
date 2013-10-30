//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/ElementIntradayBarDateTime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayBarRequest/ElementIntradayBarDateTime.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementIntradayBarDateTime::ElementIntradayBarDateTime(const std::string& name, const Datetime& value)
		{
			this->_name = name;
			this->_value = new Datetime(value);
		}

		ElementIntradayBarDateTime::~ElementIntradayBarDateTime()
		{
			delete this->_value;
			this->_value = 0;
		}

		Name ElementIntradayBarDateTime::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}

		int ElementIntradayBarDateTime::numValues() const
		{
			return 1;
		}

		int ElementIntradayBarDateTime::numElements() const
		{
			return 0;
		}

		bool ElementIntradayBarDateTime::isArray() const
		{
			return false;
		}

		bool ElementIntradayBarDateTime::isComplexType() const
		{
			return false;
		}

		Datetime ElementIntradayBarDateTime::getValueAsDatetime(int index) const
		{
			if(index == 0)
				return *(this->_value);
			else
				throw elementPtrEx;
		}

		char* ElementIntradayBarDateTime::getValueAsString(int index) const
		{
			if(index == 0)
				return ElementPtr::toCharPointer(this->_value);
			else
				throw elementPtrEx;
		}

		std::ostream& ElementIntradayBarDateTime::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}



	}
}