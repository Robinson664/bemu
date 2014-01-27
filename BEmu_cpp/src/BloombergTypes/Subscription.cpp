//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/Subscription.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Subscription.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace BEmu
{
	Subscription::Subscription(std::string topic, std::string fields, std::string options, CorrelationId correlationId)
	{
		this->construct(topic, fields, options, correlationId);
		this->_hasConflationInterval = false;
	}

	Subscription::Subscription(std::string topic, std::string fields, std::string options, CorrelationId correlationId, int conflationInterval)
	{
		this->construct(topic, fields, options, correlationId);
		this->_hasConflationInterval = true;
		this->_conflationInterval = conflationInterval;
	}

	void Subscription::construct(std::string topic, std::string fields, std::string options, CorrelationId correlationId)
	{
		this->_corr = correlationId;
		this->_fields = fields;
		this->_options = options;
		this->_security = topic;

		int start = 0;
		for(size_t i = 1; i < fields.length(); i++)
		{
			if(fields.at(i) == ',')
			{
				std::string current = fields.substr(start, i - start);
				this->_fieldList.push_back(current);
				
				start = i + 1;
				i = start + 1;
			}
		}

		std::string last = fields.substr(start);
		this->_fieldList.push_back(last);
	}

	Subscription::~Subscription()
	{
	}

	Subscription::Subscription(const Subscription& arg)
	{
		this->_corr = arg._corr;
		this->_fields = arg._fields;
		this->_options = arg._options;
		this->_security = arg._security;

		this->_fieldList = std::vector<std::string>(arg._fieldList.begin(), arg._fieldList.end());
	}

	Subscription& Subscription::operator=(const Subscription& rhs)
	{
		if (this != &rhs)
		{
			this->_corr = rhs._corr;
			this->_fields = rhs._fields;
			this->_options = rhs._options;
			this->_security = rhs._security;

			this->_fieldList = std::vector<std::string>(rhs._fieldList.begin(), rhs._fieldList.end());
		}
		return *this;
	}

	std::vector<std::string> Subscription::fieldList() const
	{
		return this->_fieldList;
	}

	std::string Subscription::security() const
	{
		return this->_security;
	}

	std::string Subscription::fields() const
	{
		return this->_fields;
	}

	std::string Subscription::options() const
	{
		return this->_options;
	}

	CorrelationId Subscription::correlationId() const
	{
		return this->_corr;
	}

	bool Subscription::hasConflationInterval() const
	{
		return this->_hasConflationInterval;
	}

	int Subscription::conflationInterval() const
	{
		return this->_conflationInterval;
	}
}