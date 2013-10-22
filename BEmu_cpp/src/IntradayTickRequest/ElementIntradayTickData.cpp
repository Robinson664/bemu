//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementIntradayTickData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "IntradayTickRequest\ElementIntradayTickData.h"
#include "IntradayTickRequest\ElementIntradayTickDataTuple3.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "BloombergTypes/Datetime.h"
#include "Types/IndentType.h"

#include "IntradayTickRequest\ElementIntradayTickDateTime.h"
#include "IntradayTickRequest\ElementIntradayTickString.h"
#include "IntradayTickRequest\ElementIntradayTickDouble.h"
#include "IntradayTickRequest\ElementIntradayTickInt.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		ElementIntradayTickData::ElementIntradayTickData(const Datetime& datetime, const ElementIntradayTickDataTuple3& arg, bool includeConditionCodes)
		{
			this->_includeConditionCodes = includeConditionCodes;

			this->_time = new ElementIntradayTickDateTime("time", datetime);
			this->_type = new ElementIntradayTickString("type", arg.item1());
			this->_value = new ElementIntradayTickDouble("value", arg.item2());
			this->_size = new ElementIntradayTickInt("size", arg.item3());

			if(includeConditionCodes)
				this->_conditionCodes = new ElementIntradayTickString("conditionCodes", "R6,IS");
			else
				this->_conditionCodes = 0;
		}

		ElementIntradayTickData::~ElementIntradayTickData()
		{
			delete this->_time;
			delete this->_type;
			delete this->_value;
			delete this->_size;

			if(this->_includeConditionCodes)
				delete this->_conditionCodes;
		}

		Name ElementIntradayTickData::name() const
		{
			Name result("tickData");
			return result;
		}

		bool ElementIntradayTickData::hasElement(const char* name, bool excludeNullElements) const
		{
			return 
				strncmp("time", name, 4) == 0 ||
				strncmp("type", name, 4) == 0 ||
				strncmp("value", name, 5) == 0 ||
				strncmp("size", name, 4) == 0 ||
				(this->_includeConditionCodes && strncmp("conditionCodes", name, 14) == 0);
		}

		ElementPtr * ElementIntradayTickData::getElement(int position) const
		{
			ElementPtr *result = 0;

			switch(position)
			{
				case 0:
					result = this->_time;
				case 1:
					result = this->_type;
				case 2:
					result = this->_value;
				case 3:
					result = this->_size;
				case 4:
					if(this->_includeConditionCodes)
						result = this->_conditionCodes;
			}

			if(result == 0)
				throw elementPtrEx;
			else
				return result;
		}

		ElementPtr * ElementIntradayTickData::getElement(const char* name) const
		{
			ElementPtr *result = 0;

			if(strncmp("time", name, 4) == 0)
				result = this->_time;

			else if(strncmp("type", name, 4) == 0)
				result = this->_type;

			else if(strncmp("value", name, 5) == 0)
				result = this->_value;

			else if(strncmp("size", name, 4) == 0)
				result = this->_size;

			else if(this->_includeConditionCodes && strncmp("conditionCodes", name, 14) == 0)
				result = this->_conditionCodes;

			if(result == 0)
				throw elementPtrEx;
			else
				return result;
		}

		int ElementIntradayTickData::getElementAsInt32(const char* name) const
		{
			ElementPtr * elm = this->getElement(name);
			return elm->getValueAsInt32(0);
		}

		Datetime ElementIntradayTickData::getElementAsDatetime(const char* name) const
		{
			ElementPtr * elm = this->getElement(name);
			return elm->getValueAsDatetime(0);
		}

		const char* ElementIntradayTickData::getElementAsString(const char* name) const
		{
			ElementPtr * elm = this->getElement(name);
			return elm->getValueAsString(0);
		}

		std::ostream& ElementIntradayTickData::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);
			stream << tabs << "tickData = {" << std::endl;

			
			this->_time->print(stream, level + 1, spacesPerLevel);
			this->_type->print(stream, level + 1, spacesPerLevel);
			this->_value->print(stream, level + 1, spacesPerLevel);
			this->_size->print(stream, level + 1, spacesPerLevel);

			if(this->_includeConditionCodes)
				this->_conditionCodes->print(stream, level + 1, spacesPerLevel);

			stream << tabs << '}' << std::endl;
			return stream;
		}

	}
}