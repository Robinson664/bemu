//------------------------------------------------------------------------------
// <copyright project="BEmu" file="ReferenceDataRequest/ElementReferenceArrayChainTickers.cs" company="Jordan Robinson">
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

    internal class ElementReferenceArrayChainTickers : ElementReferenceArray
    {
        internal enum OptionalityEnum { put = 'P', call = 'C' }

        internal ElementReferenceArrayChainTickers(string underlier, uint numPoints, string strDtExp, OptionalityEnum optionality) : base("CHAIN_TICKERS", new List<Element>())
        {
            //assume that the underlier takes the form "ABC US EQUITY"
            string ticker = underlier.Substring(0, underlier.IndexOf(' '));

            DateTime dtExp;
            if (string.IsNullOrWhiteSpace(strDtExp))
                dtExp = DateTime.Today.AddMonths(1).AddDays(-DateTime.Today.Day).AddDays(20); //assume the 20th of the month
            else if (strDtExp.Length == 8)
                dtExp = DateTime.ParseExact(strDtExp, "yyyyMMdd", System.Globalization.CultureInfo.InvariantCulture);
            else if (strDtExp.Length == 6)
                dtExp = DateTime.ParseExact(strDtExp + "20", "yyyyMMdd", System.Globalization.CultureInfo.InvariantCulture); //assume the 20th of the month
            else if (strDtExp[strDtExp.Length - 1] == 'F')
            {
                uint numMonths = uint.Parse(strDtExp.Substring(0, strDtExp.Length - 1));
                dtExp = DateTime.Today.AddMonths((int)numMonths).AddDays(-DateTime.Today.Day).AddDays(20); //assume the 20th of the month
            }
            else
                throw new NotImplementedException("BEmu.ReferenceDataRequest.ElementReferenceArrayChainTickers: unable to determine the dtExp");

            int strike = Types.RandomDataGenerator.Strike();
            for (int count = 0; count < numPoints; count++, strike += 5)
            {
                //string optionTicker = string.Format("{0} US {1:MM/dd/yy} {2}{3}", ticker, dtExp, (char)optionality, strike);

                Element elm = new ElementReferenceArrayChainTickersItem(ticker, dtExp, optionality, strike);

                base._values.Add(elm);
            }
        }
    }
}
