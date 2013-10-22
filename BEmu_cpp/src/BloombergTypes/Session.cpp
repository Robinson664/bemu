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

namespace BEmu
{
	Session::Session(const Session& session)
	{
		srand(time(0));
		this->_sessionState = session._sessionState;

		this->_sessionOptions.setServerHost(session._sessionOptions.serverHost());
		this->_sessionOptions.setServerPort(session._sessionOptions.serverPort());
	}

	Session::Session(const SessionOptions& options)
	{
		this->_sessionState = initialized;

		this->_sessionOptions.setServerHost(options.serverHost());
		this->_sessionOptions.setServerPort(options.serverPort());
	}

	Session::~Session()
	{
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
			( strncmp(this->_sessionOptions.serverHost(), "localhost", 9) == 0 || strncmp(this->_sessionOptions.serverHost(), "127.0.0.1", 9) ))
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
	}

	bool Session::openService(const char* uri)
	{
		if(strncmp("//blp/refdata", uri, 13) == 0)
		{
			this->_sessionState = serviceOpened;
			return true;
		}
		else
			return false;
	}

	Service Session::getService(const char* uri) const
	{
		if(strncmp("//blp/refdata", uri, 13) == 0)
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
		request._ptr->_correlationId = new CorrelationId(correlationId);
		this->_sentRequests.push(request._ptr);
		return correlationId;
	}

	Event Session::nextEvent(int timeout)
	{
		bool isLastRequest = this->_sentRequests.size() == 1;
		RequestPtr *reqP = this->_sentRequests.front();
		this->_sentRequests.pop();

		EventPtr * evt = EventPtr::EventFactory(reqP, isLastRequest);

		if(isLastRequest)
			evt->_type = Event::RESPONSE;
		else
			evt->_type = Event::PARTIAL_RESPONSE;

		Event result(evt);
		return result;
	}

}