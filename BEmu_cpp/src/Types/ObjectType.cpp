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

	ObjectType::ObjectType(std::string* arg)
	{
		this->_str = arg;
		this->_otype = eString;
	}

	ObjectType::ObjectType(Datetime* arg)
	{
		this->_datetime = new Datetime(*arg);
		this->_otype = eDatetime;
	}

	ObjectType::~ObjectType()
	{
		if(this->_otype == eString)
		{
			delete this->_str;
			this->_str = 0;
		}
		else if(this->_otype == eDatetime)
		{
			delete this->_datetime;
			this->_datetime = 0;
		}
	}

	ObjectType::ObjectTypeEnum ObjectType::GetType()
	{
		return this->_otype;
	}

	bool ObjectType::TryGetDouble(double &arg)
	{
		arg = this->_dbl;
		return this->_otype == eDouble;
	}

	bool ObjectType::TryGetInt(int &arg)
	{
		arg = this->_int;
		return this->_otype == eInt;
	}

	bool ObjectType::TryGetBool(bool &arg)
	{
		arg = this->_bool;
		return this->_otype == eBool;
	}

	bool ObjectType::TryGetString(std::string* arg)
	{
		arg = this->_str;
		return this->_otype == eString;
	}

	bool ObjectType::TryGetDatetime(Datetime* arg)
	{
		arg = this->_datetime;
		return this->_otype == eDatetime;
	}
}