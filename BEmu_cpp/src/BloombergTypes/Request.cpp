//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/Request.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Request.h"

namespace BEmu
{
	Request::Request()
	{
		this->_ptr = 0;
	}

	Request::Request(RequestPtr *ptr)
	{
		//I don't know when to delete this pointer.
		//  I can't delete it in a Request::~Request() because that gets called often, and not at times when I would want to delete this->_ptr.
		//If I keep the pointer around until the end of program execution, that'll be a memory leak, but it shouldn't effect performance.
		//  I did not build this emulator for performance, simply education.
		this->_ptr = ptr;
	}

	Request::Request(const Request& arg)
	{
		this->_ptr = arg._ptr;
	}

	Request& Request::operator=(const Request &rhs)
	{
		if (this != &rhs)
		{
			this->_ptr = rhs._ptr;
		}
		return *this;
	}
	
	RequestPtr * Request::getRequestPtr() const
	{
		return this->_ptr;
	}

	void Request::append(const char* name, const char* value)
	{
		this->_ptr->append(name, value);
	}

	void Request::append(const Name& name, const char* value)
	{
		this->_ptr->append(name, value);
	}


	void Request::set(const char* name, const char* value)
	{
		this->_ptr->set(name, value);
	}

	void Request::set(const Name& name, const char* value)
	{
		this->_ptr->set(name, value);
	}


	void Request::set(const char* name, const Datetime& value)
	{
		this->_ptr->set(name, value);
	}
	void Request::set(const Name& name, const Datetime& value)
	{
		this->_ptr->set(name, value);
	}


	void Request::set(const char* name, bool value)
	{
		this->_ptr->set(name, value);
	}

	void Request::set(const Name& name, bool value)
	{
		this->_ptr->set(name, value);
	}


	void Request::set(const char* name, int value)
	{
		this->_ptr->set(name, value);
	}

	void Request::set(const Name& name, int value)
	{
		this->_ptr->set(name, value);
	}
}