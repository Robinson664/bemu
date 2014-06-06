//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/api_selector.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

//comment out the following line to use the actual Bloomberg API
#define USE_BEMU_API

#ifdef USE_BEMU_API

	#include "BloombergTypes/Name.h"
	#include "BloombergTypes/CorrelationID.h"
	#include "BloombergTypes/Session.h"
	#include "BloombergTypes/MessageIterator.h"
	#include "BloombergTypes/Event.h"
	#include "BloombergTypes/SessionOptions.h"
	#include "BloombergTypes/Request.h"
	#include "BloombergTypes/Datetime.h"
	#include "BloombergTypes/Element.h"
	#include "BloombergTypes/Message.h"
	#include "BloombergTypes/Service.h"
	#include "BloombergTypes/SubscriptionList.h"
	#include "BloombergTypes/EventHandler.h"

	using namespace BEmu;

#else

	#include "blpapi_name.h"
	#include "blpapi_correlationid.h"
	#include "blpapi_session.h" //also defines EventHandler
	#include "blpapi_event.h" //also defines MessageIterator
	#include "blpapi_sessionoptions.h"
	#include "blpapi_request.h"
	#include "blpapi_datetime.h"
	#include "blpapi_service.h"
	#include "blpapi_element.h"
	#include "blpapi_message.h"
	#include "blpapi_subscriptionlist.h"

	using namespace BloombergLP::blpapi;

#endif