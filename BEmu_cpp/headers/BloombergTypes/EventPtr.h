//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/EventPtr.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\Event.h"
#include "BloombergTypes\Datetime.h"
#include "BloombergTypes\RequestPtr.h"
#include "BloombergTypes\MessagePtr.h"
#include <exception>
#include <vector>

#pragma once

namespace BEmu
{
	class Session;
	class MessageIterator;

	//See my explanation of the RequetPtr class for an explanation of this class
	class EventPtr
	{
		private:
			virtual std::vector<MessagePtr*> *getMessages() const;
			static EventPtr* EventFactory(RequestPtr *request, bool isLastRequest);

		protected:
			RequestPtr *_request;
			EventPtr(RequestPtr * request);
			EventPtr(const EventPtr &src);
			Event::EventType _type;

		public:

			class EventPtrException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} eventPtrEx;

			Event::EventType eventType();

			friend class Session;
			friend class MessageIterator;
	};
}