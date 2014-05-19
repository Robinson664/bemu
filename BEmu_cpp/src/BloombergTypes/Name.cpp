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
	std::map<std::string, Name> Name::_globalNameTable;

	Name::Name()
	{
		this->_isNull = true;
	}

	Name::Name(const char* nameString)
	{
		this->_isNull = false;
		this->_name = nameString;
		this->_cname = nameString;
		this->_length = strlen(nameString);

		if(Name::_globalNameTable.find(this->_name) == Name::_globalNameTable.end()) //if name doesn't already exist
			Name::_globalNameTable[this->_name] = *this;
	}

	Name::Name(const Name& original)
	{
		this->_isNull = original._isNull;
		this->_name = original._name;
		this->_cname = this->_name.c_str();
		this->_length = original._length;
	}

	Name& Name::operator=(const Name &rhs)
	{
		if (this != &rhs)
		{
			this->_isNull = rhs._isNull;
			this->_name = rhs._name;
			this->_cname = this->_name.c_str();
			this->_length = rhs._length;
		}
		return *this;
	}

	size_t Name::length() const
	{
		size_t result = this->_name.length();
		return result;
	}

	size_t Name::hash() const
	{
		if(this->_isNull)
			return 0;
		else
		{
			int hash = 17;
			for(size_t i = 0; i < this->_name.length(); i++)
			{
				hash = hash * 23 + this->_name[i];
			}

			return hash;
		}
	}

	Name Name::findName(const char *nameString)
	{
		if(Name::_globalNameTable.find(nameString) == Name::_globalNameTable.end()) //if name doesn't exist
		{
			Name result(nameString); //create the name and insert it into _globalNameTable
			return result;
		}
		else //if name already exists
			return Name::_globalNameTable[nameString];
	}

	bool Name::hasName(const char *nameString)
	{
		return Name::_globalNameTable.find(nameString) != Name::_globalNameTable.end();
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