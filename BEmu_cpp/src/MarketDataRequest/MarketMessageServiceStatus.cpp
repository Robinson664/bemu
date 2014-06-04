//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MarketMessageServiceStatus.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MarketMessageServiceStatus.h"
#include "MarketDataRequest/MarketElementString.h"
#include "MarketDataRequest/MarketElementServiceStatus.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MarketMessageServiceStatus::MarketMessageServiceStatus(const CorrelationId& corr) : 
			MessagePtr(Name("ServiceOpened"), corr),
			_serviceName(new MarketElementString("serviceName", "//blp/mktdata"))
		{
			//this->_serviceName = new MarketElementString("serviceName", "//blp/mktdata"); //deleted in destructor
		}

		MarketMessageServiceStatus::MarketMessageServiceStatus(const MarketMessageServiceStatus& arg) :
			MessagePtr(Name("ServiceOpened"), arg.correlationId()),
			_serviceName(arg._serviceName)
		{
			//this->_correlationId = arg._correlationId;
			//this->_messageType = arg._messageType;
			//this->_serviceName = arg._serviceName;
		}

		MarketMessageServiceStatus::~MarketMessageServiceStatus()
		{
			//delete this->_serviceName;
			//this->_serviceName = 0;
		}

		//std::stack<ElementPtr*> MarketMessageServiceStatus::getRootElements() const
		std::stack< boost::shared_ptr<ElementPtr> > MarketMessageServiceStatus::getRootElements() const
		{
			//std::stack<ElementPtr*> result;
			std::stack< boost::shared_ptr<ElementPtr> > result;

			//if(this->_serviceName != 0)
			result.push( boost::dynamic_pointer_cast<ElementPtr>(this->_serviceName) );

			return result;
		}

		void MarketMessageServiceStatus::markRootElementsDeleted()
		{
			//this->_serviceName = 0;
		}

		//ElementPtr * MarketMessageServiceStatus::firstElement() const
		boost::shared_ptr<ElementPtr> MarketMessageServiceStatus::firstElement() const
		{
			return boost::dynamic_pointer_cast<ElementPtr>(this->_serviceName);

			//return this->_serviceName;
		}

		size_t MarketMessageServiceStatus::numElements() const
		{
			return 1;
		}

		const char* MarketMessageServiceStatus::topicName() const
		{
			return "";
		}

		//ElementPtr * MarketMessageServiceStatus::asElement() const
		boost::shared_ptr<ElementPtr> MarketMessageServiceStatus::asElement() const
		{
			//const MarketMessageServiceStatus * ptr = this;
			//return new MarketElementServiceStatus(ptr); //TODO: delete

			boost::shared_ptr<MarketMessageServiceStatus> elm( new MarketMessageServiceStatus(*this) );
			boost::shared_ptr<ElementPtr> result(boost::dynamic_pointer_cast<ElementPtr>(elm));

			return result;
		}

		std::ostream& MarketMessageServiceStatus::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "ServiceOpened = {" << std::endl;
			this->_serviceName->print(stream, level + 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}
	}
}