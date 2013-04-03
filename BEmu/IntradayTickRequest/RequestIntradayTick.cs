//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayTickRequest/RequestIntradayTick.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayTickRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class RequestIntradayTick : Request
    {
        private RequestIntradayTickElementString _security;
        private readonly RequestIntradayTickElementStringArray _eventTypes;
        private RequestIntradayTickElementTime _timeStart, _timeEnd;

        private RequestIntradayTickElementBool _includeConditionCodes, _includeNonPlottableEvents, _includeExchangeCodes, _returnEids,
            _includeBrokerCodes, _includeRpsCodes, _includeBicMicCodes;

        private readonly Service _service;
        internal Service Service { get { return this._service; } }

        internal RequestIntradayTick(Service service)
        {
            this._eventTypes = new RequestIntradayTickElementStringArray("eventTypes");
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
                if (this._security.Name.ToString().ToLower() == elementName.ToLower())
                    return this._security;
                else
                    throw new NotImplementedException("BEmu.IntradayTickDataRequest.RequestReference: public Element this[string elementName] not supported");
            }
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("IntradayTickRequest = {{{0}", Environment.NewLine);

            if (this._security != null)
                result.Append(this._security.PrettyPrint(1));

            if (this._eventTypes != null)
                result.Append(this._eventTypes.PrettyPrint(1));

            if (this._timeStart != null)
                result.Append(this._timeStart.PrettyPrint(1));

            if (this._timeEnd != null)
                result.Append(this._timeEnd.PrettyPrint(1));

            if (this._includeConditionCodes != null)
                result.Append(this._includeConditionCodes.PrettyPrint(1));

            if (this._includeNonPlottableEvents != null)
                result.Append(this._includeNonPlottableEvents.PrettyPrint(1));

            if (this._includeExchangeCodes != null)
                result.Append(this._includeExchangeCodes.PrettyPrint(1));

            if (this._returnEids != null)
                result.Append(this._returnEids.PrettyPrint(1));

            if (this._includeBrokerCodes != null)
                result.Append(this._includeBrokerCodes.PrettyPrint(1));

            if (this._includeRpsCodes != null)
                result.Append(this._includeRpsCodes.PrettyPrint(1));

            if (this._includeBicMicCodes != null)
                result.Append(this._includeBicMicCodes.PrettyPrint(1));

            result.Append("}");

            return result.ToString();
        }

        #region OVERRIDES
        public override void Append(string name, string elementValue)
        {
            switch (name.ToLower())
            {
                case "eventtypes":
                    this._eventTypes.AddValue(elementValue);
                    break;
                default:
                    throw new ArgumentException(string.Format("BEmu.RequestIntradayTick.Append: Element name {0} not supported", name));
            }
        }

        public override void Set(string name, string elementValue)
        {
            var upper = name.ToUpper();
            switch (upper)
            {
                case "SECURITY":
                    this._security = new RequestIntradayTickElementString(name, elementValue);
                    break;
            }
        }

        public override void Set(string name, Datetime elementValue)
        {
            var upper = name.ToUpper();
            switch (upper)
            {
                case "STARTDATETIME":
                    this._timeStart = new RequestIntradayTickElementTime(name, elementValue);
                    break;
                case "ENDDATETIME":
                    this._timeEnd = new RequestIntradayTickElementTime(name, elementValue);
                    break;
            }
        }

        public override void Set(string name, bool elementValue)
        {
            var upper = name.ToUpper();
            switch (upper)
            {
                case "INCLUDECONDITIONCODES":
                    this._includeConditionCodes = new RequestIntradayTickElementBool(name, elementValue);
                    break;
                case "INCLUDENONPLOTTABLEEVENTS":
                    this._includeNonPlottableEvents = new RequestIntradayTickElementBool(name, elementValue);
                    break;
                case "INCLUDEEXCHANGECODES":
                    this._includeExchangeCodes = new RequestIntradayTickElementBool(name, elementValue);
                    break;
                case "RETURNEIDS":
                    this._returnEids = new RequestIntradayTickElementBool(name, elementValue);
                    break;
                case "INCLUDEBROKERCODES":
                    this._includeBrokerCodes = new RequestIntradayTickElementBool(name, elementValue);
                    break;
                case "INCLUDERPSCODES":
                    this._includeRpsCodes = new RequestIntradayTickElementBool(name, elementValue);
                    break;
                case "INCLUDEBICMICCODES":
                    this._includeBicMicCodes = new RequestIntradayTickElementBool(name, elementValue);
                    break;
            }
        }
        #endregion


    }
}
