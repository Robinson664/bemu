//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/ReferenceDataRequest/ReferenceEvent.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/EventPtr.h"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace BEmu
{
	class MessagePtr;

	namespace ReferenceDataRequest
	{
		class ReferenceRequest;

		class ReferenceEvent : public EventPtr
		{
			private:
				std::vector< boost::shared_ptr<MessagePtr> > * _messages;
				//std::vector<MessagePtr*> * _messages;

				std::vector< boost::shared_ptr<MessagePtr> > * generateMessages() const;
				//std::vector<MessagePtr*> * generateMessages() const;
				
				boost::shared_ptr<ReferenceRequest> _internalP;
				//ReferenceRequest * _internal;

			public:
				ReferenceEvent(boost::shared_ptr<ReferenceRequest> request);
				//ReferenceEvent(ReferenceRequest * request);

				~ReferenceEvent();

				//virtual std::vector<MessagePtr*> * getMessages() const;
				virtual std::vector< boost::shared_ptr<MessagePtr> > getMessages() const;
		};
	}
}