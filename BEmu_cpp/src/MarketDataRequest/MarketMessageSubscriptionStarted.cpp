//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MarketMessageSubscriptionStarted.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MarketMessageSubscriptionStarted.h"
#include <vector>
#include "Types/Rules.h"

#include "MarketDataRequest/MarketElementNull.h"
#include "MarketDataRequest/MarketElementExceptionsArray.h"
#include "MarketDataRequest/MarketElementSubscriptionStarted.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MarketMessageSubscriptionStarted::MarketMessageSubscriptionStarted(Subscription sub)
			: MessagePtr(Name("SubscriptionStarted"), sub.correlationId())
		{
            this->_correlationId = sub.correlationId();
			this->_topicName = sub.security();
			
            { //deal with bad fields
				std::vector<std::string> badFields, fields = sub.fieldList();

				for (int i = fields.size() - 1; i >= 0; i--)
				{
					if(Rules::IsBadField(fields.at(i)))
					{
						badFields.push_back(fields.at(i));
						fields.erase(fields.begin() + i);
					}
				}

				if (badFields.size() == 0)
				{
                    this->_exceptionsNull = new MarketElementNull("exceptions");
					this->_exceptionsBadFields = 0;
				}
                else
				{
					this->_exceptionsNull = 0;
                    this->_exceptionsBadFields = new MarketElementExceptionsArray(badFields);
				}
			}
		}

		MarketMessageSubscriptionStarted::~MarketMessageSubscriptionStarted()
		{
			delete this->_exceptionsNull;
			this->_exceptionsNull = 0;

			delete this->_exceptionsBadFields;
			this->_exceptionsBadFields = 0;
		}

		std::stack<ElementPtr*> MarketMessageSubscriptionStarted::getRootElements() const
		{
			std::stack<ElementPtr*> result;

			if(this->_exceptionsNull != 0)
				result.push(this->_exceptionsNull);

			if(this->_exceptionsBadFields != 0)
				result.push(this->_exceptionsBadFields);

			return result;
		}

		ElementPtr * MarketMessageSubscriptionStarted::firstElement() const
		{
			if(this->_exceptionsNull != 0)
				return this->_exceptionsNull;

			else if(this->_exceptionsBadFields != 0)
				return this->_exceptionsBadFields;

			else
				throw messageEx;
		}

		bool MarketMessageSubscriptionStarted::hasElement(const char* name, bool excludeNullElements) const
		{
			if(this->_exceptionsNull != 0 && this->_exceptionsNull->name() == name)
				return true;

			else if(this->_exceptionsBadFields != 0 && this->_exceptionsBadFields->name() == name)
				return true;

			return false;
		}

		ElementPtr * MarketMessageSubscriptionStarted::getElement(const char* name) const
		{
			if(this->_exceptionsNull != 0 && this->_exceptionsNull->name() == name)
				return this->_exceptionsNull;

			else if(this->_exceptionsBadFields != 0 && this->_exceptionsBadFields->name() == name)
				return this->_exceptionsBadFields;

			else
				throw messageEx;
		}

		size_t MarketMessageSubscriptionStarted::numElements() const
		{
			return 1;
		}

		ElementPtr * MarketMessageSubscriptionStarted::asElement() const
		{
			throw messageEx;
		}

		const char* MarketMessageSubscriptionStarted::topicName() const
		{
			return ElementPtr::toCharPointer(this->_topicName);
		}

		std::ostream& MarketMessageSubscriptionStarted::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
            if (this->_exceptionsNull != 0)
			{
				stream << "SubscriptionStarted = {" << std::endl << "}" << std::endl;
			}
			else if(this->_exceptionsBadFields != 0)
			{
				stream << "SubscriptionStarted = {" << std::endl;
				this->_exceptionsBadFields->print(stream, level + 1, spacesPerLevel);
				stream << "}" << std::endl;
			}
			else
				throw messageEx;

			return stream;
		}

	}
}