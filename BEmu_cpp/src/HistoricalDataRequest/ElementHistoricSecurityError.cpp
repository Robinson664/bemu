//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/ElementHistoricSecurityError.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricSecurityError.h"
#include "HistoricalDataRequest/ElementHistoricString.h"
#include "HistoricalDataRequest/ElementHistoricInt.h"

#include "Types/RandomDataGenerator.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricSecurityError::ElementHistoricSecurityError(const std::string& security)
		{
			int nid = RandomDataGenerator::RandomInt(99);

			std::string sourceGibberish = RandomDataGenerator::RandomString(5);
			std::transform(sourceGibberish.begin(), sourceGibberish.end(), sourceGibberish.begin(), ::tolower);

			//source
			std::stringstream sourceValue;
			sourceValue << nid << "::" << sourceGibberish.substr(0, sourceGibberish.length() - 2) << RandomDataGenerator::RandomInt(99);
			this->_source = new ElementHistoricString("source", sourceValue.str());

			//code
			this->_code = new ElementHistoricInt("code", RandomDataGenerator::RandomInt(99));

			//category
			this->_category = new ElementHistoricString("category", "BAD_SEC");

			//message
			std::stringstream messageValue;
			messageValue << "Unknown/Invalid security [nid:" << nid << "]";
			this->_message = new ElementHistoricString("message", messageValue.str());

			//sub-category
			this->_subCategory = new ElementHistoricString("subcategory", "INVALID_SECURITY");
		}

		ElementHistoricSecurityError::~ElementHistoricSecurityError()
		{
			delete this->_source;
			this->_source = 0;
			
			delete this->_code;
			this->_code = 0;
			
			delete this->_category;
			this->_category = 0;
			
			delete this->_message;
			this->_message = 0;
			
			delete this->_subCategory;
			this->_subCategory = 0;
		}


		Name ElementHistoricSecurityError::name() const
		{
			Name result("securityError");
			return result;
		}

		size_t ElementHistoricSecurityError::numValues() const
		{
			return 1;
		}

		size_t ElementHistoricSecurityError::numElements() const
		{
			return 5;
		}

		
		bool ElementHistoricSecurityError::isNull() const
		{
			return false;
		}

		bool ElementHistoricSecurityError::isArray() const
		{
			return false;
		}

		bool ElementHistoricSecurityError::isComplexType() const
		{
			return true;
		}


		ElementPtr * ElementHistoricSecurityError::getElement(const char* name) const
		{
			if(strncmp(name, "source", 7) == 0)
				return this->_source;

			else if(strncmp(name, "code", 5) == 0)
				return this->_code;

			else if(strncmp(name, "category", 9) == 0)
				return this->_category;

			else if(strncmp(name, "message", 8) == 0)
				return this->_message;

			else if(strncmp(name, "subcategory", 12) == 0)
				return this->_subCategory;

			else
				throw elementPtrEx;
		}

		bool ElementHistoricSecurityError::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(strncmp(name, "source", 7) == 0) ||
				(strncmp(name, "code", 5) == 0) ||
				(strncmp(name, "category", 9) == 0) ||
				(strncmp(name, "message", 8) == 0) ||
				(strncmp(name, "subcategory", 12) == 0);
		}


		int ElementHistoricSecurityError::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		const char* ElementHistoricSecurityError::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}


		std::ostream& ElementHistoricSecurityError::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "fieldData = {" << std::endl;
			
			this->_source->print(stream, level, spacesPerLevel);
			this->_code->print(stream, level, spacesPerLevel);
			this->_category->print(stream, level, spacesPerLevel);
			this->_message->print(stream, level, spacesPerLevel);
			this->_subCategory->print(stream, level, spacesPerLevel);

			stream << tabs << '}' << std::endl;
			
			return stream;
		}

	}
}