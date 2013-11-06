//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementIntradayTickDataParent.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/ElementIntradayTickDataParent.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "Types/IndentType.h"
#include <map>
#include "IntradayTickRequest/ElementIntradayTickDataTuple3.h"
#include "IntradayTickRequest/ElementIntradayTickDataArray.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		//makes copies of the arguments
		ElementIntradayTickDataParent::ElementIntradayTickDataParent(std::map<Datetime, ElementIntradayTickDataTuple3*>* ticks, bool includeConditionCodes)
		{
			this->_array = new ElementIntradayTickDataArray(ticks, includeConditionCodes);
		}

		ElementIntradayTickDataParent::~ElementIntradayTickDataParent()
		{
			delete this->_array;
			this->_array = 0;
		}

		Name ElementIntradayTickDataParent::name() const
		{
			Name result("tickData");
			return result;
		}

		ElementPtr * ElementIntradayTickDataParent::getElement(const char* name) const
		{
			if(this->_array->name() == name)
				return this->_array;

			else
				throw elementPtrEx;
		}

		std::ostream& ElementIntradayTickDataParent::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);

			stream << tabs << "tickData = {" << std::endl;
			this->_array->print(stream, level + 1, spacesPerLevel);
			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}