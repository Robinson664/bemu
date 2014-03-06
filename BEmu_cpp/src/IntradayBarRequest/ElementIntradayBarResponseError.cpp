//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/ElementIntradayBarResponseError.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "IntradayBarRequest/ElementIntradayBarString.h"
#include "IntradayBarRequest/ElementIntradayBarInt.h"
#include "IntradayBarRequest/ElementIntradayBarResponseError.h"
#include "Types/RandomDataGenerator.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementIntradayBarResponseError::ElementIntradayBarResponseError(const std::string& security)
		{
			int code = RandomDataGenerator::RandomInt(99);
			std::string sourceGibberish = RandomDataGenerator::RandomString(5);
			std::transform(sourceGibberish.begin(), sourceGibberish.end(), sourceGibberish.begin(), ::tolower);

			//source
			std::stringstream sourceValue;
			sourceValue << code << "::" << sourceGibberish.substr(0, sourceGibberish.length() - 2) << RandomDataGenerator::RandomInt(99);
			this->_source = new ElementIntradayBarString("source", sourceValue.str());

			//code
			this->_code = new ElementIntradayBarInt("code", code);

			//category
			this->_category = new ElementIntradayBarString("category", "BAD_SEC");

			//message
			std::stringstream messageValue;
			messageValue << "Unknown/Invalid security [nid:" << code << "]";
			this->_message = new ElementIntradayBarString("message", messageValue.str());

			//sub-category
			this->_subCategory = new ElementIntradayBarString("subcategory", "INVALID_SECURITY");
		}

		ElementIntradayBarResponseError::~ElementIntradayBarResponseError()
		{
			delete this->_source;
			this->_source = 0;
			
			delete this->_category;
			this->_category = 0;
			
			delete this->_message;
			this->_message = 0;
			
			delete this->_subCategory;
			this->_subCategory = 0;
			
			delete this->_code;
			this->_code = 0;
		}

		Name ElementIntradayBarResponseError::name() const
		{
			Name result("responseError");
			return result;
		}

		size_t ElementIntradayBarResponseError::numValues() const
		{
			return 1;
		}

		size_t ElementIntradayBarResponseError::numElements() const
		{
			return 5;
		}

		SchemaElementDefinition ElementIntradayBarResponseError::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("ErrorInfo"));
			return result;
		}

		bool ElementIntradayBarResponseError::isArray() const
		{
			return false;
		}

		bool ElementIntradayBarResponseError::isComplexType() const
		{
			return false;
		}

		int ElementIntradayBarResponseError::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		const char* ElementIntradayBarResponseError::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		ElementPtr * ElementIntradayBarResponseError::getElement(const char* name) const
		{
			if(strncmp("source", name, 7) == 0)
				return this->_source;

			else if(strncmp("code", name, 5) == 0)
				return this->_code;

			else if(strncmp("category", name, 9) == 0)
				return this->_category;

			else if(strncmp("message", name, 8) == 0)
				return this->_message;

			else if(strncmp("subcategory", name, 12) == 0)
				return this->_subCategory;

			else
				throw elementPtrEx;
		}

		bool ElementIntradayBarResponseError::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(strncmp("source", name, 7) == 0) ||
				(strncmp("code", name, 5) == 0) ||
				(strncmp("category", name, 9) == 0) ||
				(strncmp("message", name, 8) == 0) ||
				(strncmp("subcategory", name, 12) == 0);
		}

		std::ostream& ElementIntradayBarResponseError::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

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