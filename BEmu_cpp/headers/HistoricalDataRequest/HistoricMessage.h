//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/HistoricalDataRequest/HistoricMessage.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/MessagePtr.h"
#include <vector>
#include <map>

namespace BEmu
{
	class ObjectType;

	namespace HistoricalDataRequest
	{
		class HistoricElementSecurityData;

		class HistoricMessage : public MessagePtr
		{
			private:
				HistoricElementSecurityData * _security;

			public:
				HistoricMessage(
					const CorrelationId& corr, 
					const std::string& securityName, 
					const std::vector<std::string>& badFields, 
					std::map<Datetime, std::map<std::string, ObjectType>*> * fieldData, 
					int sequenceNumber);

				~HistoricMessage();

				HistoricElementSecurityData * getSecurity() const;
				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;
				virtual ElementPtr * getElement(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}