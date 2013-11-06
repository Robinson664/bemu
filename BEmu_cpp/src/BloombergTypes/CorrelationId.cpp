//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/CorrelationId.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/CorrelationId.h"
#include <iostream>

namespace BEmu
{
	long CorrelationId::_nextInternalCorrelationId = 0;

	CorrelationId::CorrelationId()
	{
		this->_value = _nextInternalCorrelationId++;
		this->_isInternal = true;
	}

	CorrelationId::CorrelationId(long value)
	{
		this->_value = value;
		this->_isInternal = false;
	}

	CorrelationId::CorrelationId(const CorrelationId& other)
	{
		this->_isInternal = other._isInternal;
		this->_value = other._value;
	}

	CorrelationId& CorrelationId::operator=(const CorrelationId &rhs)
	{
		if (this != &rhs)
		{
			this->_isInternal = rhs._isInternal;
			this->_value = rhs._value;
		}
		return *this;
	}

	const long CorrelationId::asInteger() const
	{
		return this->_value;
	}

	std::ostream& operator<<(std::ostream& os, const CorrelationId& correlator)
	{
		os << "[ valueType=";
		os << (correlator._isInternal ? "AUTOGEN" : "INT");
		os << " classId=" << 0 << " value=" << correlator.asInteger() << " ]";
		return os;
	};
}