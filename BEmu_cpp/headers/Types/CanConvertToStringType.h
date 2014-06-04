//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/Types/CanConvertToStringType.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include <string>
#include <sstream>
#include "BloombergTypes/Datetime.h"

namespace BEmu
{
	class CanConvertToStringType
	{
		private:
			std::stringstream _ss;
			std::string _valueAsString;

			void ClearStream();

		protected:
			CanConvertToStringType(int arg);
			CanConvertToStringType(double arg);
			CanConvertToStringType(const std::string& arg);
			CanConvertToStringType(const Datetime& arg);
			
			//Use these to change the _valueAsString argument
			void ResetStringConversion(int arg);
			void ResetStringConversion(double arg);
			void ResetStringConversion(const std::string& arg);
			void ResetStringConversion(const Datetime& arg);
			
			const std::string& ValueAsString() const;
	};
}