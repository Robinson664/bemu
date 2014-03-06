//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceDateTime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceDateTime.h"
#include "BloombergTypes/Name.h"
#include "Types/DisplayFormats.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceDateTime::ElementReferenceDateTime(const std::string& name, const Datetime& value)
		{
			this->_name = name;
			this->_value = value;
		}

		Name ElementReferenceDateTime::name() const { return Name(this->_name.c_str()); }
		size_t ElementReferenceDateTime::numValues() const { return 1; }
		size_t ElementReferenceDateTime::numElements() const { return 0; }

		bool ElementReferenceDateTime::isNull() const { return false; }
		bool ElementReferenceDateTime::isArray() const { return false; }
		bool ElementReferenceDateTime::isComplexType() const { return false; }

		Datetime ElementReferenceDateTime::getValueAsDatetime(int index) const
		{
			if(index == 0)
				return this->_value;

			else
				throw elementPtrEx;
		}

		std::ostream& ElementReferenceDateTime::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, DisplayFormats::FormatDatetimeZone(this->_value));
			return stream;
		}

	}
}