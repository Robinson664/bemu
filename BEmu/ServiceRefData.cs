//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="ServiceRefData.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    public class ServiceRefData : Service
    {
        public override string Name { get { return "//blp/refdata"; } }

        public override Request CreateRequest(string operationName)
        {
            switch (operationName)
            {
                case "HistoricalDataRequest":
                    return new HistoricalDataRequest.HistoricRequest();
                case "ReferenceDataRequest":
                    return new ReferenceDataRequest.ReferenceRequest();
                case "IntradayTickRequest":
                    return new IntradayTickRequest.IntradayTickRequest(this);
                case "IntradayBarRequest":
                    return new IntradayBarRequest.IntradayBarRequest(this);
                default:
                    throw new NotImplementedException(string.Format("BEmu.ServiceRefData.CreateRequest: Operation {0} not supported. Case-sensitive.", operationName));
            }
        }
    }
}
