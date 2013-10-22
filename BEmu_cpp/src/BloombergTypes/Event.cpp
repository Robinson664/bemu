//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/Event.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Event.h"
#include "BloombergTypes/EventPtr.h"
#include "BloombergTypes/RequestPtr.h"

namespace BEmu
{
	Event::Event()
	{
		this->_ptr = 0;
	}

	Event::Event(EventPtr *ptr)
	{
		this->_ptr = ptr;
	}

	Event::Event(const Event& arg)
	{
		this->_ptr = arg._ptr;
	}

	Event& Event::operator=(const Event &rhs)
	{
		if (this != &rhs)
		{
			this->_ptr = rhs._ptr;
		}
		return *this;
	}

	Event::EventType Event::eventType()
	{
		return this->_ptr->eventType();
	}

}