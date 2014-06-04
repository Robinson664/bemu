//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/EventPtr.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/Event.h"
#include <exception>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace BEmu
{
	class Name;
	class Session;
	class MessageIterator;
	class Datetime;
	class RequestPtr;
	class MessagePtr;

	class EventPtr
	{
		protected:
			//RequestPtr *_request;
			boost::shared_ptr<RequestPtr> _requestP;

			Event::EventType _type;

		public:
			//EventPtr(RequestPtr * request);
			EventPtr(boost::shared_ptr<RequestPtr> request);

			EventPtr(const EventPtr &src);
			virtual ~EventPtr();
			
			Event::EventType getEventType() const;
			void setEventType(Event::EventType evtType);

			//virtual std::vector<MessagePtr*> * getMessages() const;
			virtual std::vector< boost::shared_ptr<MessagePtr> > getMessages() const;
			
			//static EventPtr * EventFactory(RequestPtr *request, bool isLastRequest);
			static boost::shared_ptr<EventPtr> EventFactory(boost::shared_ptr<RequestPtr> request, bool isLastRequest);

			class EventPtrException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} eventPtrEx;
	};
}