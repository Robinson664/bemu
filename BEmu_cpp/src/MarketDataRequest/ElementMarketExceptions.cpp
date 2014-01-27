//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketExceptions.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketExceptions.h"
#include "MarketDataRequest/ElementMarketString.h"
#include "MarketDataRequest/ElementMarketReason.h"

#include "Types/IndentType.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketExceptions::ElementMarketExceptions(std::string badField)
		{
            this->_fieldId = new ElementMarketString("fieldId", badField);
            this->_reason = new ElementMarketReason(MarketDataRequest::ReasonType::badField);
		}

		Name ElementMarketExceptions::name() const
		{
			return Name("exceptions");
		}

		size_t ElementMarketExceptions::numValues() const
		{
			return 1;
		}

		size_t ElementMarketExceptions::numElements() const
		{
			return 2;
		}

		bool ElementMarketExceptions::isNull() const
		{
			return false;
		}

		bool ElementMarketExceptions::isArray() const
		{
			return false;
		}

		bool ElementMarketExceptions::isComplexType() const
		{
			return true;
		}

		ElementPtr * ElementMarketExceptions::getElement(const char* name) const
		{
			if(strncmp(name, "fieldId", 8) == 0)
				return this->_fieldId;
			
			else if(strncmp(name, "reason", 7) == 0)
				return this->_reason;

			else
				throw elementPtrEx;
		}

		bool ElementMarketExceptions::hasElement(const char* name, bool excludeNullElements) const
		{
			return strncmp(name, "fieldId", 8) == 0 || strncmp(name, "reason", 7) == 0;
		}

		const char* ElementMarketExceptions::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		std::ostream& ElementMarketExceptions::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "exceptions = {" << std::endl;
			
			this->_fieldId->print(stream, level + 1);
			this->_reason->print(stream, level + 1);

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}