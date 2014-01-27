//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MessageMarketSubscriptionFailure.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MessageMarketSubscriptionFailure.h"
#include "MarketDataRequest/ElementMarketReason.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MessageMarketSubscriptionFailure::MessageMarketSubscriptionFailure(Subscription sub)
			: MessagePtr(Name("SubscriptionFailure"), sub.correlationId())
		{
            this->_correlationId = sub.correlationId();
			this->_topicName = sub.security();
			this->_reason = new ElementMarketReason(ReasonType::badSecurity);
		}

		MessageMarketSubscriptionFailure::~MessageMarketSubscriptionFailure()
		{
			delete this->_reason;
			this->_reason = 0;
		}

		size_t MessageMarketSubscriptionFailure::numElements() const
		{
			return 1;
		}

		const char* MessageMarketSubscriptionFailure::topicName() const
		{
			return ElementPtr::toCharPointer(this->_topicName);
		}

		bool MessageMarketSubscriptionFailure::hasElement(const char* name, bool excludeNullElements) const
		{
			return this->_reason->name() == name;
		}

		ElementPtr * MessageMarketSubscriptionFailure::getElement(const char* name) const
		{
			if(this->_reason->name() == name)
				return this->_reason;

			else
				throw messageEx;
		}

		std::ostream& MessageMarketSubscriptionFailure::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "SubscriptionFailure = {" << std::endl;
			this->_reason->print(stream, level + 1, spacesPerLevel);
			stream << "}" << std::endl;

			return stream;
		}
	}
}