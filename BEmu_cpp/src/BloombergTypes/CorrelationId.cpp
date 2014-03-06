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
		this->_valueType = CorrelationId::UNSET_VALUE;

		this->_ptr = 0;
		this->_classId = -1;
		this->_value = _nextInternalCorrelationId++;
		this->_isInternal = true;
	}

	CorrelationId::CorrelationId(long value)
	{
		this->_valueType = CorrelationId::INT_VALUE;

		this->_ptr = 0;
		this->_classId = -1;
		this->_value = value;
		this->_isInternal = false;
	}

	CorrelationId::CorrelationId(const CorrelationId& other)
	{
		this->_valueType = other._valueType;

		this->_ptr = other._ptr;
		this->_classId = other._classId;
		this->_isInternal = other._isInternal;
		this->_value = other._value;
	}

	CorrelationId::CorrelationId(void * value, int classId)
	{
		this->_valueType = CorrelationId::POINTER_VALUE;

		this->_ptr = value;
		this->_classId = classId;
		this->_value = (long)value;
		this->_isInternal = false;
	}

	CorrelationId& CorrelationId::operator=(const CorrelationId &rhs)
	{
		if (this != &rhs)
		{
			this->_valueType = rhs._valueType;
			this->_classId = rhs._classId;
			this->_ptr = rhs._ptr;
			this->_isInternal = rhs._isInternal;
			this->_value = rhs._value;
		}
		return *this;
	}

	unsigned short CorrelationId::classId() const
	{
		return this->_classId;
	}

	long long CorrelationId::asInteger() const
	{
		return this->_value;
	}

	void * CorrelationId::asPointer() const
	{
		return this->_ptr;
	}

	CorrelationId::ValueType CorrelationId::valueType() const
	{
		return this->_valueType;
	}

	std::ostream& operator<<(std::ostream& os, const CorrelationId& correlator)
	{
		os << "[ valueType=";

		switch(correlator.valueType())
		{
			case CorrelationId::AUTOGEN_VALUE:
				os << "AUTOGEN";
				break;
			case CorrelationId::INT_VALUE:
				os << "INT";
				break;
			case CorrelationId::POINTER_VALUE:
				os << "POINTER";
				break;
			case CorrelationId::UNSET_VALUE:
				os << "UNSET";
				break;
		}

		os << " classId=" << correlator.classId() << " value=" << correlator.asInteger() << " ]";
		return os;
	}

	bool operator==(const CorrelationId& lhs, const CorrelationId& rhs)
	{
		if(lhs.valueType() == CorrelationId::POINTER_VALUE)
		{
			return rhs.valueType() == CorrelationId::POINTER_VALUE && lhs.asPointer() == rhs.asPointer();
		}
		else if(lhs.valueType() == CorrelationId::AUTOGEN_VALUE || lhs.valueType() == CorrelationId::INT_VALUE)
		{
			return 
				(rhs.valueType() == CorrelationId::AUTOGEN_VALUE || rhs.valueType() == CorrelationId::INT_VALUE) &&				
				lhs.asInteger() == rhs.asInteger();
		}
		else
			return lhs.valueType() == CorrelationId::UNSET_VALUE && rhs.valueType() == CorrelationId::UNSET_VALUE;
	}

	bool operator!=(const CorrelationId& lhs, const CorrelationId& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<(const CorrelationId& lhs, const CorrelationId& rhs)
	{
		if(lhs.valueType() == rhs.valueType())
		{
			if(lhs.asInteger() == rhs.asInteger())
			{
				if(lhs.asPointer() == rhs.asPointer())
					return false;
				else
					return lhs.asPointer() < rhs.asPointer();
			}
			else
				return lhs.asInteger() < rhs.asInteger();
		}
		else
			return lhs.valueType() < rhs.valueType();
	}
}