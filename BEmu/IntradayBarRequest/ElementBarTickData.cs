//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayBarRequest/ElementBarTickData.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayBarRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class ElementBarTickData : Element
    {
        internal ElementBarTickData(BarTickDataType arg)
        {
            this._time = new ElementIntradayBarDateTime(arg.DtTime);
            this._open = new ElementIntradayBarDouble("open", arg.Open);
            this._high = new ElementIntradayBarDouble("high", arg.High);
            this._low = new ElementIntradayBarDouble("low", arg.Low);
            this._close = new ElementIntradayBarDouble("close", arg.Close);
            this._volume = new ElementIntradayBarLong("volume", arg.Volume);
            this._numEvents = new ElementIntradayBarInt("numEvents", arg.NumEvents);
            this._value = new ElementIntradayBarDouble("value", arg.Value);
        }

        private readonly ElementIntradayBarDateTime _time;
        private readonly ElementIntradayBarDouble _open, _high, _low, _close, _value;
        private readonly ElementIntradayBarLong _volume;
        private readonly ElementIntradayBarInt _numEvents;

        public override Name Name { get { return new Name("barTickData"); } }
        public override int NumValues { get { return 0; } }
        public override int NumElements { get { return this.Elements.Count(); } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsArray { get { return false; } }
        public override bool IsNull { get { return false; } }

        public override object this[int index] { get { return null; } }
        public override Element GetElement(int index) { return this.Elements.Skip(index).First(); }
        public override Element GetElement(string name) { return this[name]; }

        public override object this[string name, int index]
        {
            get
            {
                if (index == 0)
                    return this[name].GetValue();
                else
                    return base[name, index];
            }
        }

        public override Element this[string name]
        {
            get
            {
                var upper = name.ToUpper();
                foreach (var item in this.Elements)
                {
                    if (item.Name.ToString().ToUpper() == upper)
                        return item;
                }
                return base[name];
            }
        }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._time;
                yield return this._open;
                yield return this._high;
                yield return this._low;
                yield return this._close;
                yield return this._volume;
                yield return this._numEvents;
                yield return this._value;
            }
        }

        public override bool HasElement(string name, bool excludeNullElements = false)
        {
            var upper = name.ToUpper();
            foreach (var item in this.Elements)
            {
                if (item.Name.ToString().ToUpper() == upper)
                    return true;
            }
            return false;
        }

        public override int GetElementAsInt32(string name)
        {
            return this[name].GetValueAsInt32();
        }

        public override Datetime GetElementAsDatetime(string name)
        {
            return this[name].GetValueAsDatetime();
        }

        public override Datetime GetElementAsDate(string name)
        {
            return this[name].GetValueAsDate();
        }

        public override Datetime GetElementAsTime(string name)
        {
            return this[name].GetValueAsTime();
        }

        public override double GetElementAsFloat64(string name)
        {
            return this[name].GetValueAsFloat64();
        }

        public override long GetElementAsInt64(string name)
        {
            return this[name].GetValueAsInt64();
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1} = {{{2}", tabs, this.Name, Environment.NewLine);
            foreach (var item in this.Elements)
            {
                result.Append(item.PrettyPrint(tabIndent + 1));
            }
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }

    }
}
