//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/SubscriptionList.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "bemu_headers.h"
#include "BloombergTypes/CorrelationId.h"
#include "BloombergTypes/Subscription.h"
#include <vector>

namespace BEmu
{
	class SubscriptionList
	{
		private:
			std::vector<Subscription> * _subs;

		public:
			DLL_EXPORT SubscriptionList();
			DLL_EXPORT ~SubscriptionList();
			
			DLL_EXPORT SubscriptionList(const SubscriptionList& original);
			DLL_EXPORT SubscriptionList& operator=(const SubscriptionList& rhs);
			
			DLL_EXPORT int add(const char* topic, const char* fields, const char* options, const CorrelationId& correlationId);
			void add(Subscription sub);

			std::vector<Subscription> * list() const;
	};
}