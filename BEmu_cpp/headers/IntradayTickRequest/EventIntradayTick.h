//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/EventIntradayTick.h" company="Jordan Robinson">
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

	namespace IntradayTickRequest
	{
		class RequestIntradayTick;

		class EventIntradayTick : public EventPtr
		{
			private:
				std::vector<MessagePtr*> *_messages;
				std::vector<MessagePtr*>* GenerateMessages();
				RequestIntradayTick *_internal;

			public:
				EventIntradayTick(RequestIntradayTick *request);
				~EventIntradayTick();

				virtual std::vector<MessagePtr*> *getMessages() const;
		};
	}
}