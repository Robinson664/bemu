//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/IntradayTickElementTuple3.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class IntradayTickElementTuple3
		{
			private:
				std::string _item1;
				double _item2;
				int _item3;

			public:
				IntradayTickElementTuple3(std::string item1, double item2, int item3);

				std::string item1() const;
				double item2() const;
				int item3() const;
		};
	}
}