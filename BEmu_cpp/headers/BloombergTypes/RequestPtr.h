//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/RequestPtr.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\Datetime.h"
#include "BloombergTypes\Element.h"
#include "BloombergTypes\CorrelationId.h"
#include <exception>

#pragma once

namespace BEmu
{
	class Service;
	class Session;
	class EventPtr;

	namespace IntradayTickRequest
	{
		class EventIntradayTick;
	}

	class RequestPtr
	{
		private:
			//Session::sendRequest needs to set the correlationId of a given request.  The API marks the Request parameter as a const, so the mutable here overrides that.
			mutable CorrelationId *_correlationId;

		protected:	
			RequestPtr();
			RequestPtr(const RequestPtr &src);

			enum RequestTypeEnum { historic, reference, intradayTick, intradayBar };
			RequestTypeEnum _requestType;

	
		public:

			class RequestException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} requestEx;

			friend class Service; //Service::createRequest() needs access to the private Request() constructor
			friend class Session;
			friend class EventPtr; //EventPtr::EventFactory() needs access to the private Request() constructor and _requestType 
			
			virtual void append(const char* name, const char* value);
			void append(const Name& name, const char* value);

			virtual void set(const char* name, const char* value);
			void set(const Name& name, const char* value);

			virtual void set(const char* name, bool value);
			void set(const Name& name, bool value);

			virtual void set(const char* name, int value);
			void set(const Name& name, int value);

			virtual void set(const char* name, const Datetime& value);
			void set(const Name& name, const Datetime& value);

			virtual Element getElement(const char* name);
			Element getElement(const Name& name);

			friend class IntradayTickRequest::EventIntradayTick;

			// The C# version of the code has a "HasElement(string)" method in the Request class.  The C++ version of the code doesn't.
			//    In the C++ version, an equivalent call would be "request.asElement().hasElement(string)".
			//    Given that the caller creates a request object, the caller should be aware of whether or not a Request object has some given Element,
			//      I find the Request.hasElement(...) methods unnecessary.  (Maybe the API developers thought the same way)
			//    Note that I haven't implemented all of the asElement()s for the Requests.  I can't think of a use-case for asElements()s.
	};
}