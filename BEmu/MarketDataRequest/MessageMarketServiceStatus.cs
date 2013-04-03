//------------------------------------------------------------------------------
// <copyright project="BEmu" file="MarketDataRequest/MessageMarketServiceStatus.cs" company="Jordan Robinson">
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

    internal class MessageMarketServiceStatus : Message
    {
        private readonly ElementMarketString _serviceName;

        internal MessageMarketServiceStatus(CorrelationID corr) : base(new Name("ServiceOpened"), corr, null)
        {
            this._serviceName = new ElementMarketString("serviceName", "//blp/mktdata");
        }

        public override int NumElements { get { return 1; } }
        public override string TopicName { get { return ""; } }
        public override IEnumerable<Element> Elements { get { yield return this._serviceName; } }
        public override Element AsElement { get { return new ElementMarketServiceStatus(this); } }
        
        public override object this[string name, int index]
        {
            get
            {
                if (name.ToUpper() == this._serviceName.Name.ToString().ToUpper())
                {
                    if (index == 0)
                        return this._serviceName.GetValue();
                }
                return base[name, index];
            }
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("{0} = {{{1}", this.MessageType.ToString(), Environment.NewLine);
            result.Append(this._serviceName.PrettyPrint(1));
            result.Append("}" + Environment.NewLine);
            return result.ToString();
        }

    }
}
