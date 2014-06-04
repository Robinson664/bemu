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
		MarketMessageSubscriptionStarted::MarketMessageSubscriptionStarted(const Subscription& sub)
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
     //               this->_exceptionsNull = new MarketElementNull("exceptions"); //deleted in destructor
					//this->_exceptionsBadFields = 0;

					this->_exceptionsNull = boost::shared_ptr<MarketElementNull>(new MarketElementNull("exceptions"));
					this->_exceptionsBadFields = boost::shared_ptr<MarketElementExceptionsArray>();

					this->_isNull_exceptionsNull = false;
					this->_isNull_exceptionsBadFields = true;
				}
                else
				{
					//this->_exceptionsNull = 0;
     //               this->_exceptionsBadFields = new MarketElementExceptionsArray(badFields); //deleted in destructor

					this->_exceptionsNull = boost::shared_ptr<MarketElementNull>();
					this->_exceptionsBadFields = boost::shared_ptr<MarketElementExceptionsArray>(new MarketElementExceptionsArray(badFields));

					this->_isNull_exceptionsNull = true;
					this->_isNull_exceptionsBadFields = false;
				}
			}
		}

		MarketMessageSubscriptionStarted::~MarketMessageSubscriptionStarted()
		{
			//if(this->_exceptionsNull != 0)
			//{
			//	delete this->_exceptionsNull;
			//	this->_exceptionsNull = 0;
			//}

			//if(this->_exceptionsBadFields != 0)
			//{
			//	delete this->_exceptionsBadFields;
			//	this->_exceptionsBadFields = 0;
			//}
		}

		//std::stack<ElementPtr*> MarketMessageSubscriptionStarted::getRootElements() const
		std::stack< boost::shared_ptr<ElementPtr> > MarketMessageSubscriptionStarted::getRootElements() const
		{
			std::stack< boost::shared_ptr<ElementPtr> > result;

			//if(this->_exceptionsNull != 0)
			if(!this->_isNull_exceptionsNull)
				result.push( boost::dynamic_pointer_cast<ElementPtr>(this->_exceptionsNull) );

			//if(this->_exceptionsBadFields != 0)
			if(!this->_isNull_exceptionsBadFields)
				result.push( boost::dynamic_pointer_cast<ElementPtr>(this->_exceptionsBadFields) );

			return result;
		}

		void MarketMessageSubscriptionStarted::markRootElementsDeleted()
		{
			//this->_exceptionsNull = 0;
			//this->_exceptionsBadFields = 0;
		}

		//ElementPtr * MarketMessageSubscriptionStarted::firstElement() const
		boost::shared_ptr<ElementPtr> MarketMessageSubscriptionStarted::firstElement() const
		{
			//if(this->_exceptionsNull != 0)
			if(!this->_isNull_exceptionsNull)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_exceptionsNull);

			//else if(this->_exceptionsBadFields != 0)
			else if(!this->_isNull_exceptionsBadFields)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_exceptionsBadFields);

			else
				throw messageEx;
		}

		bool MarketMessageSubscriptionStarted::hasElement(const char* name, bool excludeNullElements) const
		{
			//if(this->_exceptionsNull != 0 && this->_exceptionsNull->name() == name)
			if(!this->_isNull_exceptionsNull && this->_exceptionsNull->name() == name)
				return true;

			//else if(this->_exceptionsBadFields != 0 && this->_exceptionsBadFields->name() == name)
			else if(!this->_isNull_exceptionsBadFields && this->_exceptionsBadFields->name() == name)
				return true;

			return false;
		}

		//ElementPtr * MarketMessageSubscriptionStarted::getElement(const char* name) const
		boost::shared_ptr<ElementPtr> MarketMessageSubscriptionStarted::getElement(const char* name) const
		{
			//if(this->_exceptionsNull != 0 && this->_exceptionsNull->name() == name)
			if(!this->_isNull_exceptionsNull && this->_exceptionsNull->name() == name)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_exceptionsNull);

			//else if(this->_exceptionsBadFields != 0 && this->_exceptionsBadFields->name() == name)
			else if(!this->_isNull_exceptionsBadFields && this->_exceptionsBadFields->name() == name)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_exceptionsBadFields);

			else
				throw messageEx;
		}

		size_t MarketMessageSubscriptionStarted::numElements() const
		{
			return 1;
		}

		//ElementPtr * MarketMessageSubscriptionStarted::asElement() const
		boost::shared_ptr<ElementPtr> MarketMessageSubscriptionStarted::asElement() const
		{
			throw messageEx;
		}

		const char* MarketMessageSubscriptionStarted::topicName() const
		{
			return this->_topicName.c_str();
		}

		std::ostream& MarketMessageSubscriptionStarted::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
            //if (this->_exceptionsNull != 0)
			if(!this->_isNull_exceptionsNull)
			{
				stream << "SubscriptionStarted = {" << std::endl << "}" << std::endl;
			}
			//else if(this->_exceptionsBadFields != 0)
			else if(!this->_isNull_exceptionsBadFields)
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