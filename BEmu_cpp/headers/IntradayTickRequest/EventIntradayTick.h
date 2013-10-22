//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/EventIntradayTick.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\MessagePtr.h"
#include "BloombergTypes\EventPtr.h"

#include <vector>

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class RequestIntradayTick;

		class EventIntradayTick : private EventPtr
		{
			private:
				EventIntradayTick(RequestIntradayTick *request);
				~EventIntradayTick();

				std::vector<MessagePtr*> *_messages;
				std::vector<MessagePtr*>* GenerateMessages();
				RequestIntradayTick *_internal;
				std::vector<MessagePtr*> *getMessages() const;

			public:
				friend class EventPtr;
		};
	}
}