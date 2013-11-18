//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceInt.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceInt::ElementReferenceInt(const std::string& name, int value)
		{
			this->_name = name;
			this->_value = value;
		}

		Name ElementReferenceInt::name() const { return Name(this->_name.c_str()); }
		size_t ElementReferenceInt::numValues() const { return 1; }
		size_t ElementReferenceInt::numElements() const { return 0; }

		bool ElementReferenceInt::isNull() const { return false; }
		bool ElementReferenceInt::isArray() const { return false; }
		bool ElementReferenceInt::isComplexType() const { return false; }

		int ElementReferenceInt::getValueAsInt32(int index) const
		{
			return this->_value;
		}

		long ElementReferenceInt::getValueAsInt64(int index) const
		{
			return (long)this->_value;
		}

		std::ostream& ElementReferenceInt::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

	}
}