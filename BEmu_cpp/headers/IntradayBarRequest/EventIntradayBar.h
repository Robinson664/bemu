//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/EventIntradayBar.h" company="Jordan Robinson">
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
		class RequestIntradayBar;

		class EventIntradayBar : public EventPtr
		{
			private:
				std::vector<MessagePtr*> * _message;
				std::vector<MessagePtr*> * GenerateMessages() const;
				RequestIntradayBar *_internal;

			public:
				EventIntradayBar(RequestIntradayBar * request);
				~EventIntradayBar();

				virtual std::vector<MessagePtr*> *getMessages() const;
		};
	}
}