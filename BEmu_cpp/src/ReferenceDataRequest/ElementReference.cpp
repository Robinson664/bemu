//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReference.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReference.h"
#include "ReferenceDataRequest/MessageReference.h"
#include "ReferenceDataRequest/ElementReferenceSecurityDataArray.h"
#include "BloombergTypes/Name.h"



namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReference::ElementReference(const MessageReference& arg)
		{
			ElementReferenceSecurityDataArray * elm = (ElementReferenceSecurityDataArray*)arg.firstElement();
			this->_securities = new ElementReferenceSecurityDataArray(*elm);
		}

		Name ElementReference::name() const { return Name("securityData"); }
		size_t ElementReference::numValues() const { return 1; }
		size_t ElementReference::numElements() const { return 1; }

		bool ElementReference::isNull() const { return false; }
		bool ElementReference::isArray() const { return false; }
		bool ElementReference::isComplexType() const { return true; }

		ElementPtr * ElementReference::getElement(const char* name) const
		{
			if(strncmp(name, "securityData", 13) == 0)
				return this->_securities;

			else
				throw elementPtrEx;
		}

		std::ostream& ElementReference::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "ReferenceDataResponse (choice) = {" << std::endl;
			this->_securities->print(stream, level + 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}

	}
}