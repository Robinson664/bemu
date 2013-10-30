//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementIntradayTickResponseError.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/ElementIntradayTickResponseError.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "Types/RandomDataGenerator.h"
#include "IntradayTickRequest/ElementIntradayTickString.h"
#include "IntradayTickRequest/ElementIntradayTickInt.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		ElementIntradayTickResponseError::ElementIntradayTickResponseError()
		{
			int code = RandomDataGenerator::RandomInt(99);
			std::string* sourceGibberish = RandomDataGenerator::RandomString(5);
			std::transform(sourceGibberish->begin(), sourceGibberish->end(), sourceGibberish->begin(), ::tolower);

			//source
			std::stringstream sourceValue;
			sourceValue << code << "::" << sourceGibberish << RandomDataGenerator::RandomInt(99);
			this->_source = new ElementIntradayTickString("source", sourceValue.str());
			delete sourceGibberish;
			sourceGibberish = 0;

			//code
			this->_code = new ElementIntradayTickInt("code", code);

			//category
			this->_category = new ElementIntradayTickString("category", "BAD_SEC");

			//message
			std::stringstream messageValue;
			messageValue << "Unknown/Invalid security [nid:" << code << "]";
			this->_message = new ElementIntradayTickString("message", messageValue.str());

			//sub-category
			this->_subCategory = new ElementIntradayTickString("subcategory", "INVALID_SECURITY");
		}

		ElementIntradayTickResponseError::~ElementIntradayTickResponseError()
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

		Name ElementIntradayTickResponseError::name() const
		{
			Name result("responseError");
			return result;
		}

		const char* ElementIntradayTickResponseError::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		int ElementIntradayTickResponseError::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		ElementPtr * ElementIntradayTickResponseError::getElement(const char* name) const
		{
			if(strncmp("source", name, 6) == 0)
				return this->_source;

			else if(strncmp("code", name, 4) == 0)
				return this->_code;

			else if(strncmp("category", name, 8) == 0)
				return this->_category;

			else if(strncmp("message", name, 7) == 0)
				return this->_message;

			else if(strncmp("subcategory", name, 11) == 0)
				return this->_subCategory;

			else
				throw elementPtrEx;
		}

		bool ElementIntradayTickResponseError::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(strncmp("source", name, 6) == 0) ||
				(strncmp("code", name, 4) == 0) ||
				(strncmp("category", name, 8) == 0) ||
				(strncmp("message", name, 7) == 0) ||
				(strncmp("subcategory", name, 11) == 0);
		}

		std::ostream& ElementIntradayTickResponseError::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);

			stream << tabs << "responseError = {" << std::endl;
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