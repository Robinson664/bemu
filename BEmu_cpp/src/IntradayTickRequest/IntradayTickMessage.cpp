//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/IntradayTickMessage.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/IntradayTickMessage.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "BloombergTypes/CorrelationId.h"
#include "BloombergTypes/Service.h"
#include "IntradayTickRequest/IntradayTickElementDataParent.h"
#include "IntradayTickRequest/IntradayTickElementResponseError.h"
#include "IntradayTickRequest/IntradayTickElementTuple3.h"
#include "IntradayTickRequest/IntradayTickElement.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		//makes copies of the arguments
		IntradayTickMessage::IntradayTickMessage(const CorrelationId& corr, const Service& service, std::map<Datetime, boost::shared_ptr<IntradayTickElementTuple3> > *ticks, bool includeConditionCodes) :
			MessagePtr(Name("IntradayTickResponse"), corr),
			_parent(new IntradayTickElementDataParent(ticks, includeConditionCodes)),
			_responseError()
		{
			//this->_parent = new IntradayTickElementDataParent(ticks, includeConditionCodes); //deleted in destructor
			//this->_responseError = 0;
			this->_isResponseError = false;
		}

		IntradayTickMessage::IntradayTickMessage(const CorrelationId& corr, const Service& service) :
			MessagePtr(Name("IntradayTickResponse"), corr),
			_parent(),
			_responseError(new IntradayTickElementResponseError())
		{
			//this->_parent = 0;
			//this->_responseError = new IntradayTickElementResponseError(); //deleted in destructor
			this->_isResponseError = true;
		}

		IntradayTickMessage::~IntradayTickMessage()
		{
			//if(this->_parent != 0)
			//{
			//	delete this->_parent;
			//	this->_parent = 0;
			//}

			//if(this->_responseError != 0)
			//{
			//	delete this->_responseError;
			//	this->_responseError = 0;
			//}
		}

		//std::stack<ElementPtr*> IntradayTickMessage::getRootElements() const
		std::stack< boost::shared_ptr<ElementPtr> > IntradayTickMessage::getRootElements() const
		{
			//std::stack<ElementPtr*> result;
			std::stack< boost::shared_ptr<ElementPtr> > result;

			if(this->_isResponseError)
				result.push( boost::dynamic_pointer_cast<ElementPtr>(this->_responseError) );
			else
				result.push( boost::dynamic_pointer_cast<ElementPtr>(this->_parent) );

			return result;
		}

		void IntradayTickMessage::markRootElementsDeleted()
		{
			//this->_parent = 0;
			//this->_responseError = 0;
		}

		//ElementPtr * IntradayTickMessage::getElement(const char* name) const
		boost::shared_ptr<ElementPtr> IntradayTickMessage::getElement(const char* name) const
		{
			if(this->_isResponseError && strncmp(name, "responseError", 14) == 0)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_responseError);

			else if(!this->_isResponseError && strncmp(name, "tickData", 9) == 0)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_parent);

			else
				throw messageEx;
		}

		bool IntradayTickMessage::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(this->_isResponseError && strncmp(name, "responseError", 14) == 0) ||
				(!this->_isResponseError && strncmp(name, "tickData", 9) == 0);
		}

		//ElementPtr* IntradayTickMessage::firstElement() const
		boost::shared_ptr<ElementPtr> IntradayTickMessage::firstElement() const
		{
			if(this->_isResponseError)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_responseError);
			else
				return boost::dynamic_pointer_cast<ElementPtr>(this->_parent);
		}

		const char* IntradayTickMessage::topicName() const
		{
			return "";
		}

		size_t IntradayTickMessage::numElements() const
		{
			return 1;
		}

		//ElementPtr * IntradayTickMessage::asElement() const
		boost::shared_ptr<ElementPtr> IntradayTickMessage::asElement() const
		{
			boost::shared_ptr<IntradayTickElement> elm(new IntradayTickElement(*this));
			return boost::dynamic_pointer_cast<ElementPtr>(elm);

			//const IntradayTickMessage msg = *this;
			//ElementPtr * resultP = new IntradayTickElement(msg); //TODO: not deleted?
			//return resultP;
		}

		std::ostream& IntradayTickMessage::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "IntradayTickResponse = {" << std::endl;
			
			if(this->_isResponseError)
				this->_responseError->print(stream, level + 1, spacesPerLevel);
			else
				this->_parent->print(stream, level + 1, spacesPerLevel);

			stream << '}' << std::endl;
			return stream;
		}

	}
}