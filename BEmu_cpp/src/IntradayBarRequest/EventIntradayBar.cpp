//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/EventIntradayBar.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayBarRequest/MessageIntradayBar.h"
#include "IntradayBarRequest/EventIntradayBar.h"
#include "IntradayBarRequest/RequestIntradayBar.h"
#include "BloombergTypes/MessagePtr.h"
#include "Types/Rules.h"
#include "Types/RandomDataGenerator.h"
#include <vector>

namespace BEmu
{
	namespace IntradayBarRequest
	{
		EventIntradayBar::EventIntradayBar(RequestIntradayBar * request) : EventPtr(request)
		{
			this->_request = request;
			this->_internal = request;

			this->_message = this->GenerateMessages();
		}

		std::vector<MessagePtr*>* EventIntradayBar::GenerateMessages() const
		{
			std::vector<MessagePtr*>* result = new std::vector<MessagePtr*>();
			RequestIntradayBar * ireq = this->_internal;

			bool isSecurityError = Rules::IsSecurityError(ireq->security());
			if(isSecurityError)
			{
				MessagePtr * msg = new MessageIntradayBar(this->_internal->getCorrelationId(), this->_internal->getService(), this->_internal->security());
				result->push_back(msg);
			}
			else
			{
				std::vector<BarTickDataType*> barData;
				if(ireq->hasStartDate())
				{
					std::vector<Datetime>* datetimes = ireq->getDateTimes();
					for(std::vector<Datetime>::const_iterator iter = datetimes->begin(); iter != datetimes->end(); ++iter)
					{
						Datetime date = *iter;
						BarTickDataType * bar = RandomDataGenerator::GenerateBarData(date);
						barData.push_back(bar);
					}
					
					delete datetimes;
					datetimes = 0;
				}

				MessagePtr * msg = new MessageIntradayBar(this->_internal->getCorrelationId(), ireq->getService(), barData);
				result->push_back(msg);
			}

			return result;
		}

		std::vector<MessagePtr*>* EventIntradayBar::getMessages() const
		{
			return this->_message;
		}

	}
}