//------------------------------------------------------------------------------
// <copyright project="BEmu" file="src/HistoricalDataRequest/MessageHistoric.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/MessageHistoric.h"
#include "HistoricalDataRequest/ElementHistoricSecurityData.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		MessageHistoric::MessageHistoric(
					const CorrelationId& corr, 
					const std::string& securityName, 
					const std::vector<std::string>& badFields, 
					std::map<Datetime, std::map<std::string, ObjectType>*> * fieldData, 
					int sequenceNumber) : MessagePtr(Name("HistoricalDataResponse"), corr)
		{
			this->_security = new ElementHistoricSecurityData(securityName, badFields, fieldData, sequenceNumber);
		}

		MessageHistoric::~MessageHistoric()
		{
			delete this->_security;
			this->_security = 0;
		}

		const ElementPtr * MessageHistoric::getElement(const char* name) const
		{
			if(strncmp(name, "securityData", 13) == 0)
				return this->_security;

			else
				throw messageEx;
		}

		bool MessageHistoric::hasElement(const char* name, bool excludeNullElements) const
		{
			return strncmp(name, "securityData", 13) == 0;
		}

		std::ostream& MessageHistoric::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "HistoricalDataResponse (choice) = {" << std::endl;
			this->_security->print(stream, 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}

	}
}