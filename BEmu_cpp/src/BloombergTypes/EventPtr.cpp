//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/EventPtr.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Event.h"
#include "BloombergTypes/EventPtr.h"
#include "BloombergTypes/RequestPtr.h"
#include <exception>
#include <vector>

#include "IntradayTickRequest/RequestIntradayTick.h"
#include "IntradayTickRequest/EventIntradayTick.h"

namespace BEmu
{
	EventPtr::EventPtr(RequestPtr * request)
	{
		this->_request = _request;
	}

	EventPtr::EventPtr(const EventPtr &src)
	{
		this->_request = src._request;
	}

	std::vector<MessagePtr*>* EventPtr::getMessages() const
	{
		throw eventPtrEx;
	}

	Event::EventType EventPtr::eventType()
	{
		return this->_type;
	}

	EventPtr* EventPtr::EventFactory(RequestPtr *request, bool isLastRequest)
	{
		if(request->_requestType == RequestPtr::historic)
		{
			throw request->requestEx;
		}
		else if(request->_requestType == RequestPtr::intradayBar)
		{
			throw request->requestEx;
		}
		else if(request->_requestType == RequestPtr::intradayTick)
		{
			IntradayTickRequest::RequestIntradayTick *req = (IntradayTickRequest::RequestIntradayTick *)request;
			IntradayTickRequest::EventIntradayTick *evt = new IntradayTickRequest::EventIntradayTick(req);

			EventPtr * evt2 = evt;

			return evt;
		}
		else if(request->_requestType == RequestPtr::reference)
		{
			throw request->requestEx;
		}
		throw request->requestEx;
	}

}