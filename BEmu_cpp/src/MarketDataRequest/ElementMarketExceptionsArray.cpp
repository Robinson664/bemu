//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketExceptionsArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketExceptionsArray.h"
#include "MarketDataRequest/ElementMarketExceptions.h"

#include "Types/IndentType.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketExceptionsArray::ElementMarketExceptionsArray(std::vector<std::string> badFields)
		{
			for(std::vector<std::string>::const_iterator iter = badFields.begin(); iter != badFields.end(); ++iter)
			{
				std::string badField = *iter;
				this->_exceptions.push_back(new ElementMarketExceptions(badField));
			}
		}

		ElementMarketExceptionsArray::~ElementMarketExceptionsArray()
		{
			for(std::vector<ElementMarketExceptions*>::const_iterator iter = this->_exceptions.begin(); iter != this->_exceptions.end(); ++iter)
			{
				ElementMarketExceptions * elm = *iter;
				delete elm;
			}
		}

		Name ElementMarketExceptionsArray::name() const
		{
			return Name("exceptions");
		}

		size_t ElementMarketExceptionsArray::numValues() const
		{
			return this->_exceptions.size();
		}

		size_t ElementMarketExceptionsArray::numElements() const
		{
			return 0;
		}

		SchemaElementDefinition ElementMarketExceptionsArray::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("SubscriptionException"));
			return result;
		}

		bool ElementMarketExceptionsArray::isNull() const
		{
			return false;
		}

		bool ElementMarketExceptionsArray::isArray() const
		{
			return true;
		}

		bool ElementMarketExceptionsArray::isComplexType() const
		{
			return false;
		}

		ElementPtr * ElementMarketExceptionsArray::getValueAsElement(int index) const
		{
			ElementPtr * result = this->_exceptions.at(index);
			return result;
		}

		std::ostream& ElementMarketExceptionsArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "exceptions[] = {" << std::endl;

			for(std::vector<ElementMarketExceptions*>::const_iterator iter = this->_exceptions.begin(); iter != this->_exceptions.end(); ++iter)
			{
				ElementMarketExceptions * elm = *iter;
				elm->print(stream, level, spacesPerLevel);
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}