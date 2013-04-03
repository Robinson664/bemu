//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/MessageMarketSessionOpened.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.MarketDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class MessageMarketSessionOpened : Message
    {
        internal MessageMarketSessionOpened() : base(new Name("SessionStarted"), null, null)
        {
        }

        public override string TopicName { get { return ""; } }

        public override IEnumerable<Element> Elements
        {
            get { throw new NotImplementedException(); }
        }
    }
}
