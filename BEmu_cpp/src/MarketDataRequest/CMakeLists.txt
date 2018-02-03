cmake_minimum_required (VERSION 2.8)
project (MarketDataRequest)

set(sources
    MarketElementBool.cpp
    MarketElementDatetime.cpp
    MarketElementDouble.cpp
    MarketElementExceptionsArray.cpp
    MarketElementExceptions.cpp
    MarketElementInt.cpp
    MarketElementNull.cpp
    MarketElementReason.cpp
    MarketElementServiceStatus.cpp
    MarketElementString.cpp
    MarketElementSubscriptionCanceled.cpp
    MarketElementSubscriptionCancelReason.cpp
    MarketElementSubscriptionStarted.cpp
    MarketEvent.cpp
    MarketMessageServiceStatus.cpp
    MarketMessageSessionOpened.cpp
    MarketMessageSubscriptionCanceled.cpp
    MarketMessageSubscriptionData.cpp
    MarketMessageSubscriptionFailure.cpp
    MarketMessageSubscriptionStarted.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})
