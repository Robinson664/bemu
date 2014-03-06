//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceFieldExceptionsArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceFieldExceptionsArray.h"
#include "ReferenceDataRequest/ElementReferenceFieldExceptions.h"
#include "BloombergTypes/Name.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceFieldExceptionsArray::ElementReferenceFieldExceptionsArray(const std::vector<std::string>& badFields)
		{
			for(std::vector<std::string>::const_iterator iter = badFields.begin(); iter != badFields.end(); ++iter)
			{
				std::string str = *iter;
				ElementReferenceFieldExceptions * elm = new	ElementReferenceFieldExceptions(str);
				this->_exceptions.push_back(elm);
			}
		}

		ElementReferenceFieldExceptionsArray::~ElementReferenceFieldExceptionsArray()
		{
			for(std::vector<ElementReferenceFieldExceptions*>::const_iterator iter = this->_exceptions.begin(); iter != this->_exceptions.end(); ++iter)
			{
				ElementReferenceFieldExceptions * elm = *iter;
				delete elm;
			}
		}

		Name ElementReferenceFieldExceptionsArray::name() const { return Name("fieldExceptions"); }
		size_t ElementReferenceFieldExceptionsArray::numValues() const { return this->_exceptions.size(); }
		size_t ElementReferenceFieldExceptionsArray::numElements() const { return 0; }

		SchemaElementDefinition ElementReferenceFieldExceptionsArray::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("FieldException"));
			return result;
		}

		bool ElementReferenceFieldExceptionsArray::isNull() const { return false; }
		bool ElementReferenceFieldExceptionsArray::isArray() const { return true; }
		bool ElementReferenceFieldExceptionsArray::isComplexType() const { return false; }

		ElementPtr * ElementReferenceFieldExceptionsArray::getValueAsElement(int index) const
		{
			return this->_exceptions[index];
		}

		std::ostream& ElementReferenceFieldExceptionsArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level + 1, spacesPerLevel));

			stream << tabs << "fieldExceptions[] = {" << std::endl;
			
			for(std::vector<ElementReferenceFieldExceptions*>::const_iterator iter = this->_exceptions.begin(); iter != this->_exceptions.end(); ++iter)
			{
				ElementReferenceFieldExceptions * elm = *iter;
				elm->print(stream, level + 1, spacesPerLevel);
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}