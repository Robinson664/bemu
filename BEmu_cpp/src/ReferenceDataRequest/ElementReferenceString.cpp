//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceString.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceString.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceString::ElementReferenceString(const std::string& name, const std::string& value)
		{
			this->_name = name;
			this->_value = value;
		}

		Name ElementReferenceString::name() const { return Name(this->_name.c_str()); }
		size_t ElementReferenceString::numValues() const { return 1; }
		size_t ElementReferenceString::numElements() const { return 0; }

		bool ElementReferenceString::isNull() const { return false; }
		bool ElementReferenceString::isArray() const { return false; }
		bool ElementReferenceString::isComplexType() const { return false; }

		void ElementReferenceString::setName(const std::string& name)
		{
			this->_name = name;
		}

		void ElementReferenceString::setValue(const std::string& value)
		{
			this->_value = value;
		}

		const char * ElementReferenceString::getValueAsString(int index) const
		{
			if(index == 0)
				return ElementPtr::toCharPointer(this->_value);
			else
				throw elementPtrEx;
		}

		std::ostream& ElementReferenceString::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

	}
}