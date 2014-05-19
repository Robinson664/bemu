//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/IntradayTickEvent.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "IntradayTickRequest/IntradayTickEvent.h"
#include "IntradayTickRequest/IntradayTickRequest.h"
#include "IntradayTickRequest/IntradayTickMessage.h"
#include "IntradayTickRequest/IntradayTickElementTuple3.h"
#include "BloombergTypes/RequestPtr.h"
#include "BloombergTypes/MessagePtr.h"
#include "BloombergTypes/Datetime.h"
#include "Types/Rules.h"
#include "Types/RandomDataGenerator.h"
#include <map>
//#include <boost/date_time/posix_time/posix_time.hpp>

namespace BEmu
{
	namespace IntradayTickRequest
	{
		IntradayTickEvent::IntradayTickEvent(IntradayTickRequest *request) : EventPtr(request)
		{
			this->_request = request;
			this->_internal = request;

			this->_messages = this->GenerateMessages();
		}

		IntradayTickEvent::~IntradayTickEvent()
		{
			for(unsigned i = 0; i < this->_messages->size(); i++)
			{
				delete this->_messages->at(i);
			}
			delete this->_messages;
			this->_messages = 0;
		}

		std::vector<MessagePtr*>* IntradayTickEvent::getMessages() const
		{
			return this->_messages;
		}

		std::vector<MessagePtr*>* IntradayTickEvent::GenerateMessages()
		{
			std::vector<MessagePtr*>* result = new std::vector<MessagePtr*>();

			std::string security = this->_internal->security();
			bool isResponseError = Rules::IsSecurityError(security);

			if (isResponseError)
            {
				IntradayTickMessage *msg = new IntradayTickMessage(this->_internal->getCorrelationId(), this->_internal->getService());
				result->push_back( (MessagePtr*)msg );
            }
			else
			{
				std::map<Datetime, IntradayTickElementTuple3*> *tickData = new std::map<Datetime, IntradayTickElementTuple3*>();

				if(this->_internal->hasStartDate())
				{
					std::vector<Datetime>* dates = this->_internal->getDates(); //i have to delete the vector

					for(unsigned i = 0; i < dates->size(); i++)
					{
						Datetime dt = dates->at(i);
						Datetime::WeekDayEnum wd = dt.getWeekDay();

						if( (wd != Datetime::Sunday) && (wd != Datetime::Saturday) )
						{
							IntradayTickElementTuple3 *t3 = new IntradayTickElementTuple3("TRADE", RandomDataGenerator::RandomDouble(), RandomDataGenerator::IntradayTickTradeSize());
							(*tickData)[dt] = t3;
						}
					}

					//the constructor makes copies of the arguments, so I can delete the inputs
					IntradayTickMessage *msg = new IntradayTickMessage(this->_internal->getCorrelationId(), this->_internal->getService(), tickData, this->_internal->includeConditionCodes());
					result->push_back(msg);

					delete dates;
					dates = 0;
				}

				//delete the tickData map (the IntradayTickMessage constructor made copies of the data, so nothing will be lost)
				for(std::map<Datetime, IntradayTickElementTuple3*>::const_iterator iter = tickData->begin(); iter != tickData->end(); ++iter)
				{
					//note that I don't have to delete the Datetime because it is deleted in the "delete date vector" code block above
					IntradayTickElementTuple3* tp = iter->second;
					delete tp;
				}
				delete tickData;
				tickData = 0;
			}
			
			return result;
		}

	}
}