//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="Main.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------


public class Main {

	/**
	 * @param args
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception //I don't know how to fix or suppress this warning
	{
        System.out.println("Bloomberg API Emulator Examples");
        System.out.println("http://bemu.codeplex.com/");
        System.out.println("By: Robinson664");
        System.out.println();
        //System.out.println("To send a reference data request, push 1");
        //System.out.println("To send a market data request, push 2");
        System.out.println("To send a historical data request, push 3");
        System.out.println("To send a intraday tick data request, push 4");
        System.out.println("To send a intraday bar data request, push 5");
        
        int input = System.in.read();
        
        /*
        Scanner in = new Scanner(System.in);
        int input = in.nextInt();
        */
        
        System.out.println();
        System.out.println();
        boolean informationReturned = true;
        
        switch(input)
        {
        	case '1':
        		//TODO: Reference Data Request
        		break;
        	case '2':
        		//TODO: Market Data Request
        		break;
        	case '3':
        		HistoricalDataRequest.RunExample();
        		break;
        	case '4':
        		IntradayBarDataRequest.RunExample();
        		break;
        	case '5':
        		IntradayTickDataRequest.RunExample();
        		break;
        	default:
        		informationReturned = false;
        		break;
        }
        
        if (informationReturned)
        {
        	System.out.println();
        	System.out.println("Please note that the data in this request is completely random: it is not real data.");
        	System.out.println("Do not make any trading or investment decisions using the data shown here.");
        }

        System.out.println();
        System.out.println("Push enter to quit the application.");
        System.in.read();
	}
	
}
