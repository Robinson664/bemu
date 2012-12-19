using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BBLinq.Types;

using Bloomberglp.Blpapi;

namespace BBLinq
{
    public static class BBHistDataType
    {
        /// <summary>
        /// Retrieve historical market data
        /// </summary>
        /// <param name="bbKeys">Bloomberg Yellow Key identifiers for securities</param>
        /// <param name="fields">Historical data fields</param>
        /// <param name="dtStart">Get historical data starting from this date</param>
        /// <param name="dtEnd">Get historical data up to this date (default = today)</param>
        /// <param name="periodicity">Frequency of the data (default = daily)</param>
        /// <param name="adj">Adjustment to the data frequency (default = actual)</param>
        /// <param name="maxPoints">The maximum number of data points to return (default = unbounded)</param>
        /// <param name="currency">Amends the value from local to desired currency</param>
        /// <param name="ovOptions">Indicates whether to use the average or the closing price in quote calculation (default = closing price)</param>
        /// <param name="pOption">Sets quote to Price or Yield for a debt instrument whose default value is quoted in yield (depending on pricing source) (default = price)</param>
        /// <param name="adjustmentNormal">Adjust historical pricing to reflect: Regular Cash, Interim, 1st Interim, 2nd Interim, 3rd Interim, 4th Interim, 5th Interim, Income, Estimated, Partnership Distribution, Final, Interest on Capital, Distribution, Prorated.</param>
        /// <param name="adjustmentAbnormal">Adjust historical pricing to reflect: Special Cash, Liquidation, Capital Gains, Long-Term Capital Gains, Short-Term Capital Gains, Memorial, Return of Capital, Rights Redemption, Miscellaneous, Return Premium, Preferred Rights Redemption, Proceeds/Rights, Proceeds/Shares, Proceeds/Warrants.</param>
        /// <param name="adjustmentSplit">Adjust historical pricing and/or volume to reflect: Spin-Offs, Stock Splits/Consolidations, Stock Dividend/Bonus, Rights Offerings/ Entitlement. (default = false)</param>
        /// <returns></returns>
        public static IEnumerable<FieldDateType> BBHistData(
            this IEnumerable<string> bbKeys,
            IEnumerable<string> fields,
            DateTime dtStart,
            DateTime? dtEnd = null,
            HistDataPeriodicity periodicity = HistDataPeriodicity.daily,
            HistDataPeriodicityAdjustment adj = HistDataPeriodicityAdjustment.actual,
            int? maxPoints = null,
            string currency = null,
            OverrideOptions ovOptions = OverrideOptions.closingPrice,
            PricingOption pOption = PricingOption.price,
            bool adjustmentNormal = false,
            bool adjustmentAbnormal = false,
            bool adjustmentSplit = false)
        {
            return BBHistDataHelpers.SendRequest(bbKeys, fields, dtStart, dtEnd ?? DateTime.Today, periodicity, adj, maxPoints, currency, ovOptions, pOption, adjustmentNormal, adjustmentAbnormal, adjustmentSplit);
        }

        private static class BBHistDataHelpers
        {
            static BBHistDataHelpers()
            {
                BBHistDataHelpers.OpenSession();
            }

            private static Service _service;
            private static Session _session;
            private static void OpenSession()
            {
                SessionOptions sessionOptions = new SessionOptions();
                sessionOptions.ServerHost = "127.0.0.1";
                sessionOptions.ServerPort = 8194;

                BBHistDataHelpers._session = new Session(sessionOptions);
                BBHistDataHelpers._session.Start();
                BBHistDataHelpers._session.OpenService("//blp/refdata");

                BBHistDataHelpers._service = BBHistDataHelpers._session.GetService("//blp/refdata");
            }

            public static IEnumerable<FieldDateType> SendRequest(
                IEnumerable<string> bbKeys,
                IEnumerable<string> fields,
                DateTime dtStart,
                DateTime dtEnd,
                HistDataPeriodicity periodicity,
                HistDataPeriodicityAdjustment adj,
                int? maxPoints,
                string currency,
                OverrideOptions ovOptions,
                PricingOption pOption,
                bool adjustmentNormal,
                bool adjustmentAbnormal,
                bool adjustmentSplit)
            {
                Request request = BBHistDataHelpers._service.CreateRequest("HistoricalDataRequest");

                foreach (var item in bbKeys)
                {
                    request.Append(Names.SECURITIES, item);
                }

                foreach (var item in fields)
                {
                    request.Append(Names.FIELDS, item);
                }

                string strPeriodicity = HistDataPeriodicityType.Convert(periodicity);
                string strAdj = HistDataPeriodicityAdjustmentType.Convert(adj);
                string strOverrideOptions = OverrideOptionsType.Convert(ovOptions);
                string strPricingOption = PricingOptionType.Convert(pOption);

                request.Set(Names.PERIODICITYADJUSTMENT, strAdj);
                request.Set(Names.PERIODICITYSELECTION, strPeriodicity);
                request.Set(Names.STARTDATE, dtStart.ToString("yyyyMMdd"));
                request.Set(Names.ENDDATE, dtEnd.ToString("yyyyMMdd"));
                request.Set(Names.PRICINGOPTION, strPricingOption);
                request.Set(Names.ADJUSTMENTNORMAL, adjustmentNormal);
                request.Set(Names.ADJUSTMENTABNORMAL, adjustmentAbnormal);
                request.Set(Names.ADJUSTMENTSPLIT, adjustmentSplit);

                if (maxPoints.HasValue)
                    request.Set(Names.MAXDATAPOINTS, maxPoints.Value);

                if (!string.IsNullOrWhiteSpace(currency))
                    request.Set(Names.CURRENCY, currency);

                if (!string.IsNullOrWhiteSpace(strOverrideOptions))
                    request.Set(Names.OVERRIDEOPTIONS, strOverrideOptions);

                CorrelationID corr = new CorrelationID(NextCorrelationId.Get());
                BBHistDataHelpers._session.SendRequest(request, corr);

                bool continueToLoop = true;
                while (continueToLoop) //wait for a complete response
                {
                    IEnumerable<FieldDateType> current = null;
                    Event eventObj = BBHistDataHelpers._session.NextEvent();

                    switch (eventObj.Type)
                    {
                        case Event.EventType.RESPONSE: // final event
                            continueToLoop = false;
                            current = BBHistDataHelpers.ProcessResponse(eventObj, corr, fields);
                            break;
                        case Event.EventType.PARTIAL_RESPONSE:
                            current = BBHistDataHelpers.ProcessResponse(eventObj, corr, fields);
                            break;
                    }

                    if (current != null)
                    {
                        foreach (var item in current)
                        {
                            yield return item;
                        }
                    }
                }
            }

            private static IEnumerable<FieldDateType> ProcessResponse(Event eventObj, CorrelationID corr, IEnumerable<string> fields)
            {
                foreach (var message in eventObj.GetMessages()) //loop through each message
                {
                    if (message.CorrelationID.Value == corr.Value)
                    {
                        Element elmSecDataArr = message.GetElement(Names.SECURITYDATA);
                        string bbkey = elmSecDataArr.GetElementAsString(Names.SECURITY);
                        Element elmFieldData = elmSecDataArr.GetElement(Names.FIELDDATA);

                        for (int i = 0; i < elmSecDataArr.NumValues; i++) //loop through each security
                        {
                            for (int j = 0; j < elmFieldData.NumValues; j++)
                            {
                                Element elmData = elmFieldData.GetValueAsElement(j);
                                if (elmData.HasElement(Names.DATE, true)) //ensure that the field has a date (it probably always does)
                                {
                                    DateTime date = elmData.GetElementAsDatetime(Names.DATE).ToSystemDateTime();
                                    foreach (var elm in elmData.Elements)
                                    {
                                        if (!elm.Name.Equals(Names.DATE)) //note that the "!=" operator here doesn't always work
                                        {
                                            object value = BBTypeConverter.GetValue(elm);
                                            FieldDateType ftype = new FieldDateType(bbkey, elm.Name.ToString(), value, date);
                                            yield return ftype;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
