using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu.HistoricalDataRequest
{
    internal class ElementReference : Element
    {
        private readonly ElementHistoricSecurityData _security;

        internal ElementReference(MessageHistoric msg)
        {
            this._security = (ElementHistoricSecurityData)msg.Elements.First();
        }

        public override Name Name
        {
            get { return new Name("securityData"); }
        }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 1; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsArray { get { return false; } }
        public override bool IsNull { get { return false; } }

        public override Element this[string name]
        {
            get
            {
                if (name.ToUpper() == this._security.Name.ToString().ToUpper())
                    return this._security;
                else
                    return base[name];
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("HistoricalDataResponse (choice) = {{{0}", Environment.NewLine);
            result.Append(this._security.PrettyPrint(1));
            result.Append("}" + Environment.NewLine);
            return result;
        }
        
    }
}
