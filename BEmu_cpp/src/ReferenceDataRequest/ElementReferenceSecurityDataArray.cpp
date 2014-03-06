//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceSecurityDataArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceSecurityDataArray.h"
#include "ReferenceDataRequest/ElementReferenceSecurityData.h"
#include "BloombergTypes/Name.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceSecurityDataArray::ElementReferenceSecurityDataArray(const std::map<std::string, std::map<std::string, ObjectType>*>& securities)
		{
			for(std::map<std::string, std::map<std::string, ObjectType>*>::const_iterator iter = securities.begin(); iter != securities.end(); ++iter)
			{
				std::string str = iter->first;
				std::map<std::string, ObjectType> * mm = iter->second;

				ElementReferenceSecurityData * elm = new ElementReferenceSecurityData(str, mm, this->_securities.size());
				this->_securities.push_back(elm);
			}
		}

		ElementReferenceSecurityDataArray::ElementReferenceSecurityDataArray(const ElementReferenceSecurityDataArray& arg)
		{
			this->_securities = std::vector<ElementPtr*>(arg._securities);
		}

		ElementReferenceSecurityDataArray::~ElementReferenceSecurityDataArray()
		{
			for(std::vector<ElementPtr*>::const_iterator iter = this->_securities.begin(); iter != this->_securities.end(); ++iter)
			{
				ElementPtr * elm = *iter;
				delete elm;
			}
		}

		Name ElementReferenceSecurityDataArray::name() const { return Name("securityData"); }
		size_t ElementReferenceSecurityDataArray::numValues() const { return this->_securities.size(); }
		size_t ElementReferenceSecurityDataArray::numElements() const { return 0; }

		SchemaElementDefinition ElementReferenceSecurityDataArray::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("ReferenceSecurityData"));
			return result;
		}

		ElementPtr * ElementReferenceSecurityDataArray::getValueAsElement(int index) const
		{
			return this->_securities[index];
		}

		bool ElementReferenceSecurityDataArray::hasElement(const char* name, bool excludeNullElements) const
		{
			for(std::vector<ElementPtr*>::const_iterator iter = this->_securities.begin(); iter != this->_securities.end(); ++iter)
			{
				ElementPtr * elm = *iter;

				if(elm->name() == name)
					return true;
			}
			return false;
		}

		ElementPtr * ElementReferenceSecurityDataArray::getElement(const char* name) const
		{
			for(std::vector<ElementPtr*>::const_iterator iter = this->_securities.begin(); iter != this->_securities.end(); ++iter)
			{
				ElementPtr * elm = *iter;

				if(elm->name() == name)
					return elm;
			}
			throw elementPtrEx;
		}

		std::ostream& ElementReferenceSecurityDataArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "securityData[] = {" << std::endl;
			
			for(std::vector<ElementPtr*>::const_iterator iter = this->_securities.begin(); iter != this->_securities.end(); ++iter)
			{
				ElementPtr * elm = *iter;
				elm->print(stream, level + 1, spacesPerLevel);
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}



	}
}