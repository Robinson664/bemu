//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MarketMessageSubscriptionFailure.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MarketMessageSubscriptionFailure.h"
#include "MarketDataRequest/MarketElementReason.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MarketMessageSubscriptionFailure::MarketMessageSubscriptionFailure(Subscription sub)
			: MessagePtr(Name("SubscriptionFailure"), sub.correlationId())
		{
            this->_correlationId = sub.correlationId();
			this->_topicName = sub.security();
			this->_reason = new MarketElementReason(ReasonType::badSecurity);
		}

		MarketMessageSubscriptionFailure::~MarketMessageSubscriptionFailure()
		{
			delete this->_reason;
			this->_reason = 0;
		}

		size_t MarketMessageSubscriptionFailure::numElements() const
		{
			return 1;
		}

		const char* MarketMessageSubscriptionFailure::topicName() const
		{
			return ElementPtr::toCharPointer(this->_topicName);
		}

		bool MarketMessageSubscriptionFailure::hasElement(const char* name, bool excludeNullElements) const
		{
			return this->_reason->name() == name;
		}

		ElementPtr * MarketMessageSubscriptionFailure::getElement(const char* name) const
		{
			if(this->_reason->name() == name)
				return this->_reason;

			else
				throw messageEx;
		}

		std::ostream& MarketMessageSubscriptionFailure::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "SubscriptionFailure = {" << std::endl;
			this->_reason->print(stream, level + 1, spacesPerLevel);
			stream << "}" << std::endl;

			return stream;
		}
	}
}