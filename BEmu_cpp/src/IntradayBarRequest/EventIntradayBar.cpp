//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/IntradayBarEvent.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayBarRequest/IntradayBarMessage.h"
#include "IntradayBarRequest/IntradayBarEvent.h"
#include "IntradayBarRequest/IntradayBarRequest.h"
#include "BloombergTypes/MessagePtr.h"
#include "Types/Rules.h"
#include "Types/RandomDataGenerator.h"
#include <vector>

namespace BEmu
{
	namespace IntradayBarRequest
	{
		IntradayBarEvent::IntradayBarEvent(IntradayBarRequest * request) : EventPtr(request)
		{
			this->_request = request;
			this->_internal = request;

			this->_message = this->GenerateMessages();
		}

		std::vector<MessagePtr*>* IntradayBarEvent::GenerateMessages() const
		{
			std::vector<MessagePtr*>* result = new std::vector<MessagePtr*>();
			IntradayBarRequest * ireq = this->_internal;

			bool isSecurityError = Rules::IsSecurityError(ireq->security());
			if(isSecurityError)
			{
				MessagePtr * msg = new IntradayBarMessage(this->_internal->getCorrelationId(), this->_internal->getService(), this->_internal->security());
				result->push_back(msg);
			}
			else
			{
				std::vector<IntradayBarTickDataType*> barData;
				if(ireq->hasStartDate())
				{
					std::vector<Datetime>* datetimes = ireq->getDateTimes();
					for(std::vector<Datetime>::const_iterator iter = datetimes->begin(); iter != datetimes->end(); ++iter)
					{
						Datetime date = *iter;
						IntradayBarTickDataType * bar = RandomDataGenerator::GenerateBarData(date);
						barData.push_back(bar);
					}
					
					delete datetimes;
					datetimes = 0;
				}

				MessagePtr * msg = new IntradayBarMessage(this->_internal->getCorrelationId(), ireq->getService(), barData);
				result->push_back(msg);
			}

			return result;
		}

		std::vector<MessagePtr*>* IntradayBarEvent::getMessages() const
		{
			return this->_message;
		}

	}
}