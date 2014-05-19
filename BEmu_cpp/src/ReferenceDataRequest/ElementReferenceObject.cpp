//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ReferenceElementObject.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ReferenceElementObject.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ReferenceElementObject::ReferenceElementObject(std::string name, ObjectType value)
		{
			this->_name = name;
			
			this->_value = value;

			const char * cstr = value.ToString().c_str();
			this->_cstr = ElementPtr::toCharPointer(cstr);
		}

		ReferenceElementObject::~ReferenceElementObject()
		{
			delete this->_cstr;
			this->_cstr = 0;
		}

		Name ReferenceElementObject::name() const { return Name(this->_name.c_str()); }
		size_t ReferenceElementObject::numValues() const { return 1; }
		size_t ReferenceElementObject::numElements() const { return 0; }

		bool ReferenceElementObject::isNull() const { return false; }
		bool ReferenceElementObject::isArray() const { return false; }
		bool ReferenceElementObject::isComplexType() const { return false; }

		void ReferenceElementObject::setName(const std::string& name)
		{
			this->_name = name;
		}

		void ReferenceElementObject::setValue(const ObjectType& value)
		{
			delete this->_cstr;
			this->_cstr = ElementPtr::toCharPointer(value.ToString());
			this->_value = value;
		}

		const char * ReferenceElementObject::getValueAsString(int index) const
		{
			return this->_cstr;
		}

		std::ostream& ReferenceElementObject::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value.ToString());
			return stream;
		}

	}
}