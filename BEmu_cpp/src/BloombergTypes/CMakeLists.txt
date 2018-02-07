cmake_minimum_required (VERSION 2.8)
project (BloombergTypes)

set(sources
    Constant.cpp
    ConstantList.cpp
    CorrelationId.cpp
    Datetime.cpp
    Element.cpp
    ElementPtr.cpp
    Event.cpp
    EventPtr.cpp
    Message.cpp
    MessageIterator.cpp
    MessagePtr.cpp
    Name.cpp
    Request.cpp
    RequestPtr.cpp
    SchemaElementDefinition.cpp
    SchemaTypeDefinition.cpp
    Service.cpp
    ServiceRefData.cpp
    Session.cpp
    SessionOptions.cpp
    SessionTimerFunction.cpp
    Subscription.cpp
    SubscriptionList.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})
