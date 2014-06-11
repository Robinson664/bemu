//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayBarRequest/IntradayBarRequest.cs" company="Jordan Robinson">
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

    internal class IntradayBarRequest : Request
    {
        internal IntradayBarRequest(Service service)
        {
            this._service = service;
            //this._eventTypes = new IntradayBarRequestElementStringArray("TBD");
        }

        private IntradayBarRequestElementString _security;
        
        //private readonly IntradayBarRequestElementStringArray _eventTypes;
        private IntradayBarRequestElementString _eventType;
        
        private IntradayBarRequestElementTime _dtStart, _dtEnd;
        private IntradayBarRequestElementInt _intervalInMinutes;
        private IntradayBarRequestElementBool _gapFillInitialBar, _returnEids, _adjustmentNormalElement, _adjustmentAbnormalElement, _adjustmentSplitElement, _adjustmentFollowDPDF;

        private readonly Service _service;
        internal Service Service { get { return this._service; } }

        internal DateTime? DtStart { get { return this._dtStart.GetDate; } }
        internal DateTime? DtEnd { get { return this._dtEnd.GetDate; } }
        internal string Security { get { return this._security.GetValueAsString(); } }

        internal IEnumerable<DateTime> GetDateTimes()
        {
            if (!this._dtStart.GetDate.HasValue)
                throw new ArgumentException("Invalid startDate.  None specified.");

            else if (!this._dtEnd.GetDate.HasValue)
                throw new ArgumentException("Invalid endDate.  None specified.");

            else if (this._intervalInMinutes == null)
                throw new ArgumentException("Invalid interval.  None specified (despite A.2.8 in the documentation, interval is required).");

            int interval = this._intervalInMinutes.GetInt;
            if (interval < 1 || interval > 1440) //if less than one, the loop below will never terminate
                throw new ArgumentException("The interval must be an integer between 1 and 1440.  You entered " + interval.ToString());
            for (DateTime dtCurrent = this._dtStart.GetDate.Value; dtCurrent <= this._dtEnd.GetDate.Value; dtCurrent = dtCurrent.AddMinutes(interval))
            {
                yield return dtCurrent;
            }
        }

        public override void Set(string name, string elementValue)
        {
            switch (name)
            {
                case "security":
                    this._security = new IntradayBarRequestElementString(name, elementValue);
                    break;
                case "eventType":
                    //this._eventTypes.AddValue(elementValue);
                    this._eventType = new IntradayBarRequestElementString(name, elementValue);
                    break;
                default:
                    throw new ArgumentException("name not recognized.  case-sensitive.");
            }
        }

        public override void Set(string name, Datetime elementValue)
        {
            switch (name)
            {
                case "startDateTime":
                    this._dtStart = new IntradayBarRequestElementTime(name, elementValue);
                    break;
                case "endDateTime":
                    this._dtEnd = new IntradayBarRequestElementTime(name, elementValue);
                    break;
                default:
                    throw new ArgumentException("name not recognized.  case-sensitive.");
            }
        }

        public override void Set(string name, int elementValue)
        {
            switch (name)
            {
                case "interval":
                    this._intervalInMinutes = new IntradayBarRequestElementInt(name, elementValue);
                    break;
                default:
                    throw new ArgumentException("name not recognized.  case-sensitive.");
            }
        }

        public override void Set(string name, bool elementValue)
        {
            switch (name)
            {
                case "gapFillInitialBar":
                    this._gapFillInitialBar = new IntradayBarRequestElementBool(name, elementValue);
                    break;
                case "returnEids":
                    this._returnEids = new IntradayBarRequestElementBool(name, elementValue);
                    break;
                case "adjustmentNormal":
                    this._adjustmentNormalElement = new IntradayBarRequestElementBool(name, elementValue);
                    break;
                case "adjustmentAbnormal":
                    this._adjustmentAbnormalElement = new IntradayBarRequestElementBool(name, elementValue);
                    break;
                case "adjustmentSplit":
                    this._adjustmentSplitElement = new IntradayBarRequestElementBool(name, elementValue);
                    break;
                case "adjustmentFollowDPDF":
                    this._adjustmentFollowDPDF = new IntradayBarRequestElementBool(name, elementValue);
                    break;
                default:
                    throw new ArgumentException("name not recognized.  case-sensitive.");
            }
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("IntradayBarRequest = {{{0}", Environment.NewLine); //TODO: check this code (and also the c++ version) against the actual BB API

            Element[] elms = { this._security, this._eventType, this._dtStart, this._dtEnd, this._intervalInMinutes, this._gapFillInitialBar, 
                                 this._returnEids, this._adjustmentNormalElement,  this._adjustmentAbnormalElement, this._adjustmentSplitElement, this._adjustmentFollowDPDF };

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

    }
}
