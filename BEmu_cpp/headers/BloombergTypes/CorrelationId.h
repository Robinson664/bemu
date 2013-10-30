//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/CorrelationId.h" company="Jordan Robinson">
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
	class CorrelationId
	{
		private:
			bool _isInternal;
			long _value;
			static long _nextInternalCorrelationId; //initial correlation ID

		public:
			DLL_EXPORT const long asInteger() const;

			DLL_EXPORT CorrelationId();
			DLL_EXPORT CorrelationId(long value);
			DLL_EXPORT CorrelationId(const CorrelationId& other);

			friend DLL_EXPORT std::ostream& operator<<(std::ostream& os, const CorrelationId& correlator); //needs access to _isInternal
	};
}