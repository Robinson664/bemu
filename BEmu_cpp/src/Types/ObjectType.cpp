//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/Types/ObjectType.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "Types/ObjectType.h"
#include <iostream>
#include <stdlib.h>

namespace BEmu
{
	ObjectType::ObjectType()
	{
		this->_otype = eNothing;
	}

	ObjectType::ObjectType(double arg)
	{
		this->_dbl = arg;
		this->_otype = eDouble;
	}

	ObjectType::ObjectType(int arg)
	{
		this->_int = arg;
		this->_otype = eInt;
	}

	ObjectType::ObjectType(bool arg)
	{
		this->_bool = arg;
		this->_otype = eBool;
	}

	ObjectType::ObjectType(const std::string& arg)
	{
		this->_str = arg;
		this->_otype = eString;
	}

	ObjectType::ObjectType(const Datetime& arg)
	{
		this->_datetime = arg;
		this->_otype = eDatetime;
	}

	ObjectType::~ObjectType()
	{
	}

	ObjectType& ObjectType::operator=(const ObjectType &rhs)
	{
		if (this != &rhs)
		{
			this->_bool = rhs._bool;
			this->_datetime = rhs._datetime;
			this->_dbl = rhs._dbl;
			this->_int = rhs._int;
			this->_otype = rhs._otype;
			this->_str = rhs._str;
		}
		return *this;
	}

	ObjectType::ObjectType(const ObjectType& arg)
	{
		this->_bool = arg._bool;
		this->_datetime = arg._datetime;
		this->_dbl = arg._dbl;
		this->_int = arg._int;
		this->_otype = arg._otype;
		this->_str = arg._str;
	}

	ObjectType::ObjectTypeEnum ObjectType::GetType() const
	{
		return this->_otype;
	}

	bool ObjectType::TryGetDouble(double &arg) const
	{
		arg = this->_dbl;
		return this->_otype == eDouble;
	}

	bool ObjectType::TryGetInt(int &arg) const
	{
		arg = this->_int;
		return this->_otype == eInt;
	}

	bool ObjectType::TryGetBool(bool &arg) const
	{
		arg = this->_bool;
		return this->_otype == eBool;
	}

	bool ObjectType::TryGetString(std::string& arg) const
	{
		arg = this->_str;
		return this->_otype == eString;
	}

	bool ObjectType::TryGetDatetime(Datetime& arg) const
	{
		arg = this->_datetime;
		return this->_otype == eDatetime;
	}
}