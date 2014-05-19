//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/ElementBarTickDataArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "Types/IndentType.h"
#include "IntradayBarRequest/ElementBarTickData.h"
#include "IntradayBarRequest/BarTickDataType.h"
#include "IntradayBarRequest/ElementBarTickDataArray.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementBarTickDataArray::ElementBarTickDataArray(const std::vector<BarTickDataType*>& bars)
		{
			for(std::vector<BarTickDataType*>::const_iterator iter = bars.begin(); iter != bars.end(); ++iter)
			{
				BarTickDataType * tick = *iter;
				ElementBarTickData * elm = new ElementBarTickData(*tick);
				this->_elements.push_back(elm);
			}
		}

		ElementBarTickDataArray::~ElementBarTickDataArray()
		{
			for(std::vector<ElementBarTickData*>::const_iterator iter = this->_elements.begin(); iter != this->_elements.end(); ++iter)
			{
				ElementBarTickData * elm = *iter;
				delete elm;
				elm = 0;
			}
		}

		Name ElementBarTickDataArray::name() const
		{
			Name result("barTickData");
			return result;
		}

		size_t ElementBarTickDataArray::numValues() const
		{
			return this->_elements.size();
		}

		size_t ElementBarTickDataArray::numElements() const
		{
			return 0;
		}

		SchemaElementDefinition ElementBarTickDataArray::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("IntradayBarTickData"));
			return result;
		}

		bool ElementBarTickDataArray::isArray() const
		{
			return true;
		}

		bool ElementBarTickDataArray::isComplexType() const
		{
			return false;
		}

		ElementPtr * ElementBarTickDataArray::getValueAsElement(int index) const
		{
			if(index >= 0 && index < (int)this->_elements.size())
				return this->_elements[index];

			else
				throw elementPtrEx;
		}

		std::ostream& ElementBarTickDataArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);

			stream << tabs << "barTickData[] = {" << std::endl;

			for(std::vector<ElementBarTickData*>::const_iterator iter = this->_elements.begin(); iter != this->_elements.end(); ++iter)
			{
				ElementBarTickData * elm = *iter;
				elm->print(stream, level + 1, spacesPerLevel);
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}
	}
}