//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="HistoricalDataRequest/HistoricRequest.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi.HistoricalDataRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class HistoricRequest : Request
    {
        private readonly HistoricRequestElementStringArray _securities, _fields;
        private HistoricRequestElementDate _dtStart, _dtEnd;

        private HistoricRequestElementBool _adjustmentNormalElement, _adjustmentAbnormalElement, _adjustmentSplitElement;

        private HistoricRequestElementInt _maxDataPointElement;

        private HistoricRequestElementString _periodicityAdjustmentElement, _periodicityElement, _overrideOptionsElement, _pricingOptionElement;

        private enum HistDataPeriodicityAdjustment { actual, calendar, fiscal }
        private HistDataPeriodicityAdjustment _periodicityAdjustment = HistDataPeriodicityAdjustment.actual;

        public enum HistDataPeriodicity { daily, weekly, monthly, quarterly, semi_annually, yearly }
        private HistDataPeriodicity _periodicity = HistDataPeriodicity.daily;

#pragma warning disable 0414 //disables the "is assigned but its value is never used" warning
        public enum PricingOption { price, yield }
        private PricingOption _pricingOption = PricingOption.price;

        public enum OverrideOptions { closingPrice, averagePrice }
        private OverrideOptions _overrideOptions = OverrideOptions.closingPrice;
#pragma warning restore 0414

        internal HistoricRequest()
        {
            this._dtStart = new HistoricRequestElementDate("startDate");
            this._dtEnd = new HistoricRequestElementDate("endDate");
            this._securities = new HistoricRequestElementStringArray("securities");
            this._fields = new HistoricRequestElementStringArray("fields");
        }

        internal List<string> Securities { get { return this._securities.Values; } }
        internal List<string> Fields { get { return this._fields.Values; } }
        internal DateTime? DtStart { get { return this._dtStart.GetDate; } }
        internal DateTime? DtEnd { get { return this._dtEnd.GetDate; } }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._securities;
                yield return this._fields;
                yield return this._dtStart;
                yield return this._dtEnd;

                if (this._adjustmentNormalElement != null) yield return this._adjustmentNormalElement;
                if (this._adjustmentAbnormalElement != null) yield return this._adjustmentAbnormalElement;
                if (this._adjustmentSplitElement != null) yield return this._adjustmentSplitElement;
                if (this._maxDataPointElement != null) yield return this._maxDataPointElement;
                if (this._periodicityAdjustmentElement != null) yield return this._periodicityAdjustmentElement;
                if (this._periodicityElement != null) yield return this._periodicityElement;
                if (this._overrideOptionsElement != null) yield return this._overrideOptionsElement;
                if (this._pricingOptionElement != null) yield return this._pricingOptionElement;
            }
        }

        public override Element this[string elementName]
        {
            get
            {
                if (this._securities.Name.ToString().ToLower() == elementName.ToLower())
                    return this._securities;
                else if (this._fields.Name.ToString().ToLower() == elementName.ToLower())
                    return this._fields;
                else
                    throw new NotImplementedException("BEmu.HistoricalDataRequest.RequestReference: public Element this[string elementName] not supported");
            }
        }

        #region Date Stream
        internal IEnumerable<DateTime> GetDates()
        {
            List<DateTime> result = this.GetDatesBeforeMaxPoints();

            if (this._maxDataPointElement == null)
                return result;
            else //if the results are capped, this returns the most recent dates
                return result.Skip(result.Count - this._maxDataPointElement.GetInt);
        }

        private List<DateTime> GetDatesBeforeMaxPoints()
        {
            List<DateTime> result = new List<DateTime>();

            DateTime dtStart = this._dtStart.GetDate.GetValueOrDefault(DateTime.Today.AddYears(-1)); //BEmu.Session.SendRequest assures that dtStart is not null
            DateTime dtEnd = this._dtEnd.GetDate.GetValueOrDefault(DateTime.Today.AddDays(-1));

            if (this._periodicityAdjustment == HistDataPeriodicityAdjustment.fiscal)
                dtStart.AddDays(-dtStart.Day); //I use the start of the month as the fiscal adjustment.  It's fake.

            DateTime dtCurrent = dtStart;
            do
            {
                result.Add(dtCurrent);

                switch (this._periodicity)
                {
                    case HistDataPeriodicity.daily:
                        dtCurrent = dtCurrent.AddDays(1);
                        break;
                    case HistDataPeriodicity.weekly:
                        dtCurrent = dtCurrent.AddDays(7);
                        break;
                    case HistDataPeriodicity.monthly:
                        dtCurrent = dtCurrent.AddMonths(1);
                        break;
                    case HistDataPeriodicity.quarterly:
                        dtCurrent = dtCurrent.AddMonths(3);
                        break;
                    case HistDataPeriodicity.semi_annually:
                        dtCurrent = dtCurrent.AddMonths(6);
                        break;
                    case HistDataPeriodicity.yearly:
                        dtCurrent = dtCurrent.AddYears(1);
                        break;
                    default:
                        throw new NotImplementedException(this._periodicity.ToString());
                }

                if (dtCurrent.DayOfWeek == DayOfWeek.Saturday)
                    dtCurrent = dtCurrent.AddDays(2);
                else if (dtCurrent.DayOfWeek == DayOfWeek.Sunday)
                    dtCurrent = dtCurrent.AddDays(1);

            } while (dtCurrent <= dtEnd && dtCurrent <= DateTime.Today);

            return result;
        }
        #endregion

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendFormat("HistoricalDataRequest = {{{0}", Environment.NewLine);

            if (this._securities.NumValues > 0)
                result.Append(this._securities.PrettyPrint(1));

            if (this._fields.NumValues > 0)
                result.Append(this._fields.PrettyPrint(1));

            Element[] elms = { this._dtStart, this._dtEnd, this._periodicityAdjustmentElement, this._periodicityElement, this._overrideOptionsElement, 
                                 this._pricingOptionElement, this._maxDataPointElement, this._adjustmentNormalElement, this._adjustmentAbnormalElement, 
                                 this._adjustmentSplitElement };

            for (int i = 0; i < elms.Length; i++)
            {
                Element current = elms[i];

                if (current != null)
                    result.Append(current.PrettyPrint(1));
            }

            result.AppendLine("}");
            return result.ToString();
        }

        #region OVERRIDES
        public override void Append(string name, string elementValue)
        {
            switch (name)
            {
                case "securities":
                    this._securities.AppendValue(elementValue);
                    break;
                case "fields":
                    this._fields.AppendValue(elementValue);
                    break;
                default:
                    throw new ArgumentException(string.Format("BEmu.RequestHistoric.Append: Element name {0} not supported.  Case-sensitive.", name));
            }
        }

        public override void Set(string name, string elementValue)
        {
            DateTime dtTemp;
            switch (name)
            {
                case "startDate":
                    if (Types.DisplayFormats.HistoricalOrReferenceRequests.TryParseInput(elementValue, out dtTemp))
                        this._dtStart = new HistoricRequestElementDate("startDate", dtTemp);
                    else
                        throw new ArgumentException(string.Format("BEmu.Request.Set: Bad startDate format {0}, yyyyMMdd expected", elementValue));
                    break;
                case "endDate":
                    if (Types.DisplayFormats.HistoricalOrReferenceRequests.TryParseInput(elementValue, out dtTemp))
                        this._dtEnd = new HistoricRequestElementDate("endDate", dtTemp);
                    else
                        throw new ArgumentException(string.Format("BEmu.Request.Set: Bad endDate format {0}, yyyyMMdd expected", elementValue));
                    break;
                case "periodicityAdjustment":
                    switch (elementValue)
                    {
                        case "CALENDAR":
                            this._periodicityAdjustment = HistDataPeriodicityAdjustment.calendar;
                            break;
                        case "FISCAL":
                            this._periodicityAdjustment = HistDataPeriodicityAdjustment.fiscal;
                            break;
                        case "ACTUAL":
                            this._periodicityAdjustment = HistDataPeriodicityAdjustment.actual;
                            break;
                        default:
                            throw new ArgumentException(string.Format("BEmu.Request.Set: unknown value ({0}) for periodicityadjustment. These are case-sensitive.", elementValue));
                    }
                    this._periodicityAdjustmentElement = new HistoricRequestElementString("periodicityAdjustment", elementValue);
                    break;

                case "periodicitySelection":
                    switch (elementValue)
                    {
                        case "WEEKLY":
                            this._periodicity = HistDataPeriodicity.weekly;
                            break;
                        case "MONTHLY":
                            this._periodicity = HistDataPeriodicity.monthly;
                            break;
                        case "QUARTERLY":
                            this._periodicity = HistDataPeriodicity.quarterly;
                            break;
                        case "SEMI_ANNUALLY":
                            this._periodicity = HistDataPeriodicity.semi_annually;
                            break;
                        case "YEARLY":
                            this._periodicity = HistDataPeriodicity.yearly;
                            break;
                        case "DAILY":
                            this._periodicity = HistDataPeriodicity.daily;
                            break;
                        default:
                            throw new ArgumentException(string.Format("BEmu.Request.Set: unknown value ({0}) for periodicityselection. These are case-sensitive.", elementValue));
                    }
                    this._periodicityElement = new HistoricRequestElementString("periodicitySelection", elementValue);
                    break;

                case "pricingOption":
                    switch (elementValue)
                    {
                        case "PRICING_OPTION_YIELD":
                            this._pricingOption = PricingOption.yield;
                            break;
                        case "PRICING_OPTION_PRICE":
                            this._pricingOption = PricingOption.price;
                            break;
                        default:
                            throw new ArgumentException(string.Format("BEmu.Request.Set: unknown value ({0}) for pricingOption. These are case-sensitive.", elementValue));
                    }
                    this._pricingOptionElement = new HistoricRequestElementString("pricingOption", elementValue);
                    break;

                case "overrideOption":
                    switch (elementValue)
                    {
                        case "OVERRIDE_OPTION_GPA":
                            this._overrideOptions = OverrideOptions.averagePrice;
                            break;
                        case "OVERRIDE_OPTION_CLOSE":
                            this._overrideOptions = OverrideOptions.closingPrice;
                            break;
                        default:
                            throw new ArgumentException(string.Format("BEmu.Request.Set: unknown value ({0}) for overrideoption. These are case-sensitive.", elementValue));
                    }
                    this._overrideOptionsElement = new HistoricRequestElementString("overrideOption", elementValue);
                    break;

                default:
                    throw new ArgumentException(string.Format("BEmu.Request.Set: Element name {0} not supported. These are case-sensitive.", name));
            }
        }

        public override void Set(string name, bool elementValue)
        {
            switch (name)
            {
                case "adjustmentNormal":
                    this._adjustmentNormalElement = new HistoricRequestElementBool("adjustmentNormal", elementValue);
                    break;
                case "adjustmentAbnormal":
                    this._adjustmentAbnormalElement = new HistoricRequestElementBool("adjustmentAbnormal", elementValue);
                    break;
                case "adjustmentSplit":
                    this._adjustmentSplitElement = new HistoricRequestElementBool("adjustmentSplit", elementValue);
                    break;
                default:
                    throw new ArgumentException(string.Format("BEmu.Request.Set: Element name {0} not supported", name));
            }
        }

        public override void Set(string name, int elementValue)
        {
            switch (name)
            {
                case "maxDataPoints":
                    this._maxDataPointElement = new HistoricRequestElementInt("maxDataPoints", elementValue);
                    break;
                default:
                    throw new ArgumentException(string.Format("BEmu.Request.Set: Element name {0} not supported", name));
            }
        }
        #endregion
    }
}
