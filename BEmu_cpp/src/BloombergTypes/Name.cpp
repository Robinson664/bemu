//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/Name.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"

namespace BEmu
{
	Name::Name()
	{
	}

	Name::Name(const char* nameString)
	{
		this->_name = nameString;
	}

	Name::Name(const Name& original)
	{
		this->_name = original._name;
	}

	Name& Name::operator=(const Name &rhs)
	{
		if (this != &rhs)
		{
			this->_name = rhs._name;
		}
		return *this;
	}

	const char* Name::string() const
	{
		return this->_name.c_str();
	}

	bool Name::operator==(const char *rhs) const
	{
		return strcmp(this->string(), rhs) == 0;
	}

	bool Name::operator==(const Name rhs) const
	{
		return strcmp(this->string(), rhs.string()) == 0;
	}

	bool Name::operator!=(const char *rhs) const
	{
		return strcmp(this->string(), rhs) != 0;
	}

	bool Name::operator!=(const Name rhs) const
	{
		return strcmp(this->string(), rhs.string()) != 0;
	}



	std::ostream& operator<<(std::ostream& stream, const Name& name)
	{
		return stream << name.string();
	}

	bool operator==(const char *lhs, const Name& rhs)
	{
		return strcmp(lhs, rhs.string()) == 0;
	}

	bool operator!=(const char *lhs, const Name& rhs)
	{
		return strcmp(lhs, rhs.string()) != 0;
	}


}