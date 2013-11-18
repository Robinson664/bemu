//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/EventReference.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/EventReference.h"
#include "ReferenceDataRequest/RequestReference.h"
#include "ReferenceDataRequest/MessageReference.h"
#include <map>
#include "Types/ObjectType.h"
#include "Types/RandomDataGenerator.h"
#include <boost/regex.hpp>

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		EventReference::EventReference(RequestReference * request) : EventPtr(request)
		{
			this->_request = request;
			this->_internal = request;
			this->_messages = this->generateMessages();
		}

		EventReference::~EventReference()
		{
			for(std::vector<MessagePtr*>::const_iterator iter = this->_messages->begin(); iter != this->_messages->end(); ++iter)
			{
				MessagePtr * msg = *iter;
				delete msg;
			}

			delete this->_messages;
			this->_messages = 0;
		}

		std::vector<MessagePtr*> * EventReference::getMessages() const
		{
			return this->_messages;
		}

		std::vector<MessagePtr*> * EventReference::generateMessages() const
		{
			const boost::regex exIsOption("[A-Z]{1,4}\\s+\\d{6}[CP]\\d{8} EQUITY");

			std::vector<MessagePtr*> * result = new std::vector<MessagePtr*>();

			std::map<std::string, std::map<std::string, ObjectType>*> securities;

			std::vector<std::string> reqSeecurities = this->_internal->getSecurities();
			for(std::vector<std::string>::const_iterator iterSec = reqSeecurities.begin(); iterSec != reqSeecurities.end(); ++iterSec)
			{
				std::string security = *iterSec;
				if(securities.find(security) == securities.end()) //if the map doesn't contain the security
				{
					bool isOption = boost::regex_match(security, exIsOption);

					std::map<std::string, ObjectType> * fieldData = new std::map<std::string, ObjectType>();
					securities[security] = fieldData;

					std::vector<std::string> badFields;

					std::vector<std::string> reqFields = this->_internal->getFields();
					for(std::vector<std::string>::const_iterator iterField = reqFields.begin(); iterField != reqFields.end(); ++iterField)
					{
						std::string reqField = *iterField;

						ObjectType value(RandomDataGenerator::ReferenceDataFromFieldName(reqField, security, isOption, this->_internal));

						bool isnull = value.IsNull();
						bool inMap = fieldData->find(reqField) != fieldData->end();

						if( !isnull && !inMap ) //if the value isn't null and the field isn't already in the map
							(*fieldData)[reqField] = value;
					}


				}
			}

			MessageReference * msg = new MessageReference(this->_request->getCorrelationId(), securities);
			result->push_back(msg);

			return result;
		}

	}
}