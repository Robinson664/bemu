//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/EventMarket.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/EventMarket.h"
#include "MarketDataRequest/MessageMarketSessionOpened.h"
#include "MarketDataRequest/MessageMarketServiceStatus.h"
#include "MarketDataRequest/MessageMarketSubscriptionFailure.h"
#include "MarketDataRequest/MessageMarketSubscriptionStarted.h"
#include "MarketDataRequest/MessageMarketSubscriptionData.h"
#include "MarketDataRequest/MessageMarketSubscriptionCanceled.h"

#include "Types/Rules.h"
#include "Types/RandomDataGenerator.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		EventMarket::EventMarket(Event::EventType evtType, CorrelationId corr, SubscriptionList subs) : EventPtr(0)
		{
			this->_messages = new std::vector<MessagePtr*>();

			switch(evtType)
			{
				case Event::SESSION_STATUS:
				{
					this->_type = evtType;
					MessageMarketSessionOpened * msgSessionOpened = new MessageMarketSessionOpened();
					this->_messages->push_back(msgSessionOpened);
					break;
				}

				case Event::SERVICE_STATUS:
				{
					this->_type = evtType;
					MessageMarketServiceStatus * msgServiceStatus = new MessageMarketServiceStatus(corr);
					this->_messages->push_back(msgServiceStatus);
					break;
				}

				case Event::SUBSCRIPTION_STATUS:
				{
					this->_type = evtType;
					std::vector<Subscription> * list = subs.list();
					for(std::vector<Subscription>::const_iterator iter = list->begin(); iter != list->end(); ++iter)
					{
						Subscription sub = *iter;
						bool securityError = Rules::IsSecurityError(sub.security());
						if(securityError)
						{
							MessageMarketSubscriptionFailure * msgError = new MessageMarketSubscriptionFailure(sub);
							this->_messages->push_back(msgError);
						}
						else
						{
							MessageMarketSubscriptionStarted * msgSubStatus = new MessageMarketSubscriptionStarted(sub);
							this->_messages->push_back(msgSubStatus);
						}
					}
					break;
				}

				case Event::SUBSCRIPTION_DATA:
				{
					this->_type = evtType;
					for(std::vector<Subscription>::const_iterator iter = subs.list()->begin(); iter != subs.list()->end(); ++iter)
					{
						Subscription sub = *iter;
						bool securityError = Rules::IsSecurityError(sub.security());
						if (!securityError)
						{
							MessageMarketSubscriptionData * msgSubData = new MessageMarketSubscriptionData(sub, EventMarket::generateFakeMessageData(sub));
							this->_messages->push_back(msgSubData);
						}
					}
					break;
				}

				default:
					throw eventPtrEx;
			}
		}

		EventMarket::EventMarket(Event::EventType evtType, Subscription sub) : EventPtr(0)
		{
			this->_messages = new std::vector<MessagePtr*>();

			switch(evtType)
			{
				case Event::SUBSCRIPTION_STATUS:
				{
					this->_type = evtType;
					MessageMarketSubscriptionCanceled * msgCancel = new MessageMarketSubscriptionCanceled(sub);
					this->_messages->push_back(msgCancel);
				}
				break;
			}
		}

		EventMarket::~EventMarket()
		{
			delete this->_messages;
		}

		std::vector<MessagePtr*> * EventMarket::getMessages() const
		{
			return this->_messages;
		}

		std::map<std::string, ObjectType> EventMarket::generateFakeMessageData(Subscription sub)
		{
			return RandomDataGenerator::GetMarketDataFields(sub.fieldList());
		}

	}
}