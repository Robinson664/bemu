//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/MessageIntradayBar.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/MessagePtr.h"
#include "IntradayBarRequest/MessageIntradayBar.h"
#include "IntradayBarRequest/ElementBarData.h"
#include "IntradayBarRequest/MessageIntradayBar.h"
#include "IntradayBarRequest/ElementIntradayBarResponseError.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		MessageIntradayBar::MessageIntradayBar(const CorrelationId& corr, const Service& service, const std::string& security) : MessagePtr(Name("IntradayBarResponse"), corr)
		{
            this->_responseError = new ElementIntradayBarResponseError(security);
            this->_parent = 0;
            this->_isResponseError = true;
		}

		MessageIntradayBar::MessageIntradayBar(const CorrelationId& corr, const Service& service, const std::vector<BarTickDataType*>& bars) : MessagePtr(Name("IntradayBarResponse"), corr)
		{
            this->_parent = new ElementBarData(bars);
            this->_responseError = 0;
            this->_isResponseError = false;
		}

		MessageIntradayBar::~MessageIntradayBar()
		{
			delete this->_responseError;
			this->_responseError = 0;

			delete this->_parent;
			this->_parent = 0;
		}

		const char* MessageIntradayBar::topicName() const
		{
			return "";
		}

		size_t MessageIntradayBar::numElements() const
		{
			return 1;
		}

		const ElementPtr * MessageIntradayBar::getElement(const char* name) const
		{
            if (this->_isResponseError)
			{
				if(strncmp(name, "responseError", 14) == 0)
					return this->_responseError;
				else
					throw messageEx;
			}
			else
			{
				if(strncmp(name, "barData", 8) == 0)
					return this->_parent;
				else
					throw messageEx;
			}
		}

		bool MessageIntradayBar::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(strncmp(name, "responseError", 14) == 0 && this->_isResponseError) ||
				(strncmp(name, "barData", 8) == 0 && !this->_isResponseError);
		}

		std::ostream& MessageIntradayBar::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "IntradayBarResponse (choice) = {" << std::endl;

			if(this->_isResponseError)
				this->_responseError->print(stream, level, spacesPerLevel);
			else
				this->_parent->print(stream, level, spacesPerLevel);

			stream << '}' << std::endl;
			return stream;
		}

	}
}