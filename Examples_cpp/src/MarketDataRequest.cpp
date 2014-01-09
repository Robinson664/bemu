//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/Examples/MarketDataRequest.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include <iostream>
#include <time.h>
#include <map>
#include <vector>
#include "api_selector.h"
#include "examples.h"
#include <sstream>

using namespace std;

namespace Examples
{
	class SubscriptionEventHandler: public EventHandler
	{
		private:
			void handleDataEvent (const Event& event, Session * session);
			void handleSubscriptionStatus (const Event& event, Session * session);
			void handleSessionStatus(const Event& event, Session * session);
			void handleServiceStatus(const Event& event, Session * session);

			map<int, string> _corrs2Security; //maps correlation ids to securities (The security name is not in Message.topicName())
			vector<string> _fields; //a list of requested fields
			char * _cfields; //a comma-delimited list of requested fields

		public:
			SubscriptionEventHandler(map<int, string> corrs2Security, vector<string> fields);
			~SubscriptionEventHandler();

			virtual bool processEvent(const Event& event, Session *session); //this overrides the abstract EventHandler::processEvent
	};

	SubscriptionEventHandler::SubscriptionEventHandler(map<int, string> corrs2Security, vector<string> fields)
	{
		this->_corrs2Security = corrs2Security;
		this->_fields = fields;

		stringstream ssFields;
		int size = (int)this->_fields.size();
		for(int i = 0; i < size; i++)
		{
			ssFields << this->_fields.at(i);
			if(i < size - 1)
				ssFields << ",";
		}
		string sfields = ssFields.str();
		this->_cfields = new char[sfields.length() + 1];
		strncpy(this->_cfields, sfields.c_str(), sfields.length() + 1);
	}

	SubscriptionEventHandler::~SubscriptionEventHandler()
	{
		delete[] this->_cfields;
		this->_cfields = 0;
	}

	//The Bloomberg API calls this function on a separate thread
	bool SubscriptionEventHandler::processEvent(const Event& event, Session * session)
	{
		switch (event.eventType())
		{
			case Event::SESSION_STATUS:
				this->handleSessionStatus(event, session); //attempts to open the //blp/mktdata service
				break;
				
			case Event::SERVICE_STATUS:
				this->handleServiceStatus(event, session); //attempts to subscribe for market data
				break;

			case Event::SUBSCRIPTION_DATA:
				this->handleDataEvent(event, session); //handles market data events
				break;

			case Event::SUBSCRIPTION_STATUS:
				this->handleSubscriptionStatus(event, session); //handles any security or field errors
				break;
		}
		return true;
	}

	void SubscriptionEventHandler::handleSubscriptionStatus(const Event& event, Session * session)
	{
		MessageIterator messageIterator(event);
		while (messageIterator.next())
		{
			Message message = messageIterator.message();

			bool fieldExceptionsExist = message.messageType() == "SubscriptionStarted" && message.hasElement("exceptions", true);
			bool securityError = message.messageType() == "SubscriptionFailure" && message.hasElement("reason", true);

			if(fieldExceptionsExist)
			{
				Element elmExceptions = message.getElement("exceptions");
				for (size_t i = 0; i < elmExceptions.numValues(); i++)
				{
					Element elmException = elmExceptions.getValueAsElement(i);
                    const char * fieldId = elmException.getElementAsString("fieldId");

					Element elmReason = elmException.getElement("reason");
                    const char * source = elmReason.getElementAsString("source");
                    const char * category = elmReason.getElementAsString("category");
                    const char * description = elmReason.getElementAsString("description");

                    cerr << "field error: " << endl;
                    cerr << "\tfieldId = " << fieldId << endl;
                    cerr << "\tsource = " << source << endl;
                    cerr << "\tcategory = {0}" << category << endl;
                    cerr << "\tdescription = " << description << endl;
				}
			}
			else if(securityError)
			{
				string security = this->_corrs2Security[(int)message.correlationId().asInteger()];

				Element elmReason = message.getElement("reason");
                const char * source = elmReason.getElementAsString("source");
                int errorCode = elmReason.getElementAsInt32("errorCode");
                const char * category = elmReason.getElementAsString("category");
                const char * description = elmReason.getElementAsString("description");

                cerr << "security not found:" << endl;
                cerr << "\tsecurity = " << security << endl;
                cerr << "\tsource = " << source << endl;
                cerr << "\terrorCode = " << errorCode << endl;
                cerr << "\tcategory = " << category << endl;
                cerr << "\tdescription = " << description << endl;
			}
		}
	}

	void SubscriptionEventHandler::handleSessionStatus(const Event& event, Session * session)
	{
		MessageIterator messageIterator(event);
		while (messageIterator.next())
		{
			Message message = messageIterator.message();
			if(message.messageType() == "SessionStarted")
			{
				session->openServiceAsync("//blp/mktdata", CorrelationId(-9999));
			}
		}
	}

	void SubscriptionEventHandler::handleServiceStatus(const Event& event, Session * session)
	{
		SubscriptionList subscriptions;
		for(map<int, string>::const_iterator iter = this->_corrs2Security.begin(); iter != this->_corrs2Security.end(); ++iter)
		{
			int corr = iter->first;
			string security = iter->second;
			subscriptions.add(security.c_str(), this->_cfields, "interval=3", CorrelationId(corr));
		}	
		session->subscribe(subscriptions);
	}

	void SubscriptionEventHandler::handleDataEvent(const Event& event, Session * session)
	{
		MessageIterator messageIterator(event);
		while (messageIterator.next())
		{
			Message message = messageIterator.message();

			int corr = (int)message.correlationId().asInteger();
			string security = this->_corrs2Security[corr];

			for(size_t i = 0; i < this->_fields.size(); i++)
			{
				if(message.hasElement(this->_fields.at(i).c_str(), true))
					cout << security << ": " << this->_fields.at(i) << " = " << message.getElementAsFloat64(this->_fields.at(i).c_str()) << endl;
			}
		}
	}


	int RunMarketDataExample()
	{
		int securityId = 1;
		map<int, string> corrs2Security;
		corrs2Security[securityId++] = "IBM US Equity";
		corrs2Security[securityId++] = "GOOG US Equity";
		corrs2Security[securityId++] = "MSFT US Equity";
		//corrs2Security[securityId++] = "ZMSFT US Equity";

		vector<string> fields;
		fields.push_back("BID");
		fields.push_back("ASK");
		//fields.push_back("ZASK");

		SessionOptions sessionOptions;
		sessionOptions.setServerHost("localhost");
		sessionOptions.setServerPort(8194);
		SubscriptionEventHandler subscriptionEventHandler(corrs2Security, fields);
		Session session(sessionOptions, &subscriptionEventHandler);
	
		if (!session.startAsync())
		{
			cerr << "Failed to start session." << endl;
			return 1;
		}

		pressEnterToQuit();
		return 0;
	}

}