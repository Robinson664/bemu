//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/MarketDataRequest/MessageMarketSubscriptionStarted.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/MessagePtr.h"
#include "BloombergTypes/Subscription.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		class ElementMarketNull;
		class ElementMarketExceptionsArray;

		class MessageMarketSubscriptionStarted : public MessagePtr
		{
			private:
				CorrelationId _correlationId;
				std::string _topicName;
				ElementMarketNull * _exceptionsNull;
				ElementMarketExceptionsArray * _exceptionsBadFields;

			public:
				MessageMarketSubscriptionStarted(Subscription sub);
				~MessageMarketSubscriptionStarted();

				ElementPtr * firstElement() const;

				virtual size_t numElements() const;
				virtual ElementPtr * asElement() const;
				virtual const char* topicName() const;

				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;
				virtual ElementPtr * getElement(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}