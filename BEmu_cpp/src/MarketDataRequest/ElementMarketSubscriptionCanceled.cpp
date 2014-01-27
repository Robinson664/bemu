//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketSubscriptionCanceled.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketSubscriptionCanceled.h"
#include "MarketDataRequest/MessageMarketSubscriptionCanceled.h"
#include "MarketDataRequest/ElementMarketSubscriptionCancelReason.h"

#include "Types/IndentType.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketSubscriptionCanceled::ElementMarketSubscriptionCanceled(MessageMarketSubscriptionCanceled * arg)
		{
			this->_reason = (ElementMarketSubscriptionCancelReason*)arg->getElement("reason");
		}

		Name ElementMarketSubscriptionCanceled::name() const
		{
			return Name("SubscriptionTerminated");
		}

		size_t ElementMarketSubscriptionCanceled::numValues() const
		{
			return 1;
		}

		size_t ElementMarketSubscriptionCanceled::numElements() const
		{
			return 1;
		}

		bool ElementMarketSubscriptionCanceled::isNull() const
		{
			return false;
		}

		bool ElementMarketSubscriptionCanceled::isArray() const
		{
			return false;
		}

		bool ElementMarketSubscriptionCanceled::isComplexType() const
		{
			return true;
		}

		std::ostream& ElementMarketSubscriptionCanceled::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "SubscriptionTerminated = {" << std::endl;
			this->_reason->print(stream, level + 1, spacesPerLevel);
			stream << tabs << '}' << std::endl;

			return stream;
		}
	}
}