//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/Types/ObjectType.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/Datetime.h"

namespace BEmu
{
	class ObjectType
	{
		public:
			enum ObjectTypeEnum { eDouble, eInt, eBool, eString, eDatetime, eNothing };

			ObjectType();
			ObjectType(double arg);
			ObjectType(int arg);
			ObjectType(bool arg);
			ObjectType(std::string* arg);
			ObjectType(Datetime* arg);
			~ObjectType();

			ObjectTypeEnum GetType();
			bool TryGetDouble(double &arg);
			bool TryGetInt(int &arg);
			bool TryGetBool(bool &arg);
			bool TryGetString(std::string* arg);
			bool TryGetDatetime(Datetime* arg);

		private:
			ObjectTypeEnum _otype;

			double _dbl;
			int _int;
			bool _bool;
			std::string* _str;
			Datetime* _datetime;

	};
}