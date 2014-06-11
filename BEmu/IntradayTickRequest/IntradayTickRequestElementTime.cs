//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="IntradayTickRequest/IntradayTickRequestElementTime.cs" company="Jordan Robinson">
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

    internal class IntradayTickRequestElementTime : IntradayTickRequestElementString
    {
        private readonly DateTime? _instance;

        internal IntradayTickRequestElementTime(string elementName) : base(elementName, "")
        {
            this._instance = null;
        }

        internal IntradayTickRequestElementTime(string elementName, DateTime date) : base(elementName, date.ToString("yyyy-MM-ddTHH:mm:ss.fff"))
        {
            this._instance = date;
        }

        internal IntradayTickRequestElementTime(string elementName, Datetime date)
            : this(elementName, date.ToSystemDateTime())
        {
            this._instance = date.ToSystemDateTime();
        }

        //I can't override GetElementAsDatetime here because the Bloomberg Request object stores dates as strings, not Datetimes.  You can't convert the string to a Datetime
        internal DateTime? GetDate { get { return this._instance; } }
        public override Schema.Datatype Datatype { get { return Schema.Datatype.STRING; } }    
    }
}
