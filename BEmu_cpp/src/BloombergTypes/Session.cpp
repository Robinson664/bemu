//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/Session.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include <time.h>
#include <stdlib.h>

#include "BloombergTypes/Session.h"
#include "BloombergTypes/Service.h"
#include "BloombergTypes/Event.h"
#include "BloombergTypes/EventPtr.h"
#include "BloombergTypes/RequestPtr.h"
#include "BloombergTypes/EventHandler.h"
#include "Types/BEmuTimer.h"
#include "BloombergTypes/SessionTimerFunction.h"

#include "MarketDataRequest/MarketEvent.h"
#include "BloombergTypes/CorrelationId.h"
#include "BloombergTypes/SubscriptionList.h"

#include "IntradayTickRequest/IntradayTickElement.h"

namespace BEmu
{
	Session::Session(const SessionOptions& options) //for sync calls (HistRef, Intraday, and Reference)
	{
		srand((unsigned int)time(0));
		this->_sessionState = initialized;

		this->_sessionOptions.setServerHost(options.serverHost());
		this->_sessionOptions.setServerPort(options.serverPort());

		this->_sessionTimerFunction = 0;
		this->_marketSimulatorTimer = 0;
	}

	Session::Session(const SessionOptions& options, EventHandler * eventHandler) //for async calls (MarketDataSubscriptions)
	{
		srand((unsigned int)time(0));
		this->_asyncHandler = eventHandler;
		
		this->_sessionOptions.setServerHost(options.serverHost());
		this->_sessionOptions.setServerPort(options.serverPort());

		this->_sessionTimerFunction = new SessionTimerFunction(this, eventHandler);

		this->_marketSimulatorTimer = new BEmuTimer(this->_sessionTimerFunction);
		this->_marketSimulatorTimer->start(0, RunType::neverRun);
	}

	void Session::subscribe(const SubscriptionList& subscriptionList)
	{
		std::vector<Subscription> * subs = subscriptionList.list();
		for(std::vector<Subscription>::const_iterator iter = subs->begin(); iter != subs->end(); ++iter)
		{
			Subscription sub = *iter;
			this->_subs.add(sub);
		}

		if (this->_asyncHandler != 0)
        {
			boost::shared_ptr<MarketDataRequest::MarketEvent> evtSubStatusP(new MarketDataRequest::MarketEvent(Event::SUBSCRIPTION_STATUS, CorrelationId(), subscriptionList));
			boost::shared_ptr<EventPtr> evtP = boost::dynamic_pointer_cast<EventPtr>(evtSubStatusP);
			const Event ev(evtP);

			this->_asyncHandler->processEvent(ev, this);
        }
	}

	void Session::unsubscribe(const SubscriptionList& subscriptionList)
	{
		std::vector<Subscription> subs(*subscriptionList.list());
		for(std::vector<Subscription>::const_iterator iter = subs.begin(); iter != subs.end(); ++iter)
		{
			Subscription subCurrent = *iter;
			CorrelationId corr = subCurrent.correlationId();
			this->cancel(corr);
		}
	}

	void Session::cancel(const CorrelationId& correlationId)
	{
		//remove subscription from the internal list
		Subscription removed = this->_subs.remove(correlationId);
		
		//send a notification to the user about the removed subscription
		if (this->_asyncHandler != 0 && !removed.isDefault())
		{
			//MarketDataRequest::MarketEvent * evtCancel = new MarketDataRequest::MarketEvent(Event::SUBSCRIPTION_STATUS, removed);
			
			boost::shared_ptr<MarketDataRequest::MarketEvent> evtSubStatusP(new MarketDataRequest::MarketEvent(Event::SUBSCRIPTION_STATUS, removed));
			boost::shared_ptr<EventPtr> evtP = boost::dynamic_pointer_cast<EventPtr>(evtSubStatusP);
			const Event ev(evtP);

			this->_asyncHandler->processEvent(ev, this);
		}
	}

	void Session::cancel(const std::vector<CorrelationId>& correlationIds)
	{
		for(std::vector<CorrelationId>::const_iterator iter = correlationIds.begin(); iter != correlationIds.end(); ++iter)
		{
			CorrelationId corr = *iter;
			this->cancel(corr);
		}
	}

	void Session::cancel(const CorrelationId* correlationIds, size_t numCorrelationIds)
	{
		for(size_t i = 0; i < numCorrelationIds; i++)
		{
			CorrelationId corr = correlationIds[i];
			this->cancel(corr);
		}
	}

	CorrelationId Session::openServiceAsync(const char* uri, const CorrelationId& correlationId)
	{
		this->_sessionState = serviceOpened;
		return correlationId;
	}

	SubscriptionList Session::getSubscriptions() const
	{
		return this->_subs;
	}

	bool Session::startAsync()
	{
		this->_sessionState = started;

		if (this->_asyncHandler != 0)
		{

			{
				//MarketDataRequest::MarketEvent * evtSessionStatus = new MarketDataRequest::MarketEvent(Event::SESSION_STATUS, CorrelationId(), SubscriptionList());
			
				boost::shared_ptr<MarketDataRequest::MarketEvent> evtSessionStatusP(new MarketDataRequest::MarketEvent(Event::SESSION_STATUS, CorrelationId(), SubscriptionList()));
				boost::shared_ptr<EventPtr> evtP1 = boost::dynamic_pointer_cast<EventPtr>(evtSessionStatusP);
				const Event ev1(evtP1);

				this->_asyncHandler->processEvent(ev1, this);
			}

			{
				//MarketDataRequest::MarketEvent * evtServiceStatus = new MarketDataRequest::MarketEvent(Event::SERVICE_STATUS, CorrelationId(), SubscriptionList());
			
				boost::shared_ptr<MarketDataRequest::MarketEvent> evtServiceStatusP(new MarketDataRequest::MarketEvent(Event::SERVICE_STATUS, CorrelationId(), SubscriptionList()));
				boost::shared_ptr<EventPtr> evtP2 = boost::dynamic_pointer_cast<EventPtr>(evtServiceStatusP);
				const Event ev2(evtP2);
			
				this->_asyncHandler->processEvent(ev2, this);
			}

        }
		
		return true;
	}

	Session::~Session()
	{
		if(this->_sessionTimerFunction != 0)
		{
			delete this->_sessionTimerFunction;
			this->_sessionTimerFunction = 0;
		}

		if(this->_marketSimulatorTimer != 0)
		{
			this->_marketSimulatorTimer->stop();
			delete this->_marketSimulatorTimer;
			this->_marketSimulatorTimer = 0;
		}

		while(!this->_sentRequests2.empty())
		{
			//RequestPtr* request = this->_sentRequests.front();
			boost::shared_ptr<RequestPtr> request(this->_sentRequests2.front());

			this->_sentRequests2.pop();
			
			//delete request;
			//request = 0;
		}
	}

	bool Session::start()
	{
		if(this->_sessionOptions.serverPort() == 8194 && 
			( strncmp(this->_sessionOptions.serverHost(), "localhost", 10) == 0 || strncmp(this->_sessionOptions.serverHost(), "127.0.0.1", 10) == 0 ))
		{
			this->_sessionState = started;
			return true;
		}
		else
		{
			this->_sessionState = connectionFailure;
			return false;
		}
	}

	void Session::stop()
	{
		this->_sessionState = stopped;

		if(this->_sessionTimerFunction != 0)
		{
			delete this->_sessionTimerFunction;
			this->_sessionTimerFunction = 0;
		}

		if(this->_marketSimulatorTimer != 0)
		{
			//this->_marketSimulatorTimer->stop();
			this->_marketSimulatorTimer->stopAndWait();

			delete this->_marketSimulatorTimer;
			this->_marketSimulatorTimer = 0;
		}
	}

	bool Session::openService(const char* uri)
	{
		if(strncmp("//blp/refdata", uri, 14) == 0)
		{
			this->_sessionState = serviceOpened;
			return true;
		}
		else
			return false;
	}

	Service Session::getService(const char* uri) const
	{
		if(strncmp("//blp/refdata", uri, 14) == 0)
		{
			Service result;
			return result;
		}
		else
		{
			throw sessionEx;
		}
	}

	CorrelationId Session::sendRequest(const Request& request, const CorrelationId& correlationId)
	{
		request.getRequestPtr()->setCorrelationId(correlationId);
		
		//this->_sentRequests.push(request.getRequestPtr());
		this->_sentRequests2.push(request.getRequestPtr());

		return correlationId;
	}

	Event Session::nextEvent(int timeout)
	{
		bool isLastRequest = this->_sentRequests2.size() == 1;
		
		//RequestPtr *reqP = this->_sentRequests.front();
		boost::shared_ptr<RequestPtr> reqP = this->_sentRequests2.front();
		
		this->_sentRequests2.pop();

		boost::shared_ptr<EventPtr> evtP(EventPtr::EventFactory(reqP, isLastRequest));
		//EventPtr * evt = EventPtr::EventFactory(reqP, isLastRequest);

		if(isLastRequest)
			evtP->setEventType(Event::RESPONSE);
		else
			evtP->setEventType(Event::PARTIAL_RESPONSE);

		Event result(evtP);
		return result;
	}

}