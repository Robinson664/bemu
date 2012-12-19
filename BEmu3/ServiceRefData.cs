using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3
{
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
                default:
                    throw new NotImplementedException(string.Format("BEmu3.ServiceRefData.CreateRequest: Operation {0} not supported", operationName));
            }
        }
    }
}
