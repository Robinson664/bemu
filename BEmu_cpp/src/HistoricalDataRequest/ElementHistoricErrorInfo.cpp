//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/ElementHistoricErrorInfo.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "Types/RandomDataGenerator.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/SchemaElementDefinition.h"
#include "HistoricalDataRequest/ElementHistoricErrorInfo.h"
#include "HistoricalDataRequest/ElementHistoricString.h"
#include "HistoricalDataRequest/ElementHistoricInt.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricErrorInfo::ElementHistoricErrorInfo()
		{
			std::string sourceGibberish = RandomDataGenerator::RandomString(5);
			std::transform(sourceGibberish.begin(), sourceGibberish.end(), sourceGibberish.begin(), ::tolower);

			std::stringstream ssSource;
			ssSource << RandomDataGenerator::RandomInt(999) << "::" << sourceGibberish.substr(0, sourceGibberish.length() - 2) << RandomDataGenerator::RandomInt(99);
			this->_source = new ElementHistoricString("source", ssSource.str());

			this->_code = new ElementHistoricInt("code", RandomDataGenerator::RandomInt(99));

			this->_category = new ElementHistoricString("category", "BAD_FLD");

            this->_message = new ElementHistoricString("message", "Invalid field");

            this->_subCategory = new ElementHistoricString("subcategory", "NOT_APPLICABLE_TO_HIST_DATA");
		}

		ElementHistoricErrorInfo::~ElementHistoricErrorInfo()
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

		Name ElementHistoricErrorInfo::name() const
		{
			Name result("errorInfo");
			return result;
		}

		size_t ElementHistoricErrorInfo::numValues() const
		{
			return 1;
		}

		size_t ElementHistoricErrorInfo::numElements() const
		{
			return 5;
		}

		SchemaElementDefinition ElementHistoricErrorInfo::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("ErrorInfo"));
			return result;
		}

		bool ElementHistoricErrorInfo::isNull() const
		{
			return false;
		}

		bool ElementHistoricErrorInfo::isArray() const
		{
			return false;
		}

		bool ElementHistoricErrorInfo::isComplexType() const
		{
			return true;
		}

				
		ElementPtr * ElementHistoricErrorInfo::getElement(const char* name) const
		{
			if(strncmp(name, "category", 9) == 0)
				return this->_category;

			else if(strncmp(name, "code", 5) == 0)
				return this->_code;

			else if(strncmp(name, "message", 8) == 0)
				return this->_message;

			else if(strncmp(name, "source", 7) == 0)
				return this->_source;

			else if(strncmp(name, "subcategory", 12) == 0)
				return this->_subCategory;

			else
				throw elementPtrEx;
		}

		bool ElementHistoricErrorInfo::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(strncmp(name, "category", 9) == 0) ||
				(strncmp(name, "code", 5) == 0) ||
				(strncmp(name, "message", 8) == 0) ||
				(strncmp(name, "source", 7) == 0) ||
				(strncmp(name, "subcategory", 12) == 0);
		}


		int ElementHistoricErrorInfo::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		const char* ElementHistoricErrorInfo::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		std::ostream& ElementHistoricErrorInfo::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);

			stream << tabs << "errorInfo = {" << std::endl;
			
			this->_source->print(stream, level + 1, spacesPerLevel);
			this->_code->print(stream, level + 1, spacesPerLevel);
			this->_category->print(stream, level + 1, spacesPerLevel);
			this->_message->print(stream, level + 1, spacesPerLevel);
			this->_subCategory->print(stream, level + 1, spacesPerLevel);

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}