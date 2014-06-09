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
		ReferenceEvent::ReferenceEvent(const boost::shared_ptr<ReferenceRequest>& request) : 
			EventPtr(boost::dynamic_pointer_cast<RequestPtr>(request)),
			_internalP(request)
		{
			this->_messages = this->generateMessages();
		}

		ReferenceEvent::~ReferenceEvent()
		{
			this->_messages.clear();
		}

		std::vector< boost::shared_ptr<MessagePtr> > ReferenceEvent::getMessages() const
		{
			return this->_messages;
		}

		std::vector< boost::shared_ptr<MessagePtr> > ReferenceEvent::generateMessages() const
		{
			// _CRTDBG_MAP_ALLOC reports a memory leak here.  I'll ignore it.
			const boost::regex exIsOption("[A-Z]{1,4}\\s+\\d{6}[CP]\\d{8} EQUITY");

			std::vector< boost::shared_ptr<MessagePtr> > result;

			std::map<std::string, std::map<std::string, ObjectType>> securities;

			std::vector<std::string> reqSecurities = this->_internalP->getSecurities();
			for(std::vector<std::string>::const_iterator iterSec = reqSecurities.begin(); iterSec != reqSecurities.end(); ++iterSec)
			{
				std::string security = *iterSec;
				if(securities.find(security) == securities.end()) //if the map doesn't contain the security
				{
					// _CRTDBG_MAP_ALLOC reports a memory leak here.  I'll ignore it.
					bool isOption = boost::regex_match(security, exIsOption);

					std::map<std::string, ObjectType> fieldData;
					std::vector<std::string> badFields;

					std::vector<std::string> reqFields = this->_internalP->getFields();
					for(std::vector<std::string>::const_iterator iterField = reqFields.begin(); iterField != reqFields.end(); ++iterField)
					{
						std::string reqField = *iterField;

						ObjectType value(RandomDataGenerator::ReferenceDataFromFieldName(reqField, security, isOption, this->_internalP));

						bool isnull = value.IsNull();
						bool inMap = fieldData.find(reqField) != fieldData.end();

						if( !isnull && !inMap ) //if the value isn't null and the field isn't already in the map
							fieldData[reqField] = value;
					}
					
					securities[security] = fieldData;
				}
			}

			boost::shared_ptr<ReferenceMessage> msgRP(new ReferenceMessage(this->_internalP->getCorrelationId(), securities));
			boost::shared_ptr<MessagePtr> msgP(boost::dynamic_pointer_cast<MessagePtr>(msgRP));

			result.push_back(msgP);

			return result;
		}

	}
}