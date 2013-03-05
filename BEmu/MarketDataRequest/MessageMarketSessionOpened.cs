using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.MarketDataRequest
{
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
