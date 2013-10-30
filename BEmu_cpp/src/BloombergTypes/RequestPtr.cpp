//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/RequestPtr.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/RequestPtr.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Datetime.h"
#include "BloombergTypes/CorrelationId.h"

#include "IntradayTickRequest/RequestIntradayTick.h"

namespace BEmu
{
	RequestPtr::RequestPtr()
	{
		this->_correlationId = new CorrelationId();
	}

	RequestPtr::RequestPtr(const RequestPtr &src)
	{
		this->_correlationId = new CorrelationId(src._correlationId->asInteger());
		this->_requestType = src._requestType;
	}

	CorrelationId * RequestPtr::getCorrelationId() const
	{
		return this->_correlationId;
	}

	void RequestPtr::setCorrelationId(CorrelationId * arg)
	{
		delete this->_correlationId;
		this->_correlationId = arg;
	}

	RequestPtr::RequestTypeEnum RequestPtr::getRequestType() const
	{
		return this->_requestType;
	}

	void RequestPtr::append(const char* name, const char* value)
	{
		throw requestEx;
	}
	void RequestPtr::append(const Name& name, const char* value) { return this->append(name.string(), value); }

	void RequestPtr::set(const char* name, const char* value) { throw requestEx; }
	void RequestPtr::set(const Name& name, const char* value) { return this->set(name.string(), value); }

	void RequestPtr::set(const char* name, bool value) { throw requestEx; }
	void RequestPtr::set(const Name& name, bool value) { return this->set(name.string(), value); }

	void RequestPtr::set(const char* name, int value) { throw requestEx; }
	void RequestPtr::set(const Name& name, int value) { return this->set(name.string(), value); }

	void RequestPtr::set(const char* name, const Datetime& value) { throw requestEx; }
	void RequestPtr::set(const Name& name, const Datetime& value) { return this->set(name.string(), value); }

	Element RequestPtr::getElement(const char* name) { throw requestEx; }
	Element RequestPtr::getElement(const Name& name) { return this->getElement(name.string()); }

}