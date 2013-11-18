//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceObject.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceObject.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceObject::ElementReferenceObject(std::string name, ObjectType value)
		{
			this->_name = name;
			
			this->_value = value;

			const char * cstr = value.ToString().c_str();
			this->_cstr = ElementPtr::toCharPointer(cstr);
		}

		ElementReferenceObject::~ElementReferenceObject()
		{
			delete this->_cstr;
			this->_cstr = 0;
		}

		Name ElementReferenceObject::name() const { return Name(this->_name.c_str()); }
		size_t ElementReferenceObject::numValues() const { return 1; }
		size_t ElementReferenceObject::numElements() const { return 0; }

		bool ElementReferenceObject::isNull() const { return false; }
		bool ElementReferenceObject::isArray() const { return false; }
		bool ElementReferenceObject::isComplexType() const { return false; }

		void ElementReferenceObject::setName(const std::string& name)
		{
			this->_name = name;
		}

		void ElementReferenceObject::setValue(const ObjectType& value)
		{
			delete this->_cstr;
			this->_cstr = ElementPtr::toCharPointer(value.ToString());
			this->_value = value;
		}

		const char * ElementReferenceObject::getValueAsString(int index) const
		{
			return this->_cstr;
		}

		std::ostream& ElementReferenceObject::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value.ToString());
			return stream;
		}

	}
}