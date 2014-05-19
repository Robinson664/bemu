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

#include "IntradayBarRequest/RequestIntradayBar.h"
#include "IntradayBarRequest/EventIntradayBar.h"

#include "HistoricalDataRequest/HistoricRequest.h"
#include "HistoricalDataRequest/HistoricEvent.h"

#include "ReferenceDataRequest/RequestReference.h"
#include "ReferenceDataRequest/EventReference.h"

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

	EventPtr::~EventPtr()
	{

	}

	std::vector<MessagePtr*>* EventPtr::getMessages() const
	{
		throw eventPtrEx;
	}

	Event::EventType EventPtr::getEventType() const
	{
		return this->_type;
	}

	void EventPtr::setEventType(Event::EventType evtType)
	{
		this->_type = evtType;
	}

	EventPtr* EventPtr::EventFactory(RequestPtr *request, bool isLastRequest)
	{
		if(request->getRequestType() == RequestPtr::historic)
		{
			HistoricalDataRequest::HistoricRequest * req = (HistoricalDataRequest::HistoricRequest *)request;
			HistoricalDataRequest::HistoricEvent * evt = new HistoricalDataRequest::HistoricEvent(req);

			return evt;
		}
		else if(request->getRequestType() == RequestPtr::intradayBar)
		{
			IntradayBarRequest::RequestIntradayBar * req = (IntradayBarRequest::RequestIntradayBar *)request;
			IntradayBarRequest::EventIntradayBar * evt = new IntradayBarRequest::EventIntradayBar(req);
			
			return evt;
		}
		else if(request->getRequestType() == RequestPtr::intradayTick)
		{
			IntradayTickRequest::RequestIntradayTick * req = (IntradayTickRequest::RequestIntradayTick *)request;
			IntradayTickRequest::EventIntradayTick * evt = new IntradayTickRequest::EventIntradayTick(req);
			return evt;
		}
		else if(request->getRequestType() == RequestPtr::reference)
		{
			ReferenceDataRequest::RequestReference * req = (ReferenceDataRequest::RequestReference *)request;
			ReferenceDataRequest::EventReference * evt = new ReferenceDataRequest::EventReference(req);
			return evt;
		}
		throw request->requestEx;
	}

}