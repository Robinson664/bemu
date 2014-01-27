//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/MarketDataRequest/EventMarket.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/EventPtr.h"
#include "BloombergTypes/CorrelationId.h"
#include "BloombergTypes/Event.h"
#include "BloombergTypes/Subscription.h"
#include "BloombergTypes/SubscriptionList.h"
#include "Types/ObjectType.h"
#include <vector>
#include <map>

namespace BEmu
{
	class MessagePtr;

	namespace MarketDataRequest
	{
		class EventMarket : public EventPtr
		{
			private:
				std::vector<MessagePtr*> * _messages;
				std::map<std::string, ObjectType> generateFakeMessageData(Subscription sub);
				virtual std::vector<MessagePtr*> * getMessages() const;

			public:
				EventMarket(Event::EventType evtType, CorrelationId corr, SubscriptionList subs); //use for subscribing
				EventMarket(Event::EventType evtType, Subscription sub); //use for unsubscribing
				~EventMarket();
		};
	}
}