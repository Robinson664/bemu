//------------------------------------------------------------------------------
// <copyright project="BEmu" file="headers/HistoricalDataRequest/ElementHistoric.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		class MessageHistoric;
		class ElementHistoricSecurityData;

		class ElementHistoric : public ElementPtr
		{
			private:
				ElementHistoricSecurityData * _security;

			public:
				ElementHistoric(const MessageHistoric& msg);
				~ElementHistoric();

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
		
				virtual bool isNull() const;
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}