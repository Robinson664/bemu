//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ReferenceEvent.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ReferenceEvent.h"
#include "ReferenceDataRequest/ReferenceRequest.h"
#include "ReferenceDataRequest/ReferenceMessage.h"
#include <map>
#include "Types/ObjectType.h"
#include "Types/RandomDataGenerator.h"
#include <boost/regex.hpp>

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ReferenceEvent::ReferenceEvent(boost::shared_ptr<ReferenceRequest> request) : 
			EventPtr(request),
			_internalP(request)
		{
			this->_requestP = boost::dynamic_pointer_cast<RequestPtr>(request);
			//this->_internalP = request;
			this->_messages = this->generateMessages(); //deleted in destructor
		}

		ReferenceEvent::~ReferenceEvent()
		{
			//for(std::vector<MessagePtr*>::const_iterator iter = this->_messages->begin(); iter != this->_messages->end(); ++iter)
			//{
			//	MessagePtr * msg = *iter;
			//	delete msg;
			//}

			this->_messages->clear();

			delete this->_messages;
			this->_messages = 0;
		}

		std::vector< boost::shared_ptr<MessagePtr> > ReferenceEvent::getMessages() const
		//std::vector<MessagePtr*> * ReferenceEvent::getMessages() const
		{
			return *(this->_messages);
		}

		std::vector< boost::shared_ptr<MessagePtr> > * ReferenceEvent::generateMessages() const
		//std::vector<MessagePtr*> * ReferenceEvent::generateMessages() const
		{
			const boost::regex exIsOption("[A-Z]{1,4}\\s+\\d{6}[CP]\\d{8} EQUITY");

			std::vector< boost::shared_ptr<MessagePtr> > * result = new std::vector< boost::shared_ptr<MessagePtr> >(); //deleted in destructor (as this->_messages)
			//std::vector<MessagePtr*> * result = new std::vector<MessagePtr*>(); //deleted in destructor (as this->_messages)

			std::map<std::string, std::map<std::string, ObjectType>*> securities;

			std::vector<std::string> reqSecurities = this->_internalP->getSecurities();
			for(std::vector<std::string>::const_iterator iterSec = reqSecurities.begin(); iterSec != reqSecurities.end(); ++iterSec)
			{
				std::string security = *iterSec;
				if(securities.find(security) == securities.end()) //if the map doesn't contain the security
				{
					bool isOption = boost::regex_match(security, exIsOption);

					std::map<std::string, ObjectType> * fieldData = new std::map<std::string, ObjectType>(); //deleted in the outer loop below
					securities[security] = fieldData;

					std::vector<std::string> badFields;

					std::vector<std::string> reqFields = this->_internalP->getFields();
					for(std::vector<std::string>::const_iterator iterField = reqFields.begin(); iterField != reqFields.end(); ++iterField)
					{
						std::string reqField = *iterField;

						ObjectType value(RandomDataGenerator::ReferenceDataFromFieldName(reqField, security, isOption, this->_internalP));

						bool isnull = value.IsNull();
						bool inMap = fieldData->find(reqField) != fieldData->end();

						if( !isnull && !inMap ) //if the value isn't null and the field isn't already in the map
							(*fieldData)[reqField] = value;
					}
				}
			}

			boost::shared_ptr<ReferenceMessage> msgRP(new ReferenceMessage(this->_internalP->getCorrelationId(), securities));
			//ReferenceMessage * msg = new ReferenceMessage(this->_internalP->getCorrelationId(), securities); //deleted in destructor

			boost::shared_ptr<MessagePtr> msgP(boost::dynamic_pointer_cast<MessagePtr>(msgRP));

			//no longer need the collections in "securities"
			for(std::map<std::string, std::map<std::string, ObjectType>*>::iterator iterSec = securities.begin(); iterSec != securities.end(); ++iterSec)
			{
				std::map<std::string, ObjectType> * mm = iterSec->second;
				delete mm;
			}

			result->push_back(msgP);

			return result;
		}

	}
}