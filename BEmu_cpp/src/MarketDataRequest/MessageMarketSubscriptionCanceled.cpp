//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MessageMarketSubscriptionCanceled.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MessageMarketSubscriptionCanceled.h"
#include "MarketDataRequest/ElementMarketSubscriptionCancelReason.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Subscription.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MessageMarketSubscriptionCanceled::MessageMarketSubscriptionCanceled(Subscription sub) : MessagePtr(Name("SubscriptionTerminated"), sub.correlationId())
		{
			this->_topicName = sub.security();
            this->_reason = new ElementMarketSubscriptionCancelReason();
		}

		MessageMarketSubscriptionCanceled::~MessageMarketSubscriptionCanceled()
		{
			delete this->_reason;
			this->_reason = 0;
		}

		size_t MessageMarketSubscriptionCanceled::numElements() const
		{
			return 1;
		}

		const char* MessageMarketSubscriptionCanceled::topicName() const
		{
			return ElementPtr::toCharPointer(this->_topicName);
		}

		ElementPtr * MessageMarketSubscriptionCanceled::asElement() const
		{
			throw messageEx;
		}

		std::ostream& MessageMarketSubscriptionCanceled::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "SubscriptionTerminated = {"  << std::endl;
			this->_reason->print(stream, level + 1, spacesPerLevel);
			stream << "}" << std::endl;

			return stream;
		}

	}
}