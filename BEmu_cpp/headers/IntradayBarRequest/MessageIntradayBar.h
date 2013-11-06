//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/MessageIntradayBar.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/MessagePtr.h"
#include <vector>

namespace BEmu
{
	class ElementPtr;
	class CorrelationId;
	class Service;
	class Name;

	namespace IntradayBarRequest
	{
		class ElementBarData;
		class BarTickDataType;
		class ElementIntradayBarResponseError;

		class MessageIntradayBar : public MessagePtr
		{
			private:
				ElementBarData * _parent;
				ElementIntradayBarResponseError * _responseError;
				bool _isResponseError;

			public:
				MessageIntradayBar(const CorrelationId& corr, const Service& service, const std::string& security);
				MessageIntradayBar(const CorrelationId& corr, const Service& service, const std::vector<BarTickDataType*>& bars);
				~MessageIntradayBar();

				virtual const char* topicName() const;
				virtual size_t numElements() const;

				virtual const ElementPtr * getElement(const char* name) const;
				virtual bool hasElement(const char* name, bool excludeNullElements=false) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;

		};
	}
}