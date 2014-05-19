//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MarketEvent.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MarketEvent.h"
#include "MarketDataRequest/MarketMessageSessionOpened.h"
#include "MarketDataRequest/MarketMessageServiceStatus.h"
#include "MarketDataRequest/MarketMessageSubscriptionFailure.h"
#include "MarketDataRequest/MarketMessageSubscriptionStarted.h"
#include "MarketDataRequest/MarketMessageSubscriptionData.h"
#include "MarketDataRequest/MarketMessageSubscriptionCanceled.h"

#include "Types/Rules.h"
#include "Types/RandomDataGenerator.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MarketEvent::MarketEvent(Event::EventType evtType, CorrelationId corr, SubscriptionList subs) : EventPtr(0)
		{
			this->_messages = new std::vector<MessagePtr*>();

			switch(evtType)
			{
				case Event::SESSION_STATUS:
				{
					this->_type = evtType;
					MarketMessageSessionOpened * msgSessionOpened = new MarketMessageSessionOpened();
					this->_messages->push_back(msgSessionOpened);
					break;
				}

				case Event::SERVICE_STATUS:
				{
					this->_type = evtType;
					MarketMessageServiceStatus * msgServiceStatus = new MarketMessageServiceStatus(corr);
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
							MarketMessageSubscriptionFailure * msgError = new MarketMessageSubscriptionFailure(sub);
							this->_messages->push_back(msgError);
						}
						else
						{
							MarketMessageSubscriptionStarted * msgSubStatus = new MarketMessageSubscriptionStarted(sub);
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
							MarketMessageSubscriptionData * msgSubData = new MarketMessageSubscriptionData(sub, MarketEvent::generateFakeMessageData(sub));
							this->_messages->push_back(msgSubData);
						}
					}
					break;
				}

				default:
					throw eventPtrEx;
			}
		}

		MarketEvent::MarketEvent(Event::EventType evtType, Subscription sub) : EventPtr(0)
		{
			this->_messages = new std::vector<MessagePtr*>();

			switch(evtType)
			{
				case Event::SUBSCRIPTION_STATUS:
				{
					this->_type = evtType;
					MarketMessageSubscriptionCanceled * msgCancel = new MarketMessageSubscriptionCanceled(sub);
					this->_messages->push_back(msgCancel);
				}
				break;
			}
		}

		MarketEvent::~MarketEvent()
		{
			delete this->_messages;
		}

		std::vector<MessagePtr*> * MarketEvent::getMessages() const
		{
			return this->_messages;
		}

		std::map<std::string, ObjectType> MarketEvent::generateFakeMessageData(Subscription sub)
		{
			return RandomDataGenerator::GetMarketDataFields(sub.fieldList());
		}

	}
}