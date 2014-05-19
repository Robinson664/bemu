//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayTickRequest/IntradayTickMessage.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.IntradayTickRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class IntradayTickMessage : Message
    {
        private readonly IntradayTickElementDataParent _parent;
        private readonly IntradayTickElementResponseError _responseError;
        private readonly bool _isResponseError;

        internal IntradayTickMessage(CorrelationID corr, Service service, SortedDictionary<DateTime, Types.Tuple3<string, double, int>> ticks, bool includeConditionCodes) :
            base(new Name("IntradayTickResponse"), corr, service)
        {
            this._parent = new IntradayTickElementDataParent(ticks, includeConditionCodes);
            this._responseError = null;
            this._isResponseError = false;
        }

        internal IntradayTickMessage(CorrelationID corr, Service service) :
            base(new Name("IntradayTickResponse"), corr, service)
        {
            this._parent = null;
            this._responseError = new IntradayTickElementResponseError();
            this._isResponseError = true;
        }

        public override object this[string name, int index] { get { return null; } }
        public override string TopicName { get { return ""; } }
        public override int NumElements { get { return 1; } }
        public override Element AsElement { get { return new IntradayTickElementReference(this); } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                if (this._isResponseError)
                    yield return this._responseError;
                else
                    yield return this._parent;
            }
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.Append("IntradayTickResponse (choice) = {" + Environment.NewLine);

            foreach (var item in this.Elements)
            {
                result.Append(item.PrettyPrint(1));
            }

            result.Append("}");

            return result.ToString();
        }
    }
}
