//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MarketMessageSubscriptionCanceled.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MarketMessageSubscriptionCanceled.h"
#include "MarketDataRequest/MarketElementSubscriptionCancelReason.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Subscription.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MarketMessageSubscriptionCanceled::MarketMessageSubscriptionCanceled(Subscription sub) : MessagePtr(Name("SubscriptionTerminated"), sub.correlationId())
		{
			this->_topicName = sub.security();
            this->_reason = new MarketElementSubscriptionCancelReason();
		}

		MarketMessageSubscriptionCanceled::~MarketMessageSubscriptionCanceled()
		{
			delete this->_reason;
			this->_reason = 0;
		}

		std::stack<ElementPtr*> MarketMessageSubscriptionCanceled::getRootElements() const
		{
			std::stack<ElementPtr*> result;

			if(this->_reason != 0)
				result.push(this->_reason);

			return result;
		}

		size_t MarketMessageSubscriptionCanceled::numElements() const
		{
			return 1;
		}

		const char* MarketMessageSubscriptionCanceled::topicName() const
		{
			return ElementPtr::toCharPointer(this->_topicName);
		}

		ElementPtr * MarketMessageSubscriptionCanceled::asElement() const
		{
			throw messageEx;
		}

		std::ostream& MarketMessageSubscriptionCanceled::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "SubscriptionTerminated = {"  << std::endl;
			this->_reason->print(stream, level + 1, spacesPerLevel);
			stream << "}" << std::endl;

			return stream;
		}

	}
}