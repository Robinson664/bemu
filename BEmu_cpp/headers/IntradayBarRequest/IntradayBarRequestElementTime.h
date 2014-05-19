//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/IntradayBarRequestElementTime.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "IntradayBarRequest/IntradayBarRequestElementString.h"

namespace BEmu
{
	class Datetime;

	namespace IntradayBarRequest
	{
		class IntradayBarRequestElementTime : public IntradayBarRequestElementString
		{
			private:
				Datetime _dtvalue;

			public:
				IntradayBarRequestElementTime(const std::string& elementName);
				IntradayBarRequestElementTime(const std::string& elementName, const Datetime& dtvalue);
				~IntradayBarRequestElementTime();
				Datetime getDatetime() const;
		};
	}
}