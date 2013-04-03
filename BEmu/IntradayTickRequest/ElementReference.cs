//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayTickRequest/ElementReference.cs" company="Jordan Robinson">
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

    internal class ElementReference : Element
    {
        private readonly ElementIntradayTickDataParent _parent;

        internal ElementReference(MessageIntradayTick msg)
        {
            this._parent = (ElementIntradayTickDataParent)msg.Elements.First();
        }

        public override Name Name
        {
            get { return new Name("IntradayTickRequest"); }
        }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 1; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsArray { get { return false; } }
        public override bool IsNull { get { return false; } }
        public override IEnumerable<Element> Elements { get { yield return this._parent; } }
        public override object this[int index] { get { return null; } }

        public override Element this[string name]
        {
            get
            {
                foreach (var item in this.Elements)
                {
                    if (item.Name.ToString().ToLower() == name.ToLower())
                        return item;
                }
                return base[name];
            }
        }

        public override object this[string name, int index] { get { return null; } }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("IntradayTickRequest (choice) = {{{0}", Environment.NewLine);
            result.Append(this._parent.PrettyPrint(1));
            result.Append("}" + Environment.NewLine);
            return result;
        }
    }
}
