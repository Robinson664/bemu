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
		MarketEvent::MarketEvent(Event::EventType evtType, const CorrelationId& corr, const SubscriptionList& subs) : 
			EventPtr(boost::shared_ptr<RequestPtr>())
		{
			switch(evtType)
			{
				case Event::SESSION_STATUS:
				{
					this->setEventType(evtType);
					
					boost::shared_ptr<MarketMessageSessionOpened> msgSessionOpenedP(new MarketMessageSessionOpened());
					boost::shared_ptr<MessagePtr> msgSessionOpened(boost::dynamic_pointer_cast<MessagePtr>(msgSessionOpenedP));

					this->_messages.push_back(msgSessionOpened);
					break;
				}

				case Event::SERVICE_STATUS:
				{
					this->setEventType(evtType);

					boost::shared_ptr<MarketMessageServiceStatus> msgServiceStatusP(new MarketMessageServiceStatus(corr));
					boost::shared_ptr<MessagePtr> msgServiceStatus(boost::dynamic_pointer_cast<MessagePtr>(msgServiceStatusP));

					this->_messages.push_back(msgServiceStatus);
					break;
				}

				case Event::SUBSCRIPTION_STATUS:
				{
					this->setEventType(evtType);

					std::vector<Subscription> list = subs.list();
					for(std::vector<Subscription>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
					{
						Subscription sub = *iter;
						bool securityError = Rules::IsSecurityError(sub.security());
						if(securityError)
						{
							boost::shared_ptr<MarketMessageSubscriptionFailure> msgErrorP(new MarketMessageSubscriptionFailure(sub));
							boost::shared_ptr<MessagePtr> msgError(boost::dynamic_pointer_cast<MessagePtr>(msgErrorP));

							this->_messages.push_back(msgError);
						}
						else
						{
							boost::shared_ptr<MarketMessageSubscriptionStarted> msgSubStatusP(new MarketMessageSubscriptionStarted(sub));
							boost::shared_ptr<MessagePtr> msgSubStatus(boost::dynamic_pointer_cast<MessagePtr>(msgSubStatusP));

							this->_messages.push_back(msgSubStatus);
						}
					}
					break;
				}

				case Event::SUBSCRIPTION_DATA:
				{
					this->setEventType(evtType);

					std::vector<Subscription> list(subs.list());

					for(std::vector<Subscription>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
					{
						Subscription sub = *iter;
						bool securityError = Rules::IsSecurityError(sub.security());
						if (!securityError)
						{
							boost::shared_ptr<MarketMessageSubscriptionData> msgSubDataP(new MarketMessageSubscriptionData(sub, MarketEvent::generateFakeMessageData(sub)));
							boost::shared_ptr<MessagePtr> msgSubData(boost::dynamic_pointer_cast<MessagePtr>(msgSubDataP));

							this->_messages.push_back(msgSubData);
						}
					}
					break;
				}

				default:
					throw eventPtrEx;
			}
		}

		MarketEvent::MarketEvent(Event::EventType evtType, const Subscription& sub) : 
			EventPtr(boost::shared_ptr<RequestPtr>())
		{
			switch(evtType)
			{
				case Event::SUBSCRIPTION_STATUS:
				{
					this->setEventType(evtType);
					
					boost::shared_ptr<MarketMessageSubscriptionCanceled> msgCancelMP(new MarketMessageSubscriptionCanceled(sub));
					boost::shared_ptr<MessagePtr> msgCancelP(boost::dynamic_pointer_cast<MessagePtr>(msgCancelMP));

					this->_messages.push_back(msgCancelMP);
				}
				break;
			}
		}

		MarketEvent::~MarketEvent()
		{
			this->_messages.clear();
		}

		std::vector< boost::shared_ptr<MessagePtr> > MarketEvent::getMessages() const
		{
			return this->_messages;
		}

		std::map<std::string, ObjectType> MarketEvent::generateFakeMessageData(const Subscription& sub) const
		{
			return RandomDataGenerator::GetMarketDataFields(sub.fieldList());
		}

	}
}