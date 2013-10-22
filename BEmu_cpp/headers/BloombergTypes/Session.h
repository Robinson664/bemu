//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/Session.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Event.h"
#include "BloombergTypes/SessionOptions.h"
#include "BloombergTypes/CorrelationId.h"
#include "BloombergTypes/Service.h"
#include "BloombergTypes/Request.h"

#include <queue>
#include <vector>
#include <exception>

#pragma once

namespace BEmu
{
	class Session
	{
		private:
			Session(const Session&);

			enum SessionStateType { initialized, started, serviceOpened, stopped, connectionFailure };
			SessionStateType _sessionState;
			SessionOptions _sessionOptions;

			std::queue<RequestPtr*> _sentRequests;

		public:

			class SessionException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} sessionEx;

			///////////////////// Start Sync
			DLL_EXPORT Session(const SessionOptions& options);
			DLL_EXPORT bool start();
			DLL_EXPORT bool startAsync();
			DLL_EXPORT void stop();
			DLL_EXPORT bool openService(const char* uri);
			DLL_EXPORT Service getService(const char* uri) const;
			DLL_EXPORT CorrelationId sendRequest(const Request& request, const CorrelationId& correlationId = CorrelationId());
			DLL_EXPORT Event nextEvent(int timeout=0);
			///////////////////// End Sync

			DLL_EXPORT ~Session();
	};
}