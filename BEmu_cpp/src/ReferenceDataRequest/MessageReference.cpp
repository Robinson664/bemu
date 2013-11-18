//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/MessageReference.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/MessageReference.h"
#include "ReferenceDataRequest/ElementReferenceSecurityDataArray.h"
#include "ReferenceDataRequest/ElementReference.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		MessageReference::MessageReference(const CorrelationId& corr, const std::map<std::string, std::map<std::string, ObjectType>*>& fieldData) : MessagePtr(Name("ReferenceDataResponse"), corr)
		{
			this->_securities = new ElementReferenceSecurityDataArray(fieldData);
		}

		MessageReference::~MessageReference()
		{
			delete this->_securities;
			this->_securities = 0;
		}

		const char* MessageReference::topicName() const
		{
			return "";
		}

		ElementPtr * MessageReference::asElement() const
		{
			ElementPtr * result = new ElementReference(*this);
			return result;
		}

		ElementPtr * MessageReference::firstElement() const
		{
			return this->_securities;
		}

		ElementPtr * MessageReference::getElement(const char* name) const
		{
			if(strncmp(name, "securityData", 13) == 0)
				return this->_securities;

			else
				throw messageEx;
		}

		std::ostream& MessageReference::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "ReferenceDataResponse (choice) = {" << std::endl;
			this->_securities->print(stream, 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}


	}
}