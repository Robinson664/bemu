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

#include "MarketDataRequest/EventMarket.h"
#include "BloombergTypes/CorrelationId.h"
#include "BloombergTypes/SubscriptionList.h"


namespace BEmu
{
	//Session::Session(const Session& session)
	//{
	//	srand((unsigned int)time(0));
	//	this->_sessionState = session._sessionState;

	//	this->_sessionOptions.setServerHost(session._sessionOptions.serverHost());
	//	this->_sessionOptions.setServerPort(session._sessionOptions.serverPort());

	//	this->_sessionTimerFunction = 0;
	//	this->_marketSimulatorTimer = 0;
	//}

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

		MarketDataRequest::EventMarket * evtSubStatus = new MarketDataRequest::EventMarket(Event::SUBSCRIPTION_STATUS, CorrelationId(), subscriptionList);

		if (this->_asyncHandler != 0)
        {
			this->_asyncHandler->processEvent(evtSubStatus, this);
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
		this->_subs.remove(correlationId);
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

		MarketDataRequest::EventMarket * evtSessionStatus = new MarketDataRequest::EventMarket(Event::SESSION_STATUS, CorrelationId(), SubscriptionList());
		MarketDataRequest::EventMarket * evtServiceStatus = new MarketDataRequest::EventMarket(Event::SERVICE_STATUS, CorrelationId(), SubscriptionList());

        if (this->_asyncHandler != 0)
        {
			this->_asyncHandler->processEvent(evtSessionStatus, this);
			this->_asyncHandler->processEvent(evtServiceStatus, this);
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

		while(!this->_sentRequests.empty())
		{
			RequestPtr* request = this->_sentRequests.front();
			this->_sentRequests.pop();
			delete request;
			request = 0;
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
		this->_sentRequests.push(request.getRequestPtr());
		return correlationId;
	}

	Event Session::nextEvent(int timeout)
	{
		bool isLastRequest = this->_sentRequests.size() == 1;
		RequestPtr *reqP = this->_sentRequests.front();
		this->_sentRequests.pop();

		EventPtr * evt = EventPtr::EventFactory(reqP, isLastRequest);

		if(isLastRequest)
			evt->setEventType(Event::RESPONSE);
		else
			evt->setEventType(Event::PARTIAL_RESPONSE);

		Event result(evt);
		return result;
	}

}