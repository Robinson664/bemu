//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayBarRequest/MessageIntradayBar.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayBarRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class MessageIntradayBar : Message
    {
        private readonly ElementBarData _parent;

        internal MessageIntradayBar(CorrelationID corr, IEnumerable<BarTickDataType> bars, Service service) :
            base(new Name("IntradayBarResponse"), corr, service)
        {
            this._parent = new ElementBarData(bars);
        }

        public override IEnumerable<Element> Elements { get { yield return this._parent; } }
        public override object this[string name, int index] { get { return null; } }
        public override string TopicName { get { return ""; } }
        public override int NumElements { get { return 1; } }

        //public override Element AsElement { get { return new ElementReference(this); } }
        

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.Append("IntradayBarResponse (choice) = {" + Environment.NewLine);
            result.Append(this._parent.PrettyPrint(1));
            result.Append("}");

            return result.ToString();
        }
    }
}
