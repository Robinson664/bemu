//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/EventQueue.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    public class EventQueue
    {
        public EventQueue()
        {
        }

        internal Session Session { get; set; }


        public Event NextEvent()
        {
            return this.Session.NextEvent();
        }

        public Event NextEvent(long timeoutMillis)
        {
            return this.Session.NextEvent(timeoutMillis);
        }

        public void Purge()
        {
            throw new NotImplementedException();
        }

        public Event TryNextEvent()
        {
            return this.NextEvent();
        }

    }
}
