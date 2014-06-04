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

namespace BEmu
{
	namespace IntradayTickRequest
	{
		IntradayTickEvent::IntradayTickEvent(boost::shared_ptr<IntradayTickRequest> request) : EventPtr(request)
		{
			this->_requestP = request;
			this->_internalP = request;

			this->_messages = this->GenerateMessages();
		}

		IntradayTickEvent::~IntradayTickEvent()
		{
			//for(unsigned i = 0; i < this->_messages->size(); i++)
			//{
			//	delete this->_messages->at(i);
			//}

			this->_messages->clear();

			delete this->_messages;
			this->_messages = 0;
		}

		//std::vector<MessagePtr*>* IntradayTickEvent::getMessages() const
		std::vector< boost::shared_ptr<MessagePtr> > IntradayTickEvent::getMessages() const
		{
			return *(this->_messages);
		}

		//std::vector<MessagePtr*>* IntradayTickEvent::GenerateMessages()
		std::vector< boost::shared_ptr<MessagePtr> > *  IntradayTickEvent::GenerateMessages()
		{
			//std::vector<MessagePtr*>* result = new std::vector<MessagePtr*>();
			std::vector< boost::shared_ptr<MessagePtr> > * result = new std::vector< boost::shared_ptr<MessagePtr> >();

			std::string security = this->_internalP->security();
			bool isResponseError = Rules::IsSecurityError(security);

			if (isResponseError)
            {
				//IntradayTickMessage *msg = new IntradayTickMessage(this->_internalP->getCorrelationId(), this->_internalP->getService());

				boost::shared_ptr<IntradayTickMessage> mspIP(new IntradayTickMessage(this->_internalP->getCorrelationId(), this->_internalP->getService()));
				boost::shared_ptr<MessagePtr> msgP(boost::dynamic_pointer_cast<MessagePtr>(mspIP));

				result->push_back(msgP);
            }
			else
			{
				//std::map<Datetime, IntradayTickElementTuple3*> *tickData = new std::map<Datetime, IntradayTickElementTuple3*>();
				std::map<Datetime, boost::shared_ptr<IntradayTickElementTuple3> > *tickData = new std::map<Datetime, boost::shared_ptr<IntradayTickElementTuple3> >();

				if(this->_internalP->hasStartDate())
				{
					std::vector<Datetime> dates = this->_internalP->getDates();

					for(unsigned i = 0; i < dates.size(); i++)
					{
						Datetime dt = dates.at(i);
						Datetime::WeekDayEnum wd = dt.getWeekDay();

						if( (wd != Datetime::Sunday) && (wd != Datetime::Saturday) )
						{
							//IntradayTickElementTuple3 *t3 = new IntradayTickElementTuple3("TRADE", RandomDataGenerator::RandomDouble(), RandomDataGenerator::IntradayTickTradeSize());
							boost::shared_ptr<IntradayTickElementTuple3> t3(new IntradayTickElementTuple3("TRADE", RandomDataGenerator::RandomDouble(), RandomDataGenerator::IntradayTickTradeSize()));
							(*tickData)[dt] = t3;
						}
					}

					//the constructor makes copies of the arguments, so I can delete the inputs
					//IntradayTickMessage *msg = new IntradayTickMessage(this->_internalP->getCorrelationId(), this->_internalP->getService(), tickData, this->_internalP->includeConditionCodes());

					boost::shared_ptr<IntradayTickMessage> mspIP(new IntradayTickMessage(this->_internalP->getCorrelationId(), this->_internalP->getService(), tickData, this->_internalP->includeConditionCodes()));
					boost::shared_ptr<MessagePtr> msgP(boost::dynamic_pointer_cast<MessagePtr>(mspIP));

					result->push_back(msgP);
				}

				////delete the tickData map (the IntradayTickMessage constructor made copies of the data, so nothing will be lost)
				////for(std::map<Datetime, IntradayTickElementTuple3*>::const_iterator iter = tickData->begin(); iter != tickData->end(); ++iter)
				//for(std::map<Datetime, IntradayTickElementTuple3*>::const_iterator iter = tickData->begin(); iter != tickData->end(); ++iter)
				//{
				//	//note that I don't have to delete the Datetime because it is deleted in the "delete date vector" code block above
				//	IntradayTickElementTuple3* tp = iter->second;
				//	delete tp;
				//}

				delete tickData;
				tickData = 0;
			}
			
			return result;
		}

	}
}