//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/SubscriptionEventHandler.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "api_selector.h"

using namespace std;

namespace Examples
{
	//You must provide a class that inherits EventHandler in order to handle Market Data Events, EventHandler is defined in
	//  #include "BloombergTypes/EventHandler.h" (BEmu), or
	//  #include "blpapi_session.h" (BB API)
	class SubscriptionEventHandler : public EventHandler
	{
		private:
			void openService(const Event& event, Session * session);
			void subscribe(const Event& event, Session * session);
			void dataReceived(const Event& event, Session * session);
			void securityOrFieldError(const Event& event, Session * session);

			map<int, string> _corrs2Security; //maps correlation ids to securities (The security name is not in Message.topicName())
			vector<string> _fields; //a list of requested fields
			char * _cfields; //a comma-delimited string of requested fields

			int _intervalInSeconds;
			bool _hasInterval;

			void initialize(map<int, string> corrs2Security, vector<string> fields);

		public:
			SubscriptionEventHandler(map<int, string> corrs2Security, vector<string> fields);
			SubscriptionEventHandler(map<int, string> corrs2Security, vector<string> fields, int intervalInSeconds);
			~SubscriptionEventHandler();

			virtual bool processEvent(const Event& event, Session *session); //The API calls this function when a market data event happens
	};
}