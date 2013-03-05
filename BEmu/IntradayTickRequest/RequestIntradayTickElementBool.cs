using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.IntradayTickRequest
{
    internal class RequestIntradayTickElementBool : RequestIntradayTickElementString
    {
        private readonly bool _value;

        internal RequestIntradayTickElementBool(string elementName, bool value)
            : base(elementName, value.ToString().ToLower())
        {
            this._value = value;
        }

        //I can't override GetElementAsBool here because the Bloomberg Request object stores bools as strings, not bools.  You can't convert the string to a bool
        internal bool GetBool { get { return this._value; } } 
    }
}
