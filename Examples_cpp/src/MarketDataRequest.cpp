//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include <map>
#include <vector>
#include "examples.h"
#include "api_selector.h"
#include "SubscriptionEventHandler.h"

using namespace std;

namespace Examples
{
	//Most of the functionality for this Market Data example is in SubscriptionEventHandler.cpp
	//Please note that there can be several ways to work with MarketDataEvents.
	//  The most important requirement is that the Session constructor requires an object of a class that implements EventHandler
	//    * EventHandler is defined in blpapi_session.h for the BB API and in BEmu_cpp/headers/BloombergTypes/EventHandler.h for BEmu
	int RunMarketDataExample()
	{
		int securityId = 1;
		map<int, string> corrs2Security; //a map of correlation ids to security keys
		corrs2Security[securityId++] = "IBM US Equity";
		corrs2Security[securityId++] = "GOOG US Equity";
		corrs2Security[securityId++] = "MSFT US Equity";

		//uncomment the following line to see what a request for a nonexistent security looks like
		//corrs2Security[securityId++] = "ZMSFT US Equity";
		//  My code treats all securities that start with a 'Z' as a nonexistent security

		vector<string> fields; //a list of realtime fields
		fields.push_back("BID");
		fields.push_back("ASK");

		//uncomment the following line to see what a request for a nonexistent field looks like
		//fields.push_back("ZASK");
		//  My code treats all fields that start with a 'Z' as a nonexistent field

		SessionOptions sessionOptions;
		sessionOptions.setServerHost("localhost");
		sessionOptions.setServerPort(8194);

		SubscriptionEventHandler subscriptionEventHandler(corrs2Security, fields); //use this constructor to receive market updates as they happen
		//SubscriptionEventHandler subscriptionEventHandler(corrs2Security, fields, 3); //use this constructor to receive market updates at most every N seconds (3 seconds in this case)

		Session session(sessionOptions, &subscriptionEventHandler);
	
		if (!session.startAsync())
		{
			cerr << "Failed to start session." << endl;
			return 1;
		}

		pressEnterToQuit();

		session.stop();

		return 0;
	}

}