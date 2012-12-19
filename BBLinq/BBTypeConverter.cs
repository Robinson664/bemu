using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Bloomberglp.Blpapi;

namespace BBLinq
{
    internal static class BBTypeConverter
    {
        /// <summary>
        /// Really, the only reason I need this function is to convert Bloomberglp.Blpapi.Datetime objects to native DateTime objects
        /// </summary>
        /// <param name="element"></param>
        /// <returns></returns>
        public static object GetValue(Element element)
        {            
            switch (element.Datatype)
            {
                case Schema.Datatype.DATE:
                    return element.GetValueAsDate().ToSystemDateTime();

                case Schema.Datatype.DATETIME:
                    return element.GetValueAsDatetime().ToSystemDateTime();

                case Schema.Datatype.TIME:
                    return element.GetValueAsTime().ToSystemDateTime();

                default:
                    return element.GetValue();
            }
        }
    }
}
