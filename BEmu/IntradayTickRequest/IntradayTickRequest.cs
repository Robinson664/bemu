//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayTickRequest/IntradayTickRequest.cs" company="Jordan Robinson">
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

    internal class IntradayTickRequest : Request
    {
        private IntradayTickRequestElementString _security;
        private readonly IntradayTickRequestElementStringArray _eventTypes;
        private IntradayTickRequestElementTime _timeStart, _timeEnd;

        private IntradayTickRequestElementBool _includeConditionCodes, _includeNonPlottableEvents, _includeExchangeCodes, _returnEids,
            _includeBrokerCodes, _includeRpsCodes, _includeBicMicCodes;

        private readonly Service _service;
        internal Service Service { get { return this._service; } }

        internal IntradayTickRequest(Service service)
        {
            this._eventTypes = new IntradayTickRequestElementStringArray("eventTypes");
            this._service = service;
        }

        internal IEnumerable<DateTime> GetDates()
        {
            DateTime dtStart = this._timeStart.GetDate.GetValueOrDefault(DateTime.Today.AddDays(-1));
            DateTime dtOldest = DateTime.Today.AddDays(-140); //intraday tick data is stored only for 140 days (documentation section 7.2.3)
            if (dtStart < dtOldest) dtStart = dtOldest;

            DateTime dtEnd = this.DtEnd.GetValueOrDefault(DateTime.Now);
            while (dtStart < dtEnd)
            {
                yield return dtStart;
                dtStart = dtStart.Add(Types.RandomDataGenerator.IntradayTickInterval());
            }
        }

        internal bool IncludeConditionCodes { get { return this._includeConditionCodes.GetBool; } }

        internal string Security { get { return this._security.Security; } }
        internal DateTime? DtStart { get { return this._timeStart.GetDate; } }
        internal DateTime? DtEnd { get { return this._timeEnd.GetDate; } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._security;
                yield return this._eventTypes;
                yield return this._timeStart;
                yield return this._timeEnd;

                if (this._includeConditionCodes != null) yield return this._includeConditionCodes;
                if (this._includeNonPlottableEvents != null) yield return this._includeNonPlottableEvents;
                if (this._includeExchangeCodes != null) yield return this._includeExchangeCodes;
                if (this._returnEids != null) yield return this._returnEids;
                if (this._includeBrokerCodes != null) yield return this._includeBrokerCodes;
                if (this._includeRpsCodes != null) yield return this._includeRpsCodes;
                if (this._includeBicMicCodes != null) yield return this._includeBicMicCodes;
            }
        }

        public override Element this[string elementName]
        {
            get
            {
                if (this._security.Name.ToString() == elementName)
                    return this._security;
                else
                    throw new NotImplementedException("BEmu.IntradayTickDataRequest.RequestReference: public Element this[string elementName] not supported");
            }
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("IntradayTickRequest = {{{0}", Environment.NewLine);

            Element[] elms = { this._security, this._timeStart, this._timeEnd, this._eventTypes, this._includeConditionCodes, this._includeNonPlottableEvents,
                                 this._includeExchangeCodes, this._returnEids, this._includeBrokerCodes, this._includeRpsCodes, this._includeBicMicCodes};

            for (int i = 0; i < elms.Length; i++)
            {
                Element current = elms[i];

                if (current != null)
                {
                    bool quotes = current == this._security;
                    result.Append(current.PrettyPrint(1, quotes));
                }
            }

            result.AppendLine("}");
            return result.ToString();
        }

        #region OVERRIDES
        public override void Append(string name, string elementValue)
        {
            switch (name)
            {
                case "eventTypes":
                    this._eventTypes.AddValue(elementValue);
                    break;
                default:
                    throw new ArgumentException(string.Format("BEmu.RequestIntradayTick.Append: Element name {0} not supported. Names are case-sensitive.", name));
            }
        }

        public override void Set(string name, string elementValue)
        {
            switch (name)
            {
                case "security":
                    this._security = new IntradayTickRequestElementString(name, elementValue);
                    break;
                default:
                    throw new ArgumentException("Names are case-sensitive");
            }
        }

        public override void Set(string name, Datetime elementValue)
        {
            switch (name)
            {
                case "startDateTime":
                    this._timeStart = new IntradayTickRequestElementTime(name, elementValue);
                    break;
                case "endDateTime":
                    this._timeEnd = new IntradayTickRequestElementTime(name, elementValue);
                    break;
                default:
                    throw new ArgumentException("Names are case-sensitive");
            }
        }

        public override void Set(string name, bool elementValue)
        {
            switch (name)
            {
                case "includeConditionCodes":
                    this._includeConditionCodes = new IntradayTickRequestElementBool(name, elementValue);
                    break;
                case "includeNonPlottableEvents":
                    this._includeNonPlottableEvents = new IntradayTickRequestElementBool(name, elementValue);
                    break;
                case "includeExchangeCodes":
                    this._includeExchangeCodes = new IntradayTickRequestElementBool(name, elementValue);
                    break;
                case "returnEids":
                    this._returnEids = new IntradayTickRequestElementBool(name, elementValue);
                    break;
                case "includeBrokerCodes":
                    this._includeBrokerCodes = new IntradayTickRequestElementBool(name, elementValue);
                    break;
                case "includeRpsCodes":
                    this._includeRpsCodes = new IntradayTickRequestElementBool(name, elementValue);
                    break;
                case "includeBicMicCodes":
                    this._includeBicMicCodes = new IntradayTickRequestElementBool(name, elementValue);
                    break;
                default:
                    throw new ArgumentException("Names are case-sensitive");
            }
        }
        #endregion


    }
}
