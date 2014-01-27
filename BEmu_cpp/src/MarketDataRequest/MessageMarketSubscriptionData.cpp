//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MessageMarketSubscriptionData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MessageMarketSubscriptionData.h"
#include "MarketDataRequest/ElementMarketDouble.h"
#include "MarketDataRequest/ElementMarketDatetime.h"
#include "MarketDataRequest/ElementMarketInt.h"
#include "MarketDataRequest/ElementMarketString.h"
#include "MarketDataRequest/ElementMarketBool.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MessageMarketSubscriptionData::MessageMarketSubscriptionData(Subscription sub, std::map<std::string, ObjectType> fields)
			: MessagePtr(Name("MarketDataEvents"), sub.correlationId())
		{
			for(std::map<std::string, ObjectType>::const_iterator iter = fields.begin(); iter != fields.end(); ++iter)
			{
				std::string str = iter->first;
				ObjectType field = iter->second;

				ElementPtr * elm = 0;

				switch(field.GetType())
				{
					case ObjectType::eDouble:
						elm = new ElementMarketDouble(str, field.ValueAsDouble());
						break;
					case ObjectType::eDatetime:
						elm = new ElementMarketDatetime(str, field.ValueAsDatetime());
						break;
					case ObjectType::eString:
						elm = new ElementMarketString(str, field.ValueAsString());
						break;
					case ObjectType::eInt:
						elm = new ElementMarketInt(str, field.ValueAsInt());
						break;
					case ObjectType::eBool:
						elm = new ElementMarketBool(str, field.ValueAsBool());
						break;
				}

				if(elm != 0)
					this->_fields[str] = elm;
			}
			this->_security = sub.security();
		}

		MessageMarketSubscriptionData::~MessageMarketSubscriptionData()
		{
			for(std::map<std::string, ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = iter->second;
				delete elm;
			}
		}

		const char* MessageMarketSubscriptionData::topicName() const
		{
			return ElementPtr::toCharPointer(this->_security);
		}

		size_t MessageMarketSubscriptionData::numElements() const
		{
			return this->_fields.size();
		}

		bool MessageMarketSubscriptionData::hasElement(const char* name, bool excludeNullElements) const
		{
			return this->_fields.find(name) != this->_fields.end();
		}

		ElementPtr * MessageMarketSubscriptionData::getElement(const char* name) const
		{
			for(std::map<std::string, ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				std::string key = iter->first;

				if(key == name)
				{
					ElementPtr * result = iter->second;
					return result;
				}
			}
			throw messageEx;
		}

		std::ostream& MessageMarketSubscriptionData::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "MarketDataEvents = {" << std::endl;
			
			for(std::map<std::string, ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = iter->second;
				elm->print(stream, level + 1, spacesPerLevel);
			}
			stream << "}" << std::endl;

			return stream;
		}

	}
}