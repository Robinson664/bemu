//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayBarRequest/IntradayBarMessage.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.IntradayBarRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class IntradayBarMessage : Message
    {
        private readonly IntradayBarElementData _parent;
        private readonly IntradayBarElementResponseError _responseError;
        private readonly bool _isResponseError;

        /// <summary>
        /// Use this for security errors
        /// </summary>
        /// <param name="corr"></param>
        /// <param name="service"></param>
        internal IntradayBarMessage(CorrelationID corr, Service service, string security) :
            base(new Name("IntradayBarResponse"), corr, service)
        {
            this._responseError = new IntradayBarElementResponseError(security);
            this._parent = null;
            this._isResponseError = true;
        }

        /// <summary>
        /// Use this for regular securities (no security error)
        /// </summary>
        /// <param name="corr"></param>
        /// <param name="bars"></param>
        /// <param name="service"></param>
        internal IntradayBarMessage(CorrelationID corr, Service service, IEnumerable<IntradayBarTickDataType> bars) :
            base(new Name("IntradayBarResponse"), corr, service)
        {
            this._parent = new IntradayBarElementData(bars);
            this._responseError = null;
            this._isResponseError = false;
        }

        public override object this[string name, int index] { get { return null; } }
        public override string TopicName { get { return ""; } }
        public override int NumElements { get { return 1; } }

        //public override Element AsElement { get { return new ElementReference(this); } }

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
            result.Append("IntradayBarResponse (choice) = {" + Environment.NewLine);

            foreach (var item in this.Elements)
            {
                result.Append(item.PrettyPrint(1));
            }

            result.Append("}");

            return result.ToString();
        }
    }
}
