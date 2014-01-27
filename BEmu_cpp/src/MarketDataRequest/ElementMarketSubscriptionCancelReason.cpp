//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketSubscriptionCancelReason.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketSubscriptionCancelReason.h"
#include "MarketDataRequest/ElementMarketString.h"
#include "MarketDataRequest/ElementMarketInt.h"

#include "Types/IndentType.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketSubscriptionCancelReason::ElementMarketSubscriptionCancelReason()
		{
            this->_source = new ElementMarketString("source", "Session");
            this->_errorCode = new ElementMarketInt("errorCode", 0);
            this->_category = new ElementMarketString("category", "CANCELED");
            this->_description = new ElementMarketString("description", "Subscription canceled");
            this->_subCategory = new ElementMarketString("subcategory", "");
		}

		ElementMarketSubscriptionCancelReason::~ElementMarketSubscriptionCancelReason()
		{
			delete this->_source;
			this->_source = 0;
			
			delete this->_errorCode;
			this->_errorCode = 0;
			
			delete this->_category;
			this->_category = 0;
			
			delete this->_description;
			this->_description = 0;
			
			delete this->_subCategory;
			this->_subCategory = 0;
		}

		Name ElementMarketSubscriptionCancelReason::name() const
		{
			return Name("reason");
		}

		size_t ElementMarketSubscriptionCancelReason::numValues() const
		{
			return 1;
		}

		size_t ElementMarketSubscriptionCancelReason::numElements() const
		{
			return 5;
		}

		bool ElementMarketSubscriptionCancelReason::isNull() const
		{
			return false;
		}

		bool ElementMarketSubscriptionCancelReason::isArray() const
		{
			return false;
		}

		bool ElementMarketSubscriptionCancelReason::isComplexType() const
		{
			return true;
		}

		std::ostream& ElementMarketSubscriptionCancelReason::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "reason = {" << std::endl;
			this->_source->print(stream, level + 1, spacesPerLevel);
			this->_errorCode->print(stream, level + 1, spacesPerLevel);
			this->_category->print(stream, level + 1, spacesPerLevel);
			this->_description->print(stream, level + 1, spacesPerLevel);
			this->_subCategory->print(stream, level + 1, spacesPerLevel);

			stream << tabs << '}' << std::endl;

			return stream;
		}
	}
}