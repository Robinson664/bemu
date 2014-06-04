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
#include <boost/shared_ptr.hpp>

namespace BEmu
{
	class MessagePtr;

	namespace IntradayBarRequest
	{
		class IntradayBarRequest;

		class IntradayBarEvent : public EventPtr
		{
			private:
				//std::vector<MessagePtr*> * _message;
				std::vector< boost::shared_ptr<MessagePtr> > * _messages;

				//std::vector<MessagePtr*> * GenerateMessages() const;
				std::vector< boost::shared_ptr<MessagePtr> > * GenerateMessages() const;
				
				boost::shared_ptr<IntradayBarRequest> _internalP;
				//IntradayBarRequest *_internal;

			public:
				IntradayBarEvent(boost::shared_ptr<IntradayBarRequest> request);
				~IntradayBarEvent();

				//virtual std::vector<MessagePtr*> * getMessages() const;
				virtual std::vector< boost::shared_ptr<MessagePtr> > getMessages() const;
		};
	}
}