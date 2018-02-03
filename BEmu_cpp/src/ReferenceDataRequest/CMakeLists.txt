cmake_minimum_required (VERSION 2.8)
project (ReferenceDataRequest)

set(sources
    ReferenceElementArrayChainTickers.cpp
    ReferenceElementArrayChainTickersItem.cpp
    ReferenceElementArray.cpp
    ReferenceElement.cpp
    ReferenceElementDateTime.cpp
    ReferenceElementDouble.cpp
    ReferenceElementErrorInfo.cpp
    ReferenceElementFieldData.cpp
    ReferenceElementFieldExceptionsArray.cpp
    ReferenceElementFieldExceptions.cpp
    ReferenceElementInt.cpp
    ReferenceElementObject.cpp
    ReferenceElementSecurityDataArray.cpp
    ReferenceElementSecurityData.cpp
    ReferenceElementSecurityError.cpp
    ReferenceElementString.cpp
    ReferenceEvent.cpp
    ReferenceMessage.cpp
    ReferenceRequest.cpp
    ReferenceRequestElementOverrideArray.cpp
    ReferenceRequestElementOverride.cpp
    ReferenceRequestElementStringArray.cpp
    ReferenceRequestElementString.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})
