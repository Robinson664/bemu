//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketReason.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketReason.h"
#include "MarketDataRequest/ElementMarketInt.h"
#include "MarketDataRequest/ElementMarketString.h"

#include "Types/IndentType.h"
#include "Types/RandomDataGenerator.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketReason::ElementMarketReason(ReasonType::ReasonTypeEnum reasonType)
		{
			if(reasonType == ReasonType::badSecurity)
			{
				std::string source = RandomDataGenerator::RandomString(5);
				std::transform(source.begin(), source.end(), source.begin(), ::tolower);
				std::stringstream ssSource;
				ssSource << source << RandomDataGenerator::RandomInt(9) << '@' << RandomDataGenerator::RandomInt(99);
				this->_source = new ElementMarketString("source", ssSource.str());

				this->_errorCode = new ElementMarketInt("errorCode", RandomDataGenerator::RandomInt(99));

				this->_category = new ElementMarketString("category", "BAD_SEC");
                
				this->_description = new ElementMarketString("description", "Invalid security, rcode = -1");
			}
			else if(reasonType == ReasonType::badField)
			{
				std::string source = RandomDataGenerator::RandomString(7);
				std::transform(source.begin(), source.end(), source.begin(), ::tolower);
				std::stringstream ssSource;
				ssSource << source << '@' << RandomDataGenerator::RandomInt(999);
				this->_source = new ElementMarketString("source", ssSource.str());

				this->_errorCode = new ElementMarketInt("errorCode", RandomDataGenerator::RandomInt(99));

				this->_category = new ElementMarketString("category", "BAD_FLD");
				
                this->_description = new ElementMarketString("description", "Unknown Field");
			}
		}

		ElementMarketReason::~ElementMarketReason()
		{
			delete this->_source;
			this->_source = 0;
			
			delete this->_errorCode;
			this->_errorCode = 0;
			
			delete this->_category;
			this->_category = 0;
			
			delete this->_description;
			this->_description = 0;
		}

		Name ElementMarketReason::name() const
		{
			return Name("reason");
		}

		size_t ElementMarketReason::numValues() const
		{
			return 1;
		}

		size_t ElementMarketReason::numElements() const
		{
			return 4;
		}

		SchemaElementDefinition ElementMarketReason::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("ErrorInfo"));
			return result;
		}

		bool ElementMarketReason::isNull() const
		{
			return false;
		}

		bool ElementMarketReason::isArray() const
		{
			return false;
		}

		bool ElementMarketReason::isComplexType() const
		{
			return true;
		}

		ElementPtr * ElementMarketReason::getElement(const char* name) const
		{
			if(strncmp(name, "source", 7) == 0)
				return this->_source;
			
			else if(strncmp(name, "errorCode", 10) == 0)
				return this->_errorCode;
			
			else if(strncmp(name, "category", 9) == 0)
				return this->_category;
			
			else if(strncmp(name, "description", 12) == 0)
				return this->_description;

			else
				throw elementPtrEx;
		}

		bool ElementMarketReason::hasElement(const char* name, bool excludeNullElements) const
		{
			return 
				strncmp(name, "source", 7) == 0 ||
				strncmp(name, "errorCode", 10) == 0 ||
				strncmp(name, "category", 9) == 0 ||
				strncmp(name, "description", 12) == 0;
		}

		int ElementMarketReason::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		const char* ElementMarketReason::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		std::ostream& ElementMarketReason::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "reason = {" << std::endl;
			
			this->_source->print(stream, level + 1, spacesPerLevel);
			this->_errorCode->print(stream, level + 1, spacesPerLevel);
			this->_category->print(stream, level + 1, spacesPerLevel);
			this->_description->print(stream, level + 1, spacesPerLevel);

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}