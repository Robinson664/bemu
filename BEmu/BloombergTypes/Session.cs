//------------------------------------------------------------------------------
// <copyright project="BEmu" file="BloombergTypes/Session.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    using System.Threading;

    public class Session
    {
        private SessionOptions _sessionOptions;

        #pragma warning disable 0414 //disables the "is assigned but its value is never used" warning
        private enum SessionResponseType { sync, async }
        private readonly SessionResponseType _sessionResponse;

        private enum SessionUriType { undefined, refData, mktData }
        private SessionUriType _sessionUri = SessionUriType.undefined;

        private enum SessionStateType { initialized, started, serviceOpened }
        private SessionStateType _sessionState = SessionStateType.initialized;
        #pragma warning restore 0414

        private readonly Queue<Request> _sentRequests;
        private readonly EventHandler _asyncHandler;
        private CorrelationID _asyncOpenCorrelation;
        private readonly List<Subscription> _subscriptions;
        private readonly Timer _marketSimulatorTimer;
        private readonly object _syncroot = new object();

        #region SYNC
        public Session(SessionOptions sessionOptions) //for ReferenceData and HistoricalData (sync)
        {
            this._sessionResponse = SessionResponseType.sync;
            this._sessionOptions = sessionOptions;
            this._sentRequests = new Queue<Request>();
            this._asyncHandler = null;
            this._subscriptions = null;
            this._marketSimulatorTimer = null;
        }

        public bool Start()
        {
            this._sessionState = SessionStateType.started;
            return true;
        }

        public bool OpenService(string uri)
        {
            this._sessionState = SessionStateType.serviceOpened;
            return true;
        }

        public Service GetService(string uri)
        {
            if (uri == "//blp/refdata")
            {
                this._sessionUri = SessionUriType.refData;
                return new ServiceRefData();
            }
            else
                throw new NotImplementedException(string.Format("BEmu.Session.GetService: Service {0} not supported", uri));
        }

        public CorrelationID SendRequest(Request request, CorrelationID correlationId)
        {
            if (request is HistoricalDataRequest.RequestHistoric)
            {
                if (!((HistoricalDataRequest.RequestHistoric)request).DtStart.HasValue)
                    throw new ArgumentException("Historic requests must have start dates");
            }

            request.correlationId = correlationId;
            this._sentRequests.Enqueue(request);
            return correlationId;
        }

        public Event NextEvent()
        {
            bool isLastRequest = this._sentRequests.Count == 1;
            return Event.EventFactory(this._sentRequests.Dequeue(), isLastRequest);
        }
        #endregion

        #region ASYNC
        public Session(SessionOptions sessionOptions, EventHandler handler) //for MarketData (async)
        {
            this._sessionResponse = SessionResponseType.async;
            this._sessionOptions = sessionOptions;
            this._sentRequests = null;
            this._asyncHandler = handler;
            this._subscriptions = new List<Subscription>();
            this._marketSimulatorTimer = new Timer(new TimerCallback(this.MarketSimulatorTimerStep), null, (int)TimeSpan.FromSeconds(0).TotalMilliseconds, Timeout.Infinite);
        }

        public bool StartAsync()
        {
            this._sessionState = SessionStateType.started;
            MarketDataRequest.EventMarket evtSessionStatus = new MarketDataRequest.EventMarket(Event.EventType.SESSION_STATUS, null, null);
            MarketDataRequest.EventMarket evtServiceStatus = new MarketDataRequest.EventMarket(Event.EventType.SERVICE_STATUS, new CorrelationID(), null);

            if (this._asyncHandler != null)
            {
                this._asyncHandler(evtSessionStatus, this);
                this._asyncHandler(evtServiceStatus, this);
            }
            
            return true;
        }

        public void Stop()
        {
            this._marketSimulatorTimer.Change(Timeout.Infinite, Timeout.Infinite);
        }

        public void Dispose()
        {
            this._marketSimulatorTimer.Dispose();
        }

        public void OpenServiceAsync(string uri, CorrelationID correlationId)
        {
            this._sessionUri = SessionUriType.mktData;
            this._sessionState = SessionStateType.serviceOpened;
            this._asyncOpenCorrelation = correlationId;
        }

        public void Subscribe(IList<Subscription> subscriptionList)
        {
            lock (this._syncroot) //protect _subscriptions
                this._subscriptions.AddRange(subscriptionList);

            MarketDataRequest.EventMarket evtSubStatus = new MarketDataRequest.EventMarket(Event.EventType.SUBSCRIPTION_STATUS, null, subscriptionList);
            if (this._asyncHandler != null)
            {
                this._asyncHandler(evtSubStatus, this);
            }
        }

        public void Cancel(CorrelationID corr)
        {
            lock (this._syncroot) //protect _subscriptions
            {
                for (int i = this._subscriptions.Count - 1; i >= 0; i--)
                {
                    if (this._subscriptions[i].CorrelationID.Value == corr.Value && this._subscriptions[i].CorrelationID.IsInternal == corr.IsInternal)
                    {
                        MarketDataRequest.EventMarket evtSubCancel = new MarketDataRequest.EventMarket(Event.EventType.SUBSCRIPTION_STATUS, this._subscriptions[i]);
                        if (this._asyncHandler != null)
                        {
                            this._asyncHandler(evtSubCancel, this);
                        }
                        this._subscriptions.RemoveAt(i);
                    }
                }
            }
        }

        private void MarketSimulatorTimerStep(object arg)
        {
            int? conflationIntervalInMilleseconds = null;

            lock (this._syncroot) //protect _subscriptions
            {
                List<Subscription> subsToUse = new List<Subscription>();                

                foreach (var item in this._subscriptions)
                {
                    if (Types.RandomDataGenerator.ShouldIncludeQuote()) //70% chance that I'll send a new quote for the current subscription (after the first response which contains all tickers)
                        subsToUse.Add(item);

                    if (item.ConflationInterval.HasValue)
                        conflationIntervalInMilleseconds = item.ConflationInterval.Value * 1000;
                }

                MarketDataRequest.EventMarket evt = new MarketDataRequest.EventMarket(Event.EventType.SUBSCRIPTION_DATA, null, subsToUse);

                if (this._asyncHandler != null)
                    this._asyncHandler(evt, this);
            }

            this._marketSimulatorTimer.Change(conflationIntervalInMilleseconds.GetValueOrDefault((int)Types.RandomDataGenerator.TimeBetweenMarketDataEvents().TotalMilliseconds), Timeout.Infinite);
        }
        #endregion

    }
}
