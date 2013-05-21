//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Session.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

import com.bemu.BEmu.SessionOptions;
import com.bemu.BEmu.CorrelationID;
import com.bemu.BEmu.Request;
import com.bemu.BEmu.Event;
import java.util.Queue;
import java.util.LinkedList;

public class Session {
	@SuppressWarnings("unused")
	private SessionOptions _sessionOptions;
	
	@SuppressWarnings("unused")
	private SessionResponseType _sessionResponse;
	private enum SessionResponseType { sync, async };
	
	@SuppressWarnings("unused")
	private SessionUriType _sessionUri = SessionUriType.undefined;
	private enum SessionUriType { undefined, refData, mktData };
	
	@SuppressWarnings("unused")
	private SessionStateType _sessionState = SessionStateType.initialized;
	private enum SessionStateType { initialized, started, serviceOpened };
	
	private final Queue<Request> _sentRequests;
    
	public Session(SessionOptions sessionOptions)
	{
		this._sessionOptions = sessionOptions;
		this._sessionResponse = SessionResponseType.sync;
		this._sentRequests = new LinkedList<Request>();
	}
	
    public boolean start()
    {
        this._sessionState = SessionStateType.started;
        return true;
    }
    
    public boolean openService(String uri)
    {
        this._sessionState = SessionStateType.serviceOpened;
        return true;
    }
    
    public Service getService(String uri) throws Exception
    {
        if (uri.equals("//blp/refdata"))
        {
            this._sessionUri = SessionUriType.refData;
            return new ServiceRefData();
        }
        else
            throw new Exception(String.format("BEmu.Session.GetService: Service %s not supported", uri));
    }
    
    public CorrelationID sendRequest(Request request, CorrelationID correlationId)
    {
        request.correlationId(correlationId);
        this._sentRequests.add(request);
        return correlationId;
    }
    
    public Event nextEvent() throws Exception
    {
    	boolean isLastRequest = this._sentRequests.size() == 1;
    	Request next = this._sentRequests.poll();
    	return Event.EventFactory(next, isLastRequest);
    }
    
    
}
