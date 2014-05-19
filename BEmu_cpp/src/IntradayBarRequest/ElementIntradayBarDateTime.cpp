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
#include "Types/DisplayFormats.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementIntradayBarDateTime::ElementIntradayBarDateTime(const std::string& name, const Datetime& value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementIntradayBarDateTime::~ElementIntradayBarDateTime()
		{
		}

		Name ElementIntradayBarDateTime::name() const
		{
			return Name(this->_name.c_str());
		}

		size_t ElementIntradayBarDateTime::numValues() const
		{
			return 1;
		}

		size_t ElementIntradayBarDateTime::numElements() const
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
				return this->_value;
			else
				throw elementPtrEx;
		}

		const char * ElementIntradayBarDateTime::getValueAsString(int index) const
		{
			if(index == 0)
				return ElementPtr::toCharPointer(this->_value);
			else
				throw elementPtrEx;
		}

		std::ostream& ElementIntradayBarDateTime::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string strvalue(DisplayFormats::IntradayRequests_FormatDatetime(this->_value));
			this->prettyPrintHelper(stream, level, spacesPerLevel, strvalue);
			return stream;
		}
	}
}