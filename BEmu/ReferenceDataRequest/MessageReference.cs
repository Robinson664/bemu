//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/MessageReference.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.ReferenceDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class MessageReference : Message
    {
        private readonly ElementReferenceSecurityDataArray _securities;

        internal MessageReference(CorrelationID corr, Dictionary<string, Dictionary<string, object>> fieldData) : base(new Name("ReferenceDataResponse"), corr, null)
        {
            this._securities = new ElementReferenceSecurityDataArray(fieldData);
        }

        public override int NumElements { get { return 1; } }
        public override IEnumerable<Element> Elements { get { yield return this._securities; } }
        public override string TopicName { get { return ""; } }
        public override BEmu.Element AsElement { get { return new ElementReference(this); } }

        public override object this[string name, int index]
        {
            get
            {
                ElementReferenceSecurityDataArray secArray = (ElementReferenceSecurityDataArray)this[name]; //parent class checks the name

                int itemCount = 0;
                foreach (var item in secArray.Elements)
                {
                    if (itemCount == index)
                        return item;

                    itemCount++;
                }

                return base[name, index];
            }
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.Append("ReferenceDataResponse (choice) = {" + Environment.NewLine);
            result.Append(this._securities.PrettyPrint(1));
            result.Append("}");

            return result.ToString();
        }

    }
}
