package com.examples;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args ) throws Exception
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
        		RunHistoricalDataRequest.RunExample();
        		break;
        	case '4':
        		RunIntradayBarDataRequest.RunExample();
        		break;
        	case '5':
        		RunIntradayTickDataRequest.RunExample();
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
    }
}
