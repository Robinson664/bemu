//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/ElementBarData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include <vector>
#include "IntradayBarRequest/ElementBarData.h"
#include "IntradayBarRequest/ElementBarTickDataArray.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementBarData::ElementBarData(const std::vector<BarTickDataType*>& bars)
		{
			this->_array = new ElementBarTickDataArray(bars);
		}

		ElementBarData::~ElementBarData()
		{
			delete this->_array;
		}

		Name ElementBarData::name() const
		{
			Name result("barData");
			return result;
		}

		int ElementBarData::numValues() const
		{
			return 1;
		}

		int ElementBarData::numElements() const
		{
			return 1;
		}

		bool ElementBarData::isArray() const
		{
			return false;
		}

		bool ElementBarData::isComplexType() const
		{
			return true;
		}

		ElementPtr * ElementBarData::getElement(const char* name) const
		{
			int length = strlen(name);
			
			if(strncmp(this->_array->name().string(), name, length) == 0)
				return this->_array;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementBarData::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "barData = {" << std::endl;
			this->_array->print(stream, level + 1, spacesPerLevel);
			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}