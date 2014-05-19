//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/IntradayTickElementDataParent.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/IntradayTickElementDataParent.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "Types/IndentType.h"
#include <map>
#include "IntradayTickRequest/IntradayTickElementTuple3.h"
#include "IntradayTickRequest/IntradayTickElementDataArray.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		//makes copies of the arguments
		IntradayTickElementDataParent::IntradayTickElementDataParent(std::map<Datetime, IntradayTickElementTuple3*>* ticks, bool includeConditionCodes)
		{
			this->_array = new IntradayTickElementDataArray(ticks, includeConditionCodes);
		}

		IntradayTickElementDataParent::~IntradayTickElementDataParent()
		{
			delete this->_array;
			this->_array = 0;
		}

		Name IntradayTickElementDataParent::name() const
		{
			Name result("tickData");
			return result;
		}

		SchemaElementDefinition IntradayTickElementDataParent::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("TickData"));
			return result;
		}

		ElementPtr * IntradayTickElementDataParent::getElement(const char* name) const
		{
			if(this->_array->name() == name)
				return this->_array;

			else
				throw elementPtrEx;
		}

		std::ostream& IntradayTickElementDataParent::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);

			stream << tabs << "tickData = {" << std::endl;
			this->_array->print(stream, level + 1, spacesPerLevel);
			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}