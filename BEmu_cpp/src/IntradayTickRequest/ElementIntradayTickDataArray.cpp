//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementIntradayTickDataArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "IntradayTickRequest/ElementIntradayTickDataArray.h"
#include "IntradayTickRequest\ElementIntradayTickData.h"
#include "IntradayTickRequest\ElementIntradayTickDataTuple3.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "Types/IndentType.h"

#include <map>
#include <vector>

namespace BEmu
{
	namespace IntradayTickRequest
	{
		//makes copies of the arguments
		ElementIntradayTickDataArray::ElementIntradayTickDataArray(std::map<Datetime*, ElementIntradayTickDataTuple3*>* ticks, bool includeConditionCodes)
		{
			for(std::map<Datetime*, ElementIntradayTickDataTuple3*>::iterator iter = ticks->begin(); iter != ticks->end(); ++iter)
			{
				Datetime date(*(iter->first));
				ElementIntradayTickDataTuple3 tuple(iter->second->item1(), iter->second->item2(), iter->second->item3());
				ElementIntradayTickData* elmFieldData = new ElementIntradayTickData(date, tuple, includeConditionCodes);

				this->_tickData.push_back(elmFieldData);
			}
		}

		ElementIntradayTickDataArray::~ElementIntradayTickDataArray()
		{
			for(std::vector<ElementIntradayTickData*>::iterator iter = this->_tickData.begin(); iter != this->_tickData.end(); ++iter)
			{
				ElementIntradayTickData* elmFieldData = *iter;
				delete elmFieldData;
				elmFieldData = 0;
			}
		}

		ElementPtr * ElementIntradayTickDataArray::getValueAsElement(int index) const
		{
			ElementIntradayTickData* result = this->_tickData.operator[](index);
			return result;
		}

		Name ElementIntradayTickDataArray::name() const
		{
			Name result("tickData");
			return result;
		}

		int ElementIntradayTickDataArray::numValues() const
		{
			return this->_tickData.size();
		}

		std::ostream& ElementIntradayTickDataArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);

			stream << tabs << "tickData[] = {" << std::endl;
			for(std::vector<ElementIntradayTickData*>::const_iterator iter = this->_tickData.begin(); iter != this->_tickData.end(); ++iter)
			{
				ElementIntradayTickData* elmFieldData = *iter;
				elmFieldData->print(stream, level + 1, spacesPerLevel);
			}
			stream << tabs << '}' << std::endl;

			return stream;
		}


	}
}