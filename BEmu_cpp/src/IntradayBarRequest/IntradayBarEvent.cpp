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
		IntradayBarEvent::IntradayBarEvent(const boost::shared_ptr<IntradayBarRequest>& request) :
			EventPtr(boost::dynamic_pointer_cast<RequestPtr>(request)),
			_internalP(request)
		{
			this->_messages = this->GenerateMessages();
		}

		IntradayBarEvent::~IntradayBarEvent()
		{
			this->_messages.clear();
		}

		std::vector< boost::shared_ptr<MessagePtr> > IntradayBarEvent::GenerateMessages() const
		{
			std::vector< boost::shared_ptr<MessagePtr> > result;

			boost::shared_ptr<IntradayBarRequest> ireq = this->_internalP;

			bool isSecurityError = Rules::IsSecurityError(ireq->security());
			if(isSecurityError)
			{
				boost::shared_ptr<IntradayBarMessage> msgIP(new IntradayBarMessage(this->_internalP->getCorrelationId(), this->_internalP->getService(), this->_internalP->security()));
				boost::shared_ptr<MessagePtr> msgP(boost::dynamic_pointer_cast<MessagePtr>(msgIP));

				result.push_back(msgP);
			}
			else
			{
				std::vector< boost::shared_ptr<IntradayBarTickDataType> > barData;

				if(ireq->hasStartDate())
				{
					std::vector<Datetime> datetimes = ireq->getDateTimes();
					for(std::vector<Datetime>::const_iterator iter = datetimes.begin(); iter != datetimes.end(); ++iter)
					{
						Datetime date = *iter;
						boost::shared_ptr<IntradayBarTickDataType> bar( RandomDataGenerator::GenerateBarData(date) );						
						
						barData.push_back(bar);
					}
				}
				
				boost::shared_ptr<IntradayBarMessage> msgIP(new IntradayBarMessage(this->_internalP->getCorrelationId(), ireq->getService(), barData));
				boost::shared_ptr<MessagePtr> msgP(boost::dynamic_pointer_cast<MessagePtr>(msgIP));

				result.push_back(msgP);
			}

			return result;
		}

		std::vector< boost::shared_ptr<MessagePtr> > IntradayBarEvent::getMessages() const
		{
			return this->_messages;
		}

	}
}