//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceErrorInfo.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceErrorInfo.h"
#include "Types/RandomDataGenerator.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

#include "ReferenceDataRequest/ElementReferenceString.h"
#include "ReferenceDataRequest/ElementReferenceInt.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceErrorInfo::ElementReferenceErrorInfo()
		{
			std::string sourceGibberish = RandomDataGenerator::RandomString(5);
			std::transform(sourceGibberish.begin(), sourceGibberish.end(), sourceGibberish.begin(), ::tolower);

			std::stringstream ssSource;
			ssSource << RandomDataGenerator::RandomInt(99) << "::" << sourceGibberish.substr(0, sourceGibberish.length() - 2) << RandomDataGenerator::RandomInt(99);
			this->_source = new ElementReferenceString("source", ssSource.str());

			this->_code = new ElementReferenceInt("code", RandomDataGenerator::RandomInt(99));

			this->_category = new ElementReferenceString("category", "BAD_FLD");

            this->_message = new ElementReferenceString("message", "Field not valid");

            this->_subCategory = new ElementReferenceString("subcategory", "INVALID_FIELD");
		}

		ElementReferenceErrorInfo::~ElementReferenceErrorInfo()
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

		Name ElementReferenceErrorInfo::name() const { return Name("errorInfo"); }
		size_t ElementReferenceErrorInfo::numValues() const { return 1; }
		size_t ElementReferenceErrorInfo::numElements() const { return 5; }

		bool ElementReferenceErrorInfo::isNull() const { return false; }
		bool ElementReferenceErrorInfo::isArray() const { return false; }
		bool ElementReferenceErrorInfo::isComplexType() const { return true; }

		const char* ElementReferenceErrorInfo::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		int ElementReferenceErrorInfo::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		ElementPtr * ElementReferenceErrorInfo::getElement(const char* name) const
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

		bool ElementReferenceErrorInfo::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(strncmp(name, "category", 9) == 0) ||
				(strncmp(name, "code", 5) == 0) ||
				(strncmp(name, "message", 8) == 0) ||
				(strncmp(name, "source", 7) == 0) ||
				(strncmp(name, "subcategory", 12) == 0);
		}

		std::ostream& ElementReferenceErrorInfo::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

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