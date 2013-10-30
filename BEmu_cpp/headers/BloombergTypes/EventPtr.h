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

namespace BEmu
{
	class Name;
	class Session;
	class MessageIterator;
	class Datetime;
	class RequestPtr;
	class MessagePtr;

	//See my explanation of the RequetPtr class for an explanation of this class
	class EventPtr
	{
		protected:
			RequestPtr *_request;
			Event::EventType _type;

		public:
			EventPtr(RequestPtr * request);
			EventPtr(const EventPtr &src);
			~EventPtr();
			
			Event::EventType getEventType() const;
			void setEventType(Event::EventType evtType);

			virtual std::vector<MessagePtr*> *getMessages() const;
			static EventPtr* EventFactory(RequestPtr *request, bool isLastRequest);

			class EventPtrException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} eventPtrEx;
	};
}