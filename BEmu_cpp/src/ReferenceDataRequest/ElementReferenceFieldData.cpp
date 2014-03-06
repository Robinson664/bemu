//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceFieldData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceFieldData.h"
#include "Types/ObjectType.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

#include "ReferenceDataRequest/ElementReferenceDouble.h"
#include "ReferenceDataRequest/ElementReferenceInt.h"
#include "ReferenceDataRequest/ElementReferenceDateTime.h"
#include "ReferenceDataRequest/ElementReferenceString.h"
#include "ReferenceDataRequest/ElementReferenceArrayChainTickers.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceFieldData::ElementReferenceFieldData(const std::map<std::string, ObjectType>& values)
		{
			for(std::map<std::string, ObjectType>::const_iterator iter = values.begin(); iter != values.end(); ++iter)
			{
				std::string name = iter->first;
				ObjectType value = iter->second;

				ElementPtr * elm = 0;

				switch(value.GetType())
				{
					case ObjectType::eDouble:
						elm = new ElementReferenceDouble(name, value.ValueAsDouble());
						break;
						
					case ObjectType::eInt:
						elm = new ElementReferenceInt(name, value.ValueAsInt());
						break;
						
					case ObjectType::eDatetime:
						elm = new ElementReferenceDateTime(name, value.ValueAsDatetime());
						break;
						
					case ObjectType::eString:
						elm = new ElementReferenceString(name, value.ValueAsString());
						break;

					case ObjectType::eChainTickers:
						elm = value.ValueAsChainTickers();
						break;
				}

				if(elm != 0)
					this->_fields.push_back(elm);

			}
		}

		ElementReferenceFieldData::~ElementReferenceFieldData()
		{
			for(std::vector<ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = *iter;
				delete elm;
			}
		}

		Name ElementReferenceFieldData::name() const { return Name("fieldData"); }
		size_t ElementReferenceFieldData::numValues() const { return 1; }
		size_t ElementReferenceFieldData::numElements() const { return this->_fields.size(); }

		SchemaElementDefinition ElementReferenceFieldData::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("ReferenceFieldData"));
			return result;
		}

		ElementPtr * ElementReferenceFieldData::getElement(int position) const
		{
			return this->_fields.at(position);
		}

		ElementPtr * ElementReferenceFieldData::getElement(const char* name) const
		{
			for(std::vector<ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = *iter;

				if(elm->name() == name)
					return elm;
			}
			throw elementPtrEx;
		}

		bool ElementReferenceFieldData::hasElement(const char* name, bool excludeNullElements) const
		{
			for(std::vector<ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = *iter;

				if(elm->name() == name)
					return true;
			}
			return false;
		}

		double ElementReferenceFieldData::getElementAsFloat64(const char* name) const
		{
			return this->getElement(name)->getValueAsFloat64(0);
		}

		int ElementReferenceFieldData::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		long ElementReferenceFieldData::getElementAsInt64(const char* name) const
		{
			return this->getElement(name)->getValueAsInt64(0);
		}

		const char* ElementReferenceFieldData::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		std::ostream& ElementReferenceFieldData::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "fieldData = {" << std::endl;
			
			for(std::vector<ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = *iter;
				elm->print(stream, level + 1, spacesPerLevel);
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}