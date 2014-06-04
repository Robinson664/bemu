//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/IntradayTickElementData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/IntradayTickElementData.h"
#include "IntradayTickRequest/IntradayTickElementTuple3.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "BloombergTypes/Datetime.h"
#include "Types/IndentType.h"
#include "IntradayTickRequest/IntradayTickElementDateTime.h"
#include "IntradayTickRequest/IntradayTickElementString.h"
#include "IntradayTickRequest/IntradayTickElementDouble.h"
#include "IntradayTickRequest/IntradayTickElementInt.h"

#include "IntradayTickRequest/IntradayTickElement.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		IntradayTickElementData::IntradayTickElementData(const Datetime& datetime, const IntradayTickElementTuple3& arg, bool includeConditionCodes) :
			_time(new IntradayTickElementDateTime("time", datetime)),
			_type(new IntradayTickElementString("type", arg.item1())),
			_value(new IntradayTickElementDouble("value", arg.item2())),
			_size(new IntradayTickElementInt("size", arg.item3()))
		{
			this->_includeConditionCodes = includeConditionCodes;

			//this->_time = new IntradayTickElementDateTime("time", datetime);
			//this->_type = new IntradayTickElementString("type", arg.item1());
			//this->_value = new IntradayTickElementDouble("value", arg.item2());
			//this->_size = new IntradayTickElementInt("size", arg.item3());

			if(includeConditionCodes)
				this->_conditionCodes = boost::shared_ptr<IntradayTickElementString>(new IntradayTickElementString("conditionCodes", "R6,IS"));
			else
				this->_conditionCodes = boost::shared_ptr<IntradayTickElementString>();
		}

		IntradayTickElementData::~IntradayTickElementData()
		{
			//delete this->_time;
			//this->_time = 0;

			//delete this->_type;
			//this->_type = 0;

			//delete this->_value;
			//this->_value = 0;

			//delete this->_size;
			//this->_size = 0;

			//if(this->_includeConditionCodes)
			//{
			//	delete this->_conditionCodes;
			//	this->_conditionCodes = 0;
			//}
		}

		Name IntradayTickElementData::name() const
		{
			Name result("tickData");
			return result;
		}

		SchemaElementDefinition IntradayTickElementData::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("IntradayTickData"));
			return result;
		}

		bool IntradayTickElementData::hasElement(const char* name, bool excludeNullElements) const
		{
			return 
				strncmp("time", name, 5) == 0 ||
				strncmp("type", name, 5) == 0 ||
				strncmp("value", name, 6) == 0 ||
				strncmp("size", name, 5) == 0 ||
				(this->_includeConditionCodes && strncmp("conditionCodes", name, 15) == 0);
		}

		//ElementPtr * IntradayTickElementData::getElement(int position) const
		boost::shared_ptr<ElementPtr> IntradayTickElementData::getElement(int position) const
		{
			switch(position)
			{
				case 0:
					return boost::dynamic_pointer_cast<ElementPtr>(this->_time);
					//result = this->_time;
				case 1:
					return boost::dynamic_pointer_cast<ElementPtr>(this->_type);
					//result = this->_type;
				case 2:
					return boost::dynamic_pointer_cast<ElementPtr>(this->_value);
					//result = this->_value;
				case 3:
					return boost::dynamic_pointer_cast<ElementPtr>(this->_size);
					//result = this->_size;
				case 4:
					if(this->_includeConditionCodes)
						return boost::dynamic_pointer_cast<ElementPtr>(this->_conditionCodes);
						//result = this->_conditionCodes;
			}

			throw elementPtrEx;
		}

		//ElementPtr * IntradayTickElementData::getElement(const char* name) const
		boost::shared_ptr<ElementPtr> IntradayTickElementData::getElement(const char* name) const
		{
			if(strncmp("time", name, 5) == 0)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_time);
				//result = this->_time;

			else if(strncmp("type", name, 5) == 0)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_type);
				//result = this->_type;

			else if(strncmp("value", name, 6) == 0)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_value);
				//result = this->_value;

			else if(strncmp("size", name, 5) == 0)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_size);
				//result = this->_size;

			else if(this->_includeConditionCodes && strncmp("conditionCodes", name, 15) == 0)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_conditionCodes);
				//result = this->_conditionCodes;

			throw elementPtrEx;
		}

		int IntradayTickElementData::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		Datetime IntradayTickElementData::getElementAsDatetime(const char* name) const
		{
			return this->getElement(name)->getValueAsDatetime(0);
		}

		const char* IntradayTickElementData::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		std::ostream& IntradayTickElementData::print(std::ostream& stream, int level, int spacesPerLevel) const
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