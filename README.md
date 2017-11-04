# Bloomberg API Emulator (.Net, Java, C++)

In the spirit of Bloomberg's [Open Market Data Initiative](http://www.openbloomberg.com/) meant to "foster open solutions for the financial services industry", I submit the Bloomberg API Emulator. In early 2012, Bloomberg released its Bloomberg API with an MIT-style license in an effort to be more open to developers of financial services solutions. Developers can download the [Bloomberg API](http://www.openbloomberg.com/open-api/) and the [API documentation](http://www.openbloomberg.com/files/2012/10/blpapi-developers-guide.pdf) (pdf link); however, developers cannot run a program written for the Bloomberg API without a Bloomberg account. I wrote the Bloomberg API Emulator to address this gap.

If you want to learn to write code that interacts with the Bloomberg API, you ordinarily need to have a Bloomberg account which could be prohibitively expensive for your purposes. If you need to write Bloomberg API code (e.g., subscribing to market data), but don't have a Bloomberg account, you can use this Bloomberg API Emulator. The Bloomberg API Emulator allows you to:

Learn to write Bloomberg code without a Bloomberg account, and
Test out your Bloomberg API calls without affecting your existing Bloomberg data caps.
Code written for the Bloomberg API Emulator works seamlessly with the actual Bloomberg API. If you have a project written for the Bloomberg API Emulator and you want it to instead use the actual Bloomberg API (available [here](http://www.openbloomberg.com/open-api/)), you will perform these two simple steps:

Remove your project's reference to BEmu and replace it with a reference to the Bloomberg API (Bloomberglp.Blapi). In C++, replace the project's reference to BEmu_cpp.dll with a reference to blpapiX_XX.dll.
In your .Net code, replace using BEmu; with using Bloomberglp.Blpapi;. In your Java code, replace the reference to BEmu.jar with a reference to blpapi_XXX.jar.  In your C++ code, simply include the blpapi_*.h headers instead of the BloombergTypes/*.h headers (see a simple example in Examples_cpp/headers/api_selector.h using a #define)
That's it. Your code will work as you'd expect. My project emulates:

Intraday tick data requests and responses (.Net, Java, C++),
Intraday bar data requests and responses (.Net, Java, C++),
Reference data requests and responses (.Net, Java, C++),
Historical data requests and responses (.Net, Java, C++), and
Market data subscription events (.Net, Java, C++)
If you like this project please consider [making a donation to the developer](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=robinson%2ejordanl%40gmail%2ecom&lc=US&item_name=BEmu&item_number=BEmuCodePlex&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHosted).  A Bloomberg account costs almost $2,000 a month, so this project could potentially save you a lot of money.

Please note that while I emulate the Bloomberg API calls, I do not make any attempt to return any real data. If, for example, you request the BID price for AAPL US EQUITY, the Bloomberg API Emulator will respond with a random number between 1 and 100 (which is far below the current price). These responses are only meant to show what an actual Bloomberg API response would look like. The data in the responses is completely fabricated. Do not use the responses from the Bloomerg API Emulator to make any actual trading or investment decisions.

## Why Should I use the Bloomberg API Emulator?

Two reasons:
1. Bloomberg provides [their API](http://www.openbloomberg.com/open-api/) in several languages, including .Net, Java, and C++, for developers. Their aim is for developers to "further enhance and extend this powerful technology for financial applications". Developers looking to write an application using the Bloomberg API will quickly discover that they need a Bloomberg account to use the Bloomberg API. Barring this, the user will simply receive responses that say something similar to "error: not logged in". The Bloomberg API Emulator sidesteps this requirement by responding in the way that the actual Bloomberg API responds when a user is actually logged in. The Bloomberg API Emulator will respond with messages that look and act like the real messages in a Bloomberg API response.
2. The second reason you may find this project useful is that a Bloomberg account has data access limits. You may be limited to querying a given number of securities per month or per day depending on the type of Bloomberg account you have. If you are writing code that repeatedly sends Bloomberg data requests, you may quickly exhaust your data capacity. If this happens, your development will be hampered because the Bloomberg API will respond only with messages that look like "error: data usage limit reached". To get around this problem, you can use the Bloomberg API Emulator for your development purposes. Send your data requests to the Bloomberg API Emulator and write your code to handle the responses. Although the data is completely fabricated, you will likely only be interested in writing code that handles the data, not the data itself. You can make as many data requests to the Bloomberg API Emulator as you like; you will never exhaust any data capacity.
## How Do I Use the Bloomberg API Emulator?

I have included some examples of how to request information in the BEmu solution. My C# examples are in the project called Examples. My Java examples are in BEmu\BEmuJava\bemu\src\main\java\com\examples*.java. My C++ examples are in the project called Examples_cpp. These examples will get you started with the Bloomberg API Emulator. For further information please refer to the [Bloomberg API Developer's Guide (pdf)](http://www.openbloomberg.com/files/2012/10/blpapi-developers-guide.pdf). The [Bloomberg API download](http://www.openbloomberg.com/open-api/) also contains code examples. Please note that since the Bloomberg API Emulator only emulates reference, historical, market, intraday tick, and intraday bar requests, some of the examples in the Bloomberg API download will not work. Also note that the emulator supports:

Request Type | .Net | Java | C++
------------ | ------------- | ------------- | -------------
Intraday Bar | supported | supported | supported
Intraday Tick | supported | supported | supported
Reference | supported | supported | supported
Historical | supported | supported | supported
Market Data | supported | supported | supported

## What Does a Response Look Like?

A response to a Bloomberg API Emulator request looks and acts exactly like a response to an actual Bloomberg API request. If you have a Message object that represents the response to a simple request and you call ToString() (.Net) on it, or toString() (Java) on it, or .print(cout) on it, it will look like the following whether the message was generated by the Bloomberg API Emulator or the actual Bloomberg API:

EventType =RESPONSE
correlationID=User: 1
messageType =ReferenceDataResponse
ReferenceDataResponse (choice) = {
securityData[] = {
securityData = {
security = IBM US Equity
sequenceNumber = 0
fieldData = {
PX_LAST = 16.15
}
}
}
} "}

It's not clear from the response above whether it came from the Bloomberg API Emulator or the actual Bloomberg API. That is the point of the Bloomberg API Emulator. The code that you write to handle the response for the Bloomberg API Emulator works exactly the same for the actual Bloomberg API.
## Now that my Code Works With the Bloomberg API Emulator, I Want to Make it Work With the Actual Bloomberg API. How do I do this?

You will need to download the appropriate Bloomberg API libraries from [Bloomberg API](http://www.openbloomberg.com/open-api/) or <WAPI> on your Bloomberg terminal. I do not include the Bloomberg API binaries in the download or in the source files.

Here is how to download and reference the actual Bloomberg API:

.Net:
1. Download the programming interface (BLPAPI) [Bloomberg API](http://www.openbloomberg.com/open-api/) or <WAPI> on your terminal and add a reference to the DLL in your project. Be sure to remove your existing reference to BEmu
2. In your code, replace all instances of using BEmu; with using Bloomberglp.Blpapi;

Java:
1. Download the programming interface (blpapi_java_X.X.X.X.tar.gz) [Bloomberg API](http://www.openbloomberg.com/open-api/) or <WAPI> on your terminal
2. Remove your project's reference to BEmu.jar and replace it with a reference to blpapi_java_X.X.X.X.jar.

C++:
1. Download the programming interface blpapi_cpp [Bloomberg API](http://www.openbloomberg.com/open-api/) or <WAPI> on your terminal and have your project reference the blpapi3_32.dll and blpapi3_32.lib files appropriately.
2. In your code, instead of including the header files in the BloombergTypes folder, include the blpapi_*.h header files. For a simple example, see the file Examples_cpp/headers/api_selector.h. I recommend copying that api_example.h directly into your project and having your Bloomberg code include that file rather than the individual header files. If you do this, you can easily control header files and namespaces by commenting on uncommenting the #define USE_BEMU_API line.

That's it. Your code will compile and it will work exactly as it did when you referenced the Bloomberg API Emulator. The difference is that your responses will contain real data.
## Limitations

**Securities**: The Bloomberg service supports many types of securities. I am unable to test the Bloomberg API Emulator with all of the security types that the Bloomberg service supports because it supports so many. I tested the Bloomberg API Emulator with equities, equity options, futures, and options on futures. If you need to work with other types of securities, the Bloobmerg API Emulator may or may not work for you. For instance, some securities price in points rather than decimals. If a PX_LAST request returns a number like, 102.13, that may be in points, and to convert that to decimals you may need to multiply the decimal part by (100 / 32) as there may be 32 points per tick. (You would get 102.40625).

**Fields**: The Bloomberg reference data request service supports thousands of fields. You can request any number of pieces of information about a security. I made no attempt to emulate them all. I do however need to show responses containing different types (e.g., strings, doubles, Datetimes (sic)) for completeness. This is how I determine how to handle a requested field and what type I should use in the response:
1. If a field starts with the letter 'Z', I treat it as an invalid field.
2. CHAIN_TICKERS: This is a bulk field with available overrides. I'll explain this below.
3. TICKER: If the field contains TICKER, I return a string equal to the ticker that the user requested.
4. EXPIRE_DT: If the field contains EXPIRE_DT and the requested security ends with COMDTY or INDEX, I return a Datetime three months from today. Otherwise if the requested security is of the format ABC yyMMdd[PC]\d{8} EQUITY (this is almost a regular expression that is meant to show what an option symbol looks like), I will return a Datetime equal to the yyMMdd part of the requested security string. If neither of those two conditions hold, I return a Datetime three months from today.
5. TRADEABLE_DT: if the field contains TRADEABLE_DT, I return a Datetime three months from today.
6. If the requested field doesn't satisfy any of the above conditions, I return a random double in the range (0, 100) rounded to two decimal places.

**Non-Existent Securities and Fields** Bloomberg supports a universe of securities. A user can locate thousands of pieces of information about a given security. I have no way of knowing if a given string is a valid security, or a valid field, or something not supported. It is however important to show how the API handles non-existent securities and invalid fields. To show this, I included a simple rule for determining if a given string is an invalid security or a field: if the string starts with 'Z'.
* If you request information for the security "ZYZZ US EQUITY", you will see error information in the response. This is true for all five request types.
* If you request the field "ZBID" for Reference Data Requests, Historic Data Requests, or Market Data Subscriptions, you will see error information in the response. Intraday Tick and Bar Requests are different. Each supports a small set of fields (eventTypes). If you request the field "ZBID", that line of code will throw an exception. The actual Bloomberg API throws an exception in this situation.

**Bulk Fields and Overrides** Some Bloomberg fields accept overrides to change the way data is returned. Some Bloomberg fields return bulk data as opposed to a single piece of data. Some Bloomberg fields are both: they accept overrides and return bulk data. I included support for one bulk field that accepts overrides in order to show the user how to request a field and handle its response. This field is called CHAIN_TICKERS and it returns information about equity options available for a requested equity. The user can use several overrides to specify which types of options to return. The overrides are:
* CHAIN_POINTS_OVRD: this is an integer which determines the number of options to return. The default value is one.
* CHAIN_EXP_DT_OVRD: this is a string representing a date (format: yyyyMMdd) that determines which option maturity to return. The default is to return options that expire in 20 days. (Please note that this is fabricated. I don't return any real information and the chances that options that expire in exactly 20 days for a given equity are small).
* CHAIN_PUT_CALL_TYPE_OVRD: this is either "P" or "C" and it determines whether the code returns puts or calls. The default is "C".

The real CHAIN_TICKERS field allows for several other overrides, but I make no attempt to emulate them. I would need real data to do so, and actually providing that data is difficult at best. The purpose for including CHAIN_TICKERS is simply to show how a user can include overrides for fields, and inspect the bulk data that is returned.

**Enumerations** One data type that appears in some Bloomberg API responses is an enumeration. IntradayTickRequests include elements with the name type that hold values of a certain enumeration. My code treats them as strings instead. Whether string or enumeration, you can call GetValueAsString() on this type element to get its value. This will of course work with the actual Bloomberg API. I can fix this in the emulator, but I've deemed it a low-priority issue.

**Languages and Operating Systems** The Bloomberg API Emulator right now supports .Net code running on Windows (.Net 4.0 or above) and Java. It also supports C++ code which I've tested only on a Windows computer. The [Bloomberg API Open Market Initiative website](http://www.openbloomberg.com/open-api/) offers code for several operating systems and at least two programming languages per available operating system. I have the strongest experience with C# code on Windows. I am working on porting my code to C++ now and possibly other languages later.

> **Java**: My Java code supports all five of the requests that my C# code supports. This project is my second Java project ever. My first is Hello World. That should show the extent of my Java experience. I am learning Java as I go. For example, I learned that Java doesn't have the internal keyword that C# has. I don't know a good substitute. As I wrote the code, parts of it should not be visible to the Bloomberg API Emulator user, but I don't know how to hide them.
>
> For instance, I declared the constructor for RequestIntradayBar public. This means that the user can create a RequestIntradayBar object, and might wrongly assume that this is possible with the actual Bloomberg API. I can't give the contructor package-local scope because it needs to be accessible in the BEmu package while defined in the BEmu.IntradayBarRequest package. I don't know how to handle this in Java (In C# I declared the scope internal). My code probably has other peculiarities that the seasoned Java coder would find laughable.
>
> **C++**: I finished porting the emulator to C++ starting with version 1.1.2. This port provides support for all the same requests that the C# and Java ports support: Intraday Bar Requests, Intraday Tick Requests, Historical Data Requests, Reference Data Requests, and Market Data Subscriptions. My C++ is pretty rusty and probably also laughable at points. For instance, I never deallocate the Message and Element types that I create because I haven't been able to figure out how the actual Bloobmerg API deallocates this memory. I don't consider this a problem though because I didn't design the emulator for performance. In my code I use Boost for handling datetimes internally though I don't know how the actual Bloomberg API handles datetimes. I've only built my code in Visual Studio 2010 so I don't if it will work in Linux, Solaris, or OS X. I can't figure out how to properly reference the BEmu_cpp.dll and BEmu_cpp.lib files in the Examples_cpp project. As a workaround, I included a post-build script in the BEmu_cpp project that copies these files for the Examples_cpp project.

**Errors** The actual Bloomberg API will include error messages in the response if you request a field incorrectly or request information for a security that doesn't exist, or for many other reasons. I put very little effort into replicating error messages because I don't find it productive. If for instance you request the CHAIN_TICKERS field for a stock option, my code simply ignores that field whereas the Bloomberg API will put an error message in the response. In either case it is safe to ignore the fact that you requested a field that doesn't exist for a given security. It is easy to check if CHAIN_TICKERS exists in the response.

**Other** When building the Bloomberg API Emulator, I had to rely on educated guesses and context clues to determine how the actual Bloomberg API would handle requests and responses. For example, I can still only guess at the difference between Elements and Values. This means that I can't guarantee that the Bloomberg API Emulator acts exactly the same as how the actual Bloomberg API acts.
