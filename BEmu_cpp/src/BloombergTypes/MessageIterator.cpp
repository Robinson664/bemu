//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/MessageIterator.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Message.h"
#include "BloombergTypes/MessagePtr.h"
#include "BloombergTypes/MessageIterator.h"
#include "BloombergTypes/Event.h"
#include "BloombergTypes/EventPtr.h"
#include "BloombergTypes/ElementPtr.h"
#include <stack>

namespace BEmu
{
	MessageIterator::MessageIterator(const Event& evt)
	{
		this->_position = -1;

		boost::shared_ptr<EventPtr> evtP(evt.getEventPtr());
		//EventPtr * evtPtr = evt.getEventPtr();

		std::vector< boost::shared_ptr<MessagePtr> > list = evtP->getMessages();
		
		//for(std::vector<MessagePtr*>::const_iterator iter = list->begin(); iter != list->end(); ++iter)
		for(std::vector< boost::shared_ptr<MessagePtr> >::const_iterator iter = list.begin(); iter != list.end(); ++iter)
		{
			boost::shared_ptr<MessagePtr> msg = *iter;

			this->_listP.push_back(msg);
		}
	}

	MessageIterator::~MessageIterator() //this should delete all Elements and Messages within it
	{
		////I can't put the Element deletion code in the MessagePtr destructor because that gets called before the MessageIterator destructor
		////for(std::vector<MessagePtr*>::iterator iter = this->_listP.begin(); iter != this->_listP.end(); ++iter)
		//for(std::vector< boost::shared_ptr<MessagePtr> >::iterator iter = this->_listP.begin(); iter != this->_listP.end(); ++iter)
		//{
		//	boost::shared_ptr<MessagePtr> msg = *iter;

		//	//Delete all of the elements within the current Message.
		//	std::stack<ElementPtr> rootElements = msg->getRootElements();

		//	while(!rootElements.empty())
		//	{
		//		ElementPtr * root = rootElements.top();
		//		rootElements.pop();

		//		delete root;
		//	}
		//	msg->markRootElementsDeleted();

		//	//delete msg;
		//	//msg = 0;
		//}

		this->_listP.clear();
	}

	bool MessageIterator::next()
	{
		this->_position++;
		return this->_position < (int)(this->_listP.size());
	}

	bool MessageIterator::isValid() const
	{
		return this->_position >= 0 && this->_position < (int)(this->_listP.size());
	}

	Message MessageIterator::message(bool createClonable) const
	{
		boost::shared_ptr<MessagePtr> messageP = this->_listP.at(this->_position);
		Message msg(messageP);
		return msg;
	}
}