//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/SubscriptionList.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/SubscriptionList.h"
#include "BloombergTypes/Subscription.h"

namespace BEmu
{
	SubscriptionList::SubscriptionList()
	{
		this->_subs = new std::vector<Subscription>();
	}
	
	SubscriptionList::~SubscriptionList()
	{
		delete this->_subs;
	}
	
	SubscriptionList::SubscriptionList(const SubscriptionList& original)
	{
		this->_subs = new std::vector<Subscription>(original._subs->begin(), original._subs->end());

		//std::vector<Subscription> * subs = original._subs;
		//for(std::vector<Subscription>::const_iterator iter = subs->begin(); iter != subs->end(); ++iter)
		//{
		//}
	}

	SubscriptionList& SubscriptionList::operator=(const SubscriptionList& rhs)
	{
		if(this != &rhs)
		{
			this->_subs = new std::vector<Subscription>(*(rhs._subs));
		}
		return *this;
	}

	int SubscriptionList::add(const char* topic, const char* fields, const char* options, const CorrelationId& correlationId)
	{
		Subscription sub(topic, fields, options, correlationId);
		this->_subs->push_back(sub);
		return 1; //I'm not sure what the add function returns
	}

	void SubscriptionList::add(Subscription sub)
	{
		this->_subs->push_back(sub);
	}

	std::vector<Subscription> * SubscriptionList::list() const
	{
		return this->_subs;
	}
}