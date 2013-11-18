//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/ElementHistoricFieldExceptions.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricFieldExceptions.h"
#include "HistoricalDataRequest/ElementHistoricString.h"
#include "HistoricalDataRequest/ElementHistoricErrorInfo.h"

#include "BloombergTypes/Name.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricFieldExceptions::ElementHistoricFieldExceptions(const std::string& badField)
		{
            this->_fieldId = new ElementHistoricString("fieldId", badField);
            this->_errorInfo = new ElementHistoricErrorInfo();
		}

		ElementHistoricFieldExceptions::~ElementHistoricFieldExceptions()
		{
			delete this->_fieldId;
			this->_fieldId = 0;

			delete this->_errorInfo;
			this->_errorInfo = 0;
		}


		Name ElementHistoricFieldExceptions::name() const
		{
			Name result("fieldExceptions");
			return result;
		}

		size_t ElementHistoricFieldExceptions::numValues() const
		{
			return 1;
		}

		size_t ElementHistoricFieldExceptions::numElements() const
		{
			return 2;
		}

		
		bool ElementHistoricFieldExceptions::isNull() const
		{
			return false;
		}

		bool ElementHistoricFieldExceptions::isArray() const
		{
			return false;
		}

		bool ElementHistoricFieldExceptions::isComplexType() const
		{
			return true;
		}


		ElementPtr * ElementHistoricFieldExceptions::getElement(const char* name) const
		{
			if(strncmp(name, "errorInfo", 10) == 0)
				return this->_errorInfo;

			else if(strncmp(name, "fieldId", 8) == 0)
				return this->_fieldId;

			else
				throw elementPtrEx;
		}

		bool ElementHistoricFieldExceptions::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(strncmp(name, "errorInfo", 10) == 0) ||
				(strncmp(name, "fieldId", 8) == 0);
		}

		int ElementHistoricFieldExceptions::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		const char* ElementHistoricFieldExceptions::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}


		std::ostream& ElementHistoricFieldExceptions::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "fieldExceptions = {" << std::endl;
			
			this->_fieldId->print(stream, level + 1, spacesPerLevel);
			this->_errorInfo->print(stream, level + 1, spacesPerLevel);

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}