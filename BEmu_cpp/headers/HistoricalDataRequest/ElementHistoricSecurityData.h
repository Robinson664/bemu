//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/HistoricalDataRequest/ElementHistoricSecurityData.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"
#include <vector>
#include <map>

namespace BEmu
{
	class ObjectType;

	namespace HistoricalDataRequest
	{
		class ElementHistoricString;
		class ElementHistoricFieldDataArray;
		class ElementHistoricInt;
		class ElementHistoricFieldExceptionsArray;
		class ElementHistoricSecurityError;

		class ElementHistoricSecurityData : public ElementPtr
		{
			private:
				ElementHistoricString * _elmSecurityName;
				ElementHistoricFieldDataArray * _elmFieldDataArray;
				ElementHistoricInt * _elmSequenceNumber;
				ElementHistoricFieldExceptionsArray * _elmFieldExceptions;
				ElementHistoricSecurityError * _elmSecError;
				bool _isSecurityError;

			public:
				ElementHistoricSecurityData(
					const std::string& securityName, 
					const std::vector<std::string>& badFields, 
					const std::map<Datetime, std::map<std::string, ObjectType>*> * fieldData, 
					int sequenceNumber);

				~ElementHistoricSecurityData();

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
		
				bool isNull() const;
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				virtual ElementPtr * getElement(const char* name) const;
				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;

				virtual int getElementAsInt32(const char* name) const;
				virtual const char* getElementAsString(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}