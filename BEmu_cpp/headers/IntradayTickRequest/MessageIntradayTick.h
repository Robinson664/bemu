//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/MessageIntradayTick.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\MessagePtr.h"
#include "BloombergTypes\Datetime.h"

#include "BloombergTypes\Element.h"
#include "BloombergTypes\ElementPtr.h"
#include "BloombergTypes\CorrelationId.h"
#include "BloombergTypes\Service.h"
#include "IntradayTickRequest/ElementIntradayTickDataParent.h"
#include "IntradayTickRequest/ElementIntradayTickResponseError.h"
#include "IntradayTickRequest/ElementIntradayTickDataTuple3.h"

#include <map>

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class ElementReference;
		class EventIntradayTick;

		class MessageIntradayTick : private MessagePtr
		{
			private:		
				ElementIntradayTickDataParent *_parent;
				ElementIntradayTickResponseError *_responseError;
				bool _isResponseError;

				MessageIntradayTick(CorrelationId *corr, const Service *service, std::map<Datetime*, ElementIntradayTickDataTuple3*> *ticks, bool includeConditionCodes);
				MessageIntradayTick(CorrelationId *corr, const Service *service);
				~MessageIntradayTick();
				ElementPtr* firstElement() const;

			public:
				virtual const char* topicName() const;
				virtual int numElements() const;
				virtual const ElementPtr * asElement() const;
				virtual const ElementPtr * getElement(const char* name) const;
				virtual bool hasElement(const char* name, bool excludeNullElements=false) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;

				friend class ElementReference; //The ElementReference constructor needs access to the firstElement method
				friend class EventIntradayTick;
		};
	}
}