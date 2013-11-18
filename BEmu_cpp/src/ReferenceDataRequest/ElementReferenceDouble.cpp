//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceDouble.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceDouble.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceDouble::ElementReferenceDouble(const std::string& name, double value)
		{
			this->_name = name;
			this->_value = value;
		}

		Name ElementReferenceDouble::name() const { return Name(this->_name.c_str()); }
		size_t ElementReferenceDouble::numValues() const { return 1; }
		size_t ElementReferenceDouble::numElements() const { return 0; }

		bool ElementReferenceDouble::isNull() const { return false; }
		bool ElementReferenceDouble::isArray() const { return false; }
		bool ElementReferenceDouble::isComplexType() const { return false; }

		double ElementReferenceDouble::getValueAsFloat64(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		int ElementReferenceDouble::getValueAsInt32(int index) const
		{
			if(index == 0)
				return (int)this->_value;
			else
				throw elementPtrEx;
		}

		long ElementReferenceDouble::getValueAsInt64(int index) const
		{
			if(index == 0)
				return (long)this->_value;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementReferenceDouble::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

	}
}