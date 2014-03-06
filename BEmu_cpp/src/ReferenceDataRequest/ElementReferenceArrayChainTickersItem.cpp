//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceArrayChainTickersItem.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceArrayChainTickersItem.h"
#include "ReferenceDataRequest/ElementReferenceString.h"
#include "BloombergTypes/Name.h"
#include "Types/IndentType.h"
#include "Types/DisplayFormats.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceArrayChainTickersItem::ElementReferenceArrayChainTickersItem(std::string ticker, Datetime dtExp, ReferenceDataRequest::OptionalityEnum::EnumType optionality, int strike)
		{
			std::stringstream ss;
			ss << ticker << " US ";
			ss << DisplayFormats::ToMMddYYWithSlashes(dtExp) << ' ';

			char cp = (optionality == ReferenceDataRequest::OptionalityEnum::call) ? 'C' : 'P';
			ss << cp;

			ss << strike;
			
			this->_element = new ElementReferenceString("Ticker", ss.str());
		}

		ElementReferenceArrayChainTickersItem::~ElementReferenceArrayChainTickersItem()
		{
			delete this->_element;
			this->_element = 0;
		}		

		Name ElementReferenceArrayChainTickersItem::name() const { return Name("Ticker"); }
		size_t ElementReferenceArrayChainTickersItem::numValues() const { return 0; }
		size_t ElementReferenceArrayChainTickersItem::numElements() const { return 1; }

		SchemaElementDefinition ElementReferenceArrayChainTickersItem::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("CHAIN_TICKERS"));
			return result;
		}

		bool ElementReferenceArrayChainTickersItem::isNull() const { return false; }
		bool ElementReferenceArrayChainTickersItem::isArray() const { return false; }
		bool ElementReferenceArrayChainTickersItem::isComplexType() const { return false; }

		const char* ElementReferenceArrayChainTickersItem::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		ElementPtr * ElementReferenceArrayChainTickersItem::getElement(const char* name) const
		{
			if(strncmp(name, "Ticker", 7) == 0)
				return this->_element;

			else
				throw elementPtrEx;
		}

		std::ostream& ElementReferenceArrayChainTickersItem::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "CHAIN_TICKERS = {" << std::endl;

			this->_element->print(stream, level + 1, spacesPerLevel);

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}