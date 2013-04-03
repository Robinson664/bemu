//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayTickRequest/RequestIntradayTickElementTime.cs" company="Jordan Robinson">
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

    internal class RequestIntradayTickElementTime : RequestIntradayTickElementString
    {
        private readonly DateTime? _instance;

        internal RequestIntradayTickElementTime(string elementName) : base(elementName, "")
        {
            this._instance = null;
        }

        internal RequestIntradayTickElementTime(string elementName, DateTime date) : base(elementName, date.ToString("yyyyMMdd"))
        {
            this._instance = date;
        }

        internal RequestIntradayTickElementTime(string elementName, Datetime date)
            : this(elementName, date.ToSystemDateTime())
        {
            this._instance = date.ToSystemDateTime();
        }

        //I can't override GetElementAsDatetime here because the Bloomberg Request object stores dates as strings, not Datetimes.  You can't convert the string to a Datetime
        internal DateTime? GetDate { get { return this._instance; } }       
    }
}
