cmake_minimum_required (VERSION 2.8)
project (Examples_cpp)

find_package(Threads REQUIRED)
get_target_property(BEMU_INCLUDES BEmu_cpp INCLUDE_DIRECTORIES)

include_directories(headers)
include_directories(${BEMU_INCLUDES})

set(sources
    src/HistoricalDataRequest.cpp
    src/IntradayBarRequest.cpp
    src/IntradayTickRequest.cpp
    src/main.cpp
    src/MarketDataRequest.cpp
    src/ReferenceDataRequest.cpp
    src/SubscriptionEventHandler.cpp
)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME}
    BEmu_cpp
    ${CMAKE_THREAD_LIBS_INIT})
