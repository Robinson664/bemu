//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ReferenceMessage.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ReferenceMessage.h"
#include "ReferenceDataRequest/ReferenceElementSecurityDataArray.h"
#include "ReferenceDataRequest/ReferenceElement.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ReferenceMessage::ReferenceMessage(const CorrelationId& corr, const std::map<std::string, std::map<std::string, ObjectType>*>& fieldData) : MessagePtr(Name("ReferenceDataResponse"), corr)
		{
			this->_securities = new ReferenceElementSecurityDataArray(fieldData);
		}

		ReferenceMessage::~ReferenceMessage()
		{
			delete this->_securities;
			this->_securities = 0;
		}

		std::stack<ElementPtr*> ReferenceMessage::getRootElements() const
		{
			std::stack<ElementPtr*> result;

			if(this->_securities != 0)
				result.push(this->_securities);

			return result;
		}

		const char* ReferenceMessage::topicName() const
		{
			return "";
		}

		ElementPtr * ReferenceMessage::asElement() const
		{
			ElementPtr * result = new ReferenceElement(*this);
			return result;
		}

		ElementPtr * ReferenceMessage::firstElement() const
		{
			return this->_securities;
		}

		ElementPtr * ReferenceMessage::getElement(const char* name) const
		{
			if(strncmp(name, "securityData", 13) == 0)
				return this->_securities;

			else
				throw messageEx;
		}

		std::ostream& ReferenceMessage::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "ReferenceDataResponse (choice) = {" << std::endl;
			this->_securities->print(stream, 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}


	}
}