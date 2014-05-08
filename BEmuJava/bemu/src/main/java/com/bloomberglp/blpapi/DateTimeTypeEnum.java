//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/DateTimeTypeEnum.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

public enum DateTimeTypeEnum
{
	neither(0), date(1), time(2), both(3);
	
    private final int index;   

    DateTimeTypeEnum(int index) {
        this.index = index;
    }

    public int index() { 
        return index; 
    }
}
