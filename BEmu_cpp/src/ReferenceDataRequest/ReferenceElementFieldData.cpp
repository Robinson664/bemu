//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ReferenceElementFieldData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ReferenceElementFieldData.h"
#include "Types/ObjectType.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

#include "ReferenceDataRequest/ReferenceElementDouble.h"
#include "ReferenceDataRequest/ReferenceElementInt.h"
#include "ReferenceDataRequest/ReferenceElementDateTime.h"
#include "ReferenceDataRequest/ReferenceElementString.h"
#include "ReferenceDataRequest/ReferenceElementArrayChainTickers.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ReferenceElementFieldData::ReferenceElementFieldData(const std::map<std::string, ObjectType>& values)
		{
			for(std::map<std::string, ObjectType>::const_iterator iter = values.begin(); iter != values.end(); ++iter)
			{
				std::string name = iter->first;
				ObjectType value = iter->second;

				ElementPtr * elm = 0;

				switch(value.GetType())
				{
					case ObjectType::eDouble:
						elm = new ReferenceElementDouble(name, value.ValueAsDouble());
						break;
						
					case ObjectType::eInt:
						elm = new ReferenceElementInt(name, value.ValueAsInt());
						break;
						
					case ObjectType::eDatetime:
						elm = new ReferenceElementDateTime(name, value.ValueAsDatetime());
						break;
						
					case ObjectType::eString:
						elm = new ReferenceElementString(name, value.ValueAsString());
						break;

					case ObjectType::eChainTickers:
						elm = value.ValueAsChainTickers();
						break;
				}

				if(elm != 0)
					this->_fields.push_back(elm);

			}
		}

		ReferenceElementFieldData::~ReferenceElementFieldData()
		{
			for(std::vector<ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = *iter;
				delete elm;
			}
		}

		Name ReferenceElementFieldData::name() const { return Name("fieldData"); }
		size_t ReferenceElementFieldData::numValues() const { return 1; }
		size_t ReferenceElementFieldData::numElements() const { return this->_fields.size(); }

		SchemaElementDefinition ReferenceElementFieldData::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("ReferenceFieldData"));
			return result;
		}

		ElementPtr * ReferenceElementFieldData::getElement(int position) const
		{
			return this->_fields.at(position);
		}

		ElementPtr * ReferenceElementFieldData::getElement(const char* name) const
		{
			for(std::vector<ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = *iter;

				if(elm->name() == name)
					return elm;
			}
			throw elementPtrEx;
		}

		bool ReferenceElementFieldData::hasElement(const char* name, bool excludeNullElements) const
		{
			for(std::vector<ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = *iter;

				if(elm->name() == name)
					return true;
			}
			return false;
		}

		double ReferenceElementFieldData::getElementAsFloat64(const char* name) const
		{
			return this->getElement(name)->getValueAsFloat64(0);
		}

		int ReferenceElementFieldData::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		long ReferenceElementFieldData::getElementAsInt64(const char* name) const
		{
			return this->getElement(name)->getValueAsInt64(0);
		}

		const char* ReferenceElementFieldData::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		std::ostream& ReferenceElementFieldData::print(std::ostream& stream, int level, int spacesPerLevel) const
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