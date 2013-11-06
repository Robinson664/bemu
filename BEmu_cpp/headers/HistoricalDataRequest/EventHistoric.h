//------------------------------------------------------------------------------
// <copyright project="BEmu" file="headers/HistoricalDataRequest/EventHistoric.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/EventPtr.h"
#include <vector>

namespace BEmu
{
	class MessagePtr;

	namespace HistoricalDataRequest
	{
		class RequestHistoric;

		class EventHistoric : public EventPtr
		{
			private:
				std::vector<MessagePtr*> * _messages;
				std::vector<MessagePtr*> * GenerateMessages() const;
				RequestHistoric * _internal;

			public:
				EventHistoric(RequestHistoric * request);
				~EventHistoric();
				
				virtual std::vector<MessagePtr*> *getMessages() const;
		};
	}
}