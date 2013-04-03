//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ServiceRefData.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu
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
                    return new HistoricalDataRequest.RequestHistoric();
                case "ReferenceDataRequest":
                    return new ReferenceDataRequest.RequestReference();
                case "IntradayTickRequest":
                    return new IntradayTickRequest.RequestIntradayTick(this);
                case "IntradayBarRequest":
                    return new IntradayBarRequest.RequestIntradayBar(this);
                default:
                    throw new NotImplementedException(string.Format("BEmu.ServiceRefData.CreateRequest: Operation {0} not supported", operationName));
            }
        }
    }
}
