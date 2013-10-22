//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/MessageIntradayTick.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "IntradayTickRequest/MessageIntradayTick.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

#include "BloombergTypes\CorrelationId.h"
#include "BloombergTypes\Service.h"
#include "IntradayTickRequest/ElementIntradayTickDataParent.h"
#include "IntradayTickRequest/ElementIntradayTickResponseError.h"
#include "IntradayTickRequest/ElementIntradayTickDataTuple3.h"
#include "IntradayTickRequest/ElementReference.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		//makes copies of the arguments
		MessageIntradayTick::MessageIntradayTick(CorrelationId *corr, const Service *service, std::map<Datetime*, ElementIntradayTickDataTuple3*> *ticks, bool includeConditionCodes)
			: MessagePtr(Name("IntradayTickResponse"), corr)
		{
			this->_parent = new ElementIntradayTickDataParent(ticks, includeConditionCodes);
			this->_responseError = 0;
			this->_isResponseError = false;
		}

		MessageIntradayTick::MessageIntradayTick(CorrelationId *corr, const Service *service)
			: MessagePtr(Name("IntradayTickResponse"), corr)
		{
			this->_parent = 0;
			this->_responseError = new ElementIntradayTickResponseError();
			this->_isResponseError = true;
		}

		MessageIntradayTick::~MessageIntradayTick()
		{
			delete this->_parent;
			this->_parent = 0;

			delete this->_responseError;
			this->_responseError = 0;
		}

		const ElementPtr * MessageIntradayTick::getElement(const char* name) const
		{
			if(this->_isResponseError && strncmp(name, "responseError", 13) == 0)
				return this->_responseError;

			else if(!this->_isResponseError && strncmp(name, "tickData", 8) == 0)
				return this->_parent;

			else
				throw messageEx;
		}

		bool MessageIntradayTick::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(this->_isResponseError && strncmp(name, "responseError", 13) == 0) ||
				(!this->_isResponseError && strncmp(name, "tickData", 8) == 0);
		}

		ElementPtr* MessageIntradayTick::firstElement() const
		{
			if(this->_isResponseError)
				return this->_responseError;
			else
				return this->_parent;
		}

		const char* MessageIntradayTick::topicName() const
		{
			return "";
		}

		int MessageIntradayTick::numElements() const
		{
			return 1;
		}

		const ElementPtr * MessageIntradayTick::asElement() const
		{
			const MessageIntradayTick msg = *this;
			ElementPtr * resultP = new ElementReference(msg);
			return resultP;
		}

		std::ostream& MessageIntradayTick::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "IntradayTickResponse = {" << std::endl;
			
			if(this->_isResponseError)
				this->_responseError->print(stream, level + 1, spacesPerLevel);
			else
				this->_parent->print(stream, level + 1, spacesPerLevel);

			stream << '}' << std::endl;
			return stream;
		}

	}
}