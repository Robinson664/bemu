//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/IntradayBarEvent.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include <vector>
#include "BloombergTypes/EventPtr.h"

namespace BEmu
{
	class MessagePtr;

	namespace IntradayBarRequest
	{
		class IntradayBarRequest;

		class IntradayBarEvent : public EventPtr
		{
			private:
				std::vector<MessagePtr*> * _message;
				std::vector<MessagePtr*> * GenerateMessages() const;
				IntradayBarRequest *_internal;

			public:
				IntradayBarEvent(IntradayBarRequest * request);
				~IntradayBarEvent();

				virtual std::vector<MessagePtr*> *getMessages() const;
		};
	}
}