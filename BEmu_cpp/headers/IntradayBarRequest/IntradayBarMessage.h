//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/IntradayBarMessage.h" company="Jordan Robinson">
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
		class IntradayBarElementData;
		class IntradayBarTickDataType;
		class IntradayBarElementResponseError;

		class IntradayBarMessage : public MessagePtr
		{
			private:
				boost::shared_ptr<IntradayBarElementData> _parent;
				boost::shared_ptr<IntradayBarElementResponseError> _responseError;

				bool _isResponseError;

			public:
				IntradayBarMessage(const CorrelationId& corr, const Service& service, const std::string& security);
				IntradayBarMessage(const CorrelationId& corr, const Service& service, const std::vector< boost::shared_ptr<IntradayBarTickDataType> >& bars);

				~IntradayBarMessage();

				virtual const char* topicName() const;
				virtual size_t numElements() const;

				virtual boost::shared_ptr<ElementPtr> getElement(const char* name) const;

				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}