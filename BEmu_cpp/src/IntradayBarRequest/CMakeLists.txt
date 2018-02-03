cmake_minimum_required (VERSION 2.8)
project (IntradayBarRequest)

set(sources
    IntradayBarElementData.cpp
    IntradayBarElementDateTime.cpp
    IntradayBarElementDouble.cpp
    IntradayBarElementInt.cpp
    IntradayBarElementLong.cpp
    IntradayBarElementResponseError.cpp
    IntradayBarElementString.cpp
    IntradayBarElementTickDataArray.cpp
    IntradayBarElementTickData.cpp
    IntradayBarEvent.cpp
    IntradayBarMessage.cpp
    IntradayBarRequest.cpp
    IntradayBarRequestElementBool.cpp
    IntradayBarRequestElementInt.cpp
    IntradayBarRequestElementStringArray.cpp
    IntradayBarRequestElementString.cpp
    IntradayBarRequestElementTime.cpp
    IntradayBarTickDataType.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})
