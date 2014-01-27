//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/MarketDataRequest/MessageMarketServiceStatus.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/MessagePtr.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		class ElementMarketString;

		class MessageMarketServiceStatus : public MessagePtr
		{
			private:
				ElementMarketString * _serviceName;

			public:
				MessageMarketServiceStatus(CorrelationId corr);

				ElementPtr * firstElement() const;

				virtual size_t numElements() const;
				virtual const char* topicName() const;
				virtual ElementPtr * asElement() const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}