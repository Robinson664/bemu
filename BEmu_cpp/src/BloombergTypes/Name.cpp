//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/Name.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	Name::Name()
	{
	}

	Name::Name(const char* nameString)
	{
		this->_name = nameString;
		this->_cname = nameString;
		this->_length = strlen(nameString);
	}

	Name::Name(const Name& original)
	{
		this->_name = original._name;
		this->_cname = this->_name.c_str();
		this->_length = original._length;
	}

	Name& Name::operator=(const Name &rhs)
	{
		if (this != &rhs)
		{
			this->_name = rhs._name;
			this->_cname = this->_name.c_str();
			this->_length = rhs._length;
		}
		return *this;
	}

	const char* Name::string() const
	{
		return this->_cname;
	}

	bool Name::operator==(const char *rhs) const
	{
		return strncmp(this->_cname, rhs, this->_length + 1) == 0;
	}

	bool Name::operator==(const Name rhs) const
	{
		return strncmp(this->_cname, rhs._cname, this->_length + 1) == 0;
	}

	bool Name::operator!=(const char *rhs) const
	{
		return !(*this == rhs);
	}

	bool Name::operator!=(const Name rhs) const
	{
		return !(*this == rhs);
	}



	std::ostream& operator<<(std::ostream& stream, const Name& name)
	{
		return stream << name.string();
	}

	bool operator==(const char *lhs, const Name& rhs)
	{
		return rhs == lhs;
	}

	bool operator!=(const char *lhs, const Name& rhs)
	{
		return rhs == lhs;
	}


}