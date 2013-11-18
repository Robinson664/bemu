//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/ElementHistoricSecurityData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricSecurityData.h"
#include "HistoricalDataRequest/ElementHistoricFieldExceptionsArray.h"
#include "HistoricalDataRequest/ElementHistoricString.h"
#include "HistoricalDataRequest/ElementHistoricInt.h"
#include "HistoricalDataRequest/ElementHistoricSecurityError.h"
#include "HistoricalDataRequest/ElementHistoricFieldDataArray.h"

#include "Types/Rules.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricSecurityData::ElementHistoricSecurityData(
			const std::string& securityName, 
			const std::vector<std::string>& badFields, 
			//const std::map<Datetime, std::map<std::string, ObjectType>*>& fieldData, 
			const std::map<Datetime, std::map<std::string, ObjectType>*> * fieldData,
			int sequenceNumber)
		{
			this->_isSecurityError = Rules::IsSecurityError(securityName);
			
            //remove bad field names from the dictionary			
            if (badFields.size() == 0)
                this->_elmFieldExceptions = 0;
            else
                this->_elmFieldExceptions = new ElementHistoricFieldExceptionsArray(badFields);

			this->_elmSecurityName = new ElementHistoricString("security", securityName);

			this->_elmSequenceNumber = new ElementHistoricInt("sequenceNumber", sequenceNumber);

			if (this->_isSecurityError)
            {
                this->_elmSecError = new ElementHistoricSecurityError(securityName);
                this->_elmFieldDataArray = 0;
            }
            else
            {
                this->_elmSecError = 0;
                this->_elmFieldDataArray = new ElementHistoricFieldDataArray(fieldData);
            }
		}


		ElementHistoricSecurityData::~ElementHistoricSecurityData()
		{
			delete this->_elmFieldExceptions;
			this->_elmFieldExceptions = 0;

			delete this->_elmSecurityName;
			this->_elmSecurityName = 0;

			delete this->_elmSequenceNumber;
			this->_elmSequenceNumber = 0;

			delete this->_elmSecError;
			this->_elmSecError = 0;

			delete this->_elmFieldDataArray;
			this->_elmFieldDataArray = 0;
		}


		Name ElementHistoricSecurityData::name() const
		{
			Name result("securityData");
			return result;
		}

		size_t ElementHistoricSecurityData::numValues() const
		{
			return 1;
		}

		size_t ElementHistoricSecurityData::numElements() const
		{
			return 3 + (this->_elmFieldExceptions == 0 ? 0 : 1);
		}

		
		bool ElementHistoricSecurityData::isNull() const
		{
			return false;
		}

		bool ElementHistoricSecurityData::isArray() const
		{
			return false;
		}

		bool ElementHistoricSecurityData::isComplexType() const
		{
			return true;
		}


		ElementPtr * ElementHistoricSecurityData::getElement(const char* name) const
		{
			if(strncmp(name, "fieldData", 10) == 0)
			{
				if(!this->_isSecurityError)
					return this->_elmFieldDataArray;
			}

			else if(strncmp(name, "security", 9) == 0)
				return this->_elmSecurityName;

			else if(strncmp(name, "sequenceNumber", 9) == 0)
				return this->_elmSequenceNumber;

			else if(strncmp(name, "fieldExceptions", 16) == 0)
			{
				if(this->_elmFieldExceptions != 0)
					return this->_elmFieldExceptions;
			}

			else if(strncmp(name, "securityError", 14) == 0)
			{
				if(this->_isSecurityError)
					return this->_elmSecError;
			}

			throw elementPtrEx;
		}

		bool ElementHistoricSecurityData::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				( strncmp(name, "fieldData", 10) == 0 && !this->_isSecurityError ) ||
				( strncmp(name, "security", 9) == 0) ||
				( strncmp(name, "sequenceNumber", 9) == 0) ||
				( strncmp(name, "fieldExceptions", 16) == 0 && this->_elmFieldExceptions != 0) ||
				( strncmp(name, "securityError", 14) == 0 && this->_isSecurityError );
		}


		int ElementHistoricSecurityData::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		const char* ElementHistoricSecurityData::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}


		std::ostream& ElementHistoricSecurityData::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));
			stream << tabs << "securityData = {" << std::endl;
			
			this->_elmSecurityName->print(stream, level + 1, spacesPerLevel);
			this->_elmSequenceNumber->print(stream, level + 1, spacesPerLevel);

			if(this->_elmFieldExceptions != 0)
				this->_elmFieldExceptions->print(stream, level + 1, spacesPerLevel);

			if(this->_isSecurityError)
				this->_elmSecError->print(stream, level + 1, spacesPerLevel);
			else
				this->_elmFieldDataArray->print(stream, level + 1, spacesPerLevel);

			stream << tabs << '}' << std::endl;

            return stream;
		}

	}
}