//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/Types/CanConvertToStringType.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "Types/CanConvertToStringType.h"

namespace BEmu
{
	CanConvertToStringType::CanConvertToStringType(double arg)
	{
		//this->_ss << arg;
		//this->_valueAsString = this->_ss.str();
		this->ResetStringConversion(arg);
	}
	
	CanConvertToStringType::CanConvertToStringType(int arg)
	{
		//this->_ss << arg;
		//this->_valueAsString = this->_ss.str();
		this->ResetStringConversion(arg);
	}
	
	CanConvertToStringType::CanConvertToStringType(const std::string& arg)
	{
		//this->_valueAsString = arg;
		this->ResetStringConversion(arg);
	}

	CanConvertToStringType::CanConvertToStringType(const Datetime& arg)
	{
		//this->_ss << arg;
		//this->_valueAsString = this->_ss.str();
		this->ResetStringConversion(arg);
	}

	const std::string& CanConvertToStringType::ValueAsString() const
	{
		return this->_valueAsString;
	}

	void CanConvertToStringType::ClearStream()
	{
		this->_ss.str(std::string()); //clears out the stringstream
	}
	
	void CanConvertToStringType::ResetStringConversion(int arg)
	{
		this->ClearStream();
		this->_ss << arg;
		this->_valueAsString = this->_ss.str();
	}

	void CanConvertToStringType::ResetStringConversion(double arg)
	{
		this->ClearStream();
		this->_ss << arg;
		this->_valueAsString = this->_ss.str();
	}

	void CanConvertToStringType::ResetStringConversion(const std::string& arg)
	{
		this->ClearStream();
		this->_valueAsString = arg;
	}

	void CanConvertToStringType::ResetStringConversion(const Datetime& arg)
	{
		this->ClearStream();
		this->_ss << arg;
		this->_valueAsString = this->_ss.str();
	}
}