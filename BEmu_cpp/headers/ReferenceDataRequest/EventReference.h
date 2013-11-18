//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/ReferenceDataRequest/EventReference.h" company="Jordan Robinson">
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

	namespace ReferenceDataRequest
	{
		class RequestReference;

		class EventReference : public EventPtr
		{
			private:
				std::vector<MessagePtr*> * _messages;
				std::vector<MessagePtr*> * generateMessages() const;
				RequestReference * _internal;

			public:
				EventReference(RequestReference * request);
				~EventReference();

				virtual std::vector<MessagePtr*> * getMessages() const;
		};
	}
}