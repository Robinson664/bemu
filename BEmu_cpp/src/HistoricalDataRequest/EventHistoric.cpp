//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/HistoricEvent.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/HistoricEvent.h"
#include "HistoricalDataRequest/HistoricRequest.h"
#include "HistoricalDataRequest/HistoricMessage.h"
#include "BloombergTypes/Datetime.h"
#include "Types/ObjectType.h"
#include "Types/Rules.h"
#include "Types/RandomDataGenerator.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		HistoricEvent::HistoricEvent(HistoricRequest * request) : EventPtr(request)
		{
			this->_request = request;
			this->_internal = request;
			this->_messages = this->GenerateMessages();
		}

		HistoricEvent::~HistoricEvent()
		{
			delete this->_messages;
			this->_messages = 0;
		}

				
		std::vector<MessagePtr*> * HistoricEvent::getMessages() const
		{
			return this->_messages;
		}

		std::vector<MessagePtr*> * HistoricEvent::GenerateMessages() const
		{
			std::vector<MessagePtr*> * result = new std::vector<MessagePtr*>();

			std::vector<std::string> badFields;
			std::vector<std::string> rfields(this->_internal->fields());
			for(std::vector<std::string>::const_iterator iterField = rfields.begin(); iterField != rfields.end(); ++iterField)
			{
				std::string field = *iterField;

				if(Rules::IsBadField(field))
					badFields.push_back(field);
			}

			std::vector<std::string> securities(this->_internal->securities());
			for(std::vector<std::string>::const_iterator iterSec = securities.begin(); iterSec != securities.end(); ++iterSec)
			{
				std::string sec = *iterSec;

				std::map<Datetime, std::map<std::string, ObjectType> *> * fieldData = new std::map<Datetime, std::map<std::string, ObjectType> *>();

				if(this->_internal->hasStartDate())
				{
					Datetime dtStart = this->_internal->dtStart();
					std::vector<Datetime> * dates = this->_internal->getDates();

					for(std::vector<Datetime>::const_iterator iterDate = dates->begin(); iterDate != dates->end(); ++iterDate)
					{
						Datetime date = *iterDate;
						if(date.getWeekDay() != Datetime::Saturday && date.getWeekDay() != Datetime::Sunday)
						{
							std::map<std::string, ObjectType> * fields = new std::map<std::string, ObjectType>();

							(*fieldData)[date] = fields;

							for(std::vector<std::string>::const_iterator iterField2 = rfields.begin(); iterField2 != rfields.end(); ++iterField2)
							{
								std::string field2 = *iterField2;

								if(!Rules::IsBadField(field2))
									fields->operator[](field2) = ObjectType(RandomDataGenerator::RandomDouble());
							}
						}
					}

					HistoricMessage * msg = new HistoricMessage(this->_internal->getCorrelationId(), sec, badFields, fieldData, result->size());
					result->push_back(msg);

					delete dates;
					dates = 0;
				}
			}

			return result;
		}

	}
}