//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/MessageIntradayTick.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include <map>
#include "BloombergTypes/MessagePtr.h"

namespace BEmu
{
	class CorrelationId;
	class Service;
	class Datetime;
	class ElementPtr;

	namespace IntradayTickRequest
	{
		class ElementIntradayTickDataParent;
		class ElementIntradayTickResponseError;
		class ElementIntradayTickDataTuple3;

		class MessageIntradayTick : public MessagePtr
		{
			private:		
				ElementIntradayTickDataParent *_parent;
				ElementIntradayTickResponseError *_responseError;
				bool _isResponseError;

			public:
				MessageIntradayTick(CorrelationId *corr, const Service *service, std::map<Datetime*, ElementIntradayTickDataTuple3*> *ticks, bool includeConditionCodes);
				MessageIntradayTick(CorrelationId *corr, const Service *service);
				~MessageIntradayTick();
				ElementPtr* firstElement() const;

				virtual const char* topicName() const;
				virtual int numElements() const;
				virtual const ElementPtr * asElement() const;
				virtual const ElementPtr * getElement(const char* name) const;
				virtual bool hasElement(const char* name, bool excludeNullElements=false) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}