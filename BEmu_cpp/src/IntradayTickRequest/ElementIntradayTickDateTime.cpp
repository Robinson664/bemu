//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementIntradayTickDateTime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/ElementIntradayTickDateTime.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "BloombergTypes/Datetime.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		ElementIntradayTickDateTime::ElementIntradayTickDateTime(const std::string& name, const Datetime& value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementIntradayTickDateTime::~ElementIntradayTickDateTime()
		{
		}

		std::ostream& ElementIntradayTickDateTime::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

		Name ElementIntradayTickDateTime::name() const
		{
			return Name("time");
		}

		bool ElementIntradayTickDateTime::hasElement(const char* name, bool excludeNullElements) const
		{
			return false;
		}

		Datetime ElementIntradayTickDateTime::getValueAsDatetime(int index) const
		{
			return this->_value;
		}

		const char * ElementIntradayTickDateTime::getValueAsString(int index) const
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