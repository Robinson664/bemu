cmake_minimum_required (VERSION 2.8)
project (IntradayTickRequest)

set(sources
    IntradayTickElement.cpp
    IntradayTickElementDataArray.cpp
    IntradayTickElementData.cpp
    IntradayTickElementDataParent.cpp
    IntradayTickElementDateTime.cpp
    IntradayTickElementDouble.cpp
    IntradayTickElementInt.cpp
    IntradayTickElementResponseError.cpp
    IntradayTickElementString.cpp
    IntradayTickElementTuple3.cpp
    IntradayTickEvent.cpp
    IntradayTickMessage.cpp
    IntradayTickRequest.cpp
    IntradayTickRequestElementBool.cpp
    IntradayTickRequestElementInt.cpp
    IntradayTickRequestElementStringArray.cpp
    IntradayTickRequestElementString.cpp
    IntradayTickRequestElementTime.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})
