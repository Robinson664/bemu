cmake_minimum_required (VERSION 2.8)
project (HistoricalDataRequest)

set(sources
    HistoricElement.cpp
    HistoricElementDateTime.cpp
    HistoricElementDouble.cpp
    HistoricElementErrorInfo.cpp
    HistoricElementFieldDataArray.cpp
    HistoricElementFieldData.cpp
    HistoricElementFieldExceptionsArray.cpp
    HistoricElementFieldExceptions.cpp
    HistoricElementInt.cpp
    HistoricElementSecurityData.cpp
    HistoricElementSecurityError.cpp
    HistoricElementString.cpp
    HistoricEvent.cpp
    HistoricMessage.cpp
    HistoricRequest.cpp
    HistoricRequestElementBool.cpp
    HistoricRequestElementDate.cpp
    HistoricRequestElementInt.cpp
    HistoricRequestElementStringArray.cpp
    HistoricRequestElementString.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})
