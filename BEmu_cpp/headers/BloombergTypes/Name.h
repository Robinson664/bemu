//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/Name.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "bemu_headers.h"

namespace BEmu
{
	class Name
	{
		private:
			std::string _name;
			const char * _cname;
			int _length;

		public:
			DLL_EXPORT Name();
			DLL_EXPORT Name(const char* nameString);
			DLL_EXPORT Name(const Name& original);
			DLL_EXPORT const char *string() const;
			Name& operator=(const Name &rhs);
			
			DLL_EXPORT bool operator==(const char *rhs) const;
			DLL_EXPORT bool operator==(const Name rhs) const;
			DLL_EXPORT bool operator!=(const char *rhs) const;
			DLL_EXPORT bool operator!=(const Name rhs) const;
	};

	DLL_EXPORT std::ostream& operator<<(std::ostream& stream, const Name& name);
	DLL_EXPORT bool operator==(const char *lhs, const Name& rhs);
	DLL_EXPORT bool operator!=(const char *lhs, const Name& rhs);
}