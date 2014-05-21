//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/SubscriptionEventHandler.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "SubscriptionEventHandler.h"

namespace Examples
{
	SubscriptionEventHandler::SubscriptionEventHandler(map<int, string> corrs2Security, vector<string> fields)
	{
		this->initialize(corrs2Security, fields);

		this->_hasInterval = false;
	}

	SubscriptionEventHandler::SubscriptionEventHandler(map<int, string> corrs2Security, vector<string> fields, int intervalInSeconds)
	{
		this->initialize(corrs2Security, fields);
		
		this->_hasInterval = true;
		this->_intervalInSeconds = intervalInSeconds;
	}

	void SubscriptionEventHandler::initialize(map<int, string> corrs2Security, vector<string> fields)
	{
		this->_corrs2Security = corrs2Security;
		this->_fields = fields;

		//turns a collection that looks like { "BID", "ASK", "LAST" } into a string that looks like "BID,ASK,LAST"
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
				this->openService(event, session); //attempts to open the //blp/mktdata service
				break;
				
			case Event::SERVICE_STATUS:
				this->subscribe(event, session); //attempts to subscribe for market data
				break;

			case Event::SUBSCRIPTION_DATA:
				this->dataReceived(event, session); //handles market data events
				break;

			case Event::SUBSCRIPTION_STATUS:
				this->securityOrFieldError(event, session); //handles any security or field errors
				break;
		}
		return true;
	}

	void SubscriptionEventHandler::openService(const Event& event, Session * session)
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

	void SubscriptionEventHandler::subscribe(const Event& event, Session * session)
	{
		SubscriptionList subscriptions;
		for(map<int, string>::const_iterator iter = this->_corrs2Security.begin(); iter != this->_corrs2Security.end(); ++iter)
		{
			int corr = iter->first;
			string security = iter->second;

			if(this->_hasInterval)
			{
				stringstream ssInterval;
				ssInterval << "interval=" << this->_intervalInSeconds;

				subscriptions.add(security.c_str(), this->_cfields, ssInterval.str().c_str(), CorrelationId(corr));
			}
			else
			{
				subscriptions.add(security.c_str(), this->_cfields, "", CorrelationId(corr));
			}
		}	
		session->subscribe(subscriptions);
	}

	void SubscriptionEventHandler::dataReceived(const Event& event, Session * session)
	{
		MessageIterator messageIterator(event);
		while (messageIterator.next())
		{
			Message message = messageIterator.message();

			int corr = (int)message.correlationId().asInteger();
			string security = this->_corrs2Security[corr];

			if(message.hasElement("BID", true))
				cout << security << ": BID = " << message.getElementAsFloat64("BID") << endl;
				
			if(message.hasElement("ASK", true))
				cout << security << ": ASK = " << message.getElementAsFloat64("ASK") << endl;
		}
	}

	void SubscriptionEventHandler::securityOrFieldError(const Event& event, Session * session)
	{
		MessageIterator messageIterator(event);
		while (messageIterator.next())
		{
			Message message = messageIterator.message();

			bool fieldExceptionsExist = message.messageType() == "SubscriptionStarted" && message.hasElement("exceptions", true);
			bool securityError = message.messageType() == "SubscriptionFailure" && message.hasElement("reason", true);
			bool subscriptionCancelled = message.messageType() == "SubscriptionTerminated";

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
			else if(subscriptionCancelled)
			{
				string security = this->_corrs2Security[(int)message.correlationId().asInteger()];
				cout << "Cancelled \"" << security << "\" subscription" << endl;
			}
		}
	}
}