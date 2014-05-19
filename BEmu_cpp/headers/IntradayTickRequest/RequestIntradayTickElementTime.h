//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/IntradayTickRequestElementTime.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "IntradayTickRequest/IntradayTickRequestElementString.h"

namespace BEmu
{
	class Datetime;

	namespace IntradayTickRequest
	{
		class IntradayTickRequestElementTime : public IntradayTickRequestElementString
		{
			private:
				Datetime _instance;

			public:
				IntradayTickRequestElementTime(const std::string& elementName);
				IntradayTickRequestElementTime(const std::string& elementName, const Datetime& date);
				~IntradayTickRequestElementTime();
				Datetime getDate();
		};
	}
}