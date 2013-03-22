using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.IntradayBarRequest
{
    internal class RequestIntradayBar : Request
    {
        internal RequestIntradayBar(Service service)
        {
            this._service = service;
            this._eventTypes = new RequestIntradayBarElementStringArray("TBD");
        }

        private RequestIntradayBarElementString _security;
        private readonly RequestIntradayBarElementStringArray _eventTypes;
        private RequestIntradayBarElementTime _dtStart, _dtEnd;
        private RequestIntradayBarElementInt _intervalInMinutes;
        private RequestIntradayBarElementBool _gapFillInitialBar, _returnEids, _adjustmentNormalElement, _adjustmentAbnormalElement, _adjustmentSplitElement, _adjustmentFollowDPDF;

        private readonly Service _service;
        internal Service Service { get { return this._service; } }

        internal DateTime? DtStart { get { return this._dtStart.GetDate; } }
        internal DateTime? DtEnd { get { return this._dtEnd.GetDate; } }

        internal IEnumerable<DateTime> GetDateTimes()
        {
            if (this._dtStart.GetDate.HasValue && this._dtEnd.GetDate.HasValue)
            {
                int interval = this._intervalInMinutes.GetInt;
                if (interval < 1) //if less than one, the loop below will never terminate
                    interval = 1; //default = 1 (A.2.8)
                for (DateTime dtCurrent = this._dtStart.GetDate.Value; dtCurrent <= this._dtEnd.GetDate.Value; dtCurrent = dtCurrent.AddMinutes(interval))
                {
                    yield return dtCurrent;
                }
            }
        }

        public override void Set(string name, string elementValue)
        {
            var upper = name.ToUpper();
            switch (upper)
            {
                case "SECURITY":
                    this._security = new RequestIntradayBarElementString(name, elementValue);
                    break;
                case "EVENTTYPE":
                    this._eventTypes.AddValue(elementValue);
                    break;
            }
        }

        public override void Set(string name, Datetime elementValue)
        {
            var upper = name.ToUpper();
            switch (upper)
            {
                case "STARTDATETIME":
                    this._dtStart = new RequestIntradayBarElementTime(name, elementValue);
                    break;
                case "ENDDATETIME":
                    this._dtEnd = new RequestIntradayBarElementTime(name, elementValue);
                    break;
            }
        }

        public override void Set(string name, int elementValue)
        {
            var upper = name.ToUpper();
            switch (upper)
            {
                case "INTERVAL":
                    this._intervalInMinutes = new RequestIntradayBarElementInt(name, elementValue);
                    break;
            }
        }

        public override void Set(string name, bool elementValue)
        {
            var upper = name.ToUpper();
            switch (upper)
            {
                case "GAPFILLINITIALBAR":
                    this._gapFillInitialBar = new RequestIntradayBarElementBool(name, elementValue);
                    break;
                case "RETURNEIDS":
                    this._returnEids = new RequestIntradayBarElementBool(name, elementValue);
                    break;
                case "ADJUSTMENTNORMAL":
                    this._adjustmentNormalElement = new RequestIntradayBarElementBool(name, elementValue);
                    break;
                case "ADJUSTMENTABNORMAL":
                    this._adjustmentAbnormalElement = new RequestIntradayBarElementBool(name, elementValue);
                    break;
                case "ADJUSTMENTSPLIT":
                    this._adjustmentSplitElement = new RequestIntradayBarElementBool(name, elementValue);
                    break;
                case "ADJUSTMENTFOLLOWDPDF":
                    this._adjustmentFollowDPDF = new RequestIntradayBarElementBool(name, elementValue);
                    break;
            }
        }

    }
}
