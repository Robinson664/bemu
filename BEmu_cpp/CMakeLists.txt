cmake_minimum_required (VERSION 2.8)
project (BEmu_cpp)

include_directories(headers)

add_subdirectory(src/BloombergTypes)
add_subdirectory(src/HistoricalDataRequest)
add_subdirectory(src/IntradayBarRequest)
add_subdirectory(src/IntradayTickRequest)
add_subdirectory(src/MarketDataRequest)
add_subdirectory(src/ReferenceDataRequest)
add_subdirectory(src/Types)

add_library(${PROJECT_NAME} SHARED
    $<TARGET_OBJECTS:Types>
    $<TARGET_OBJECTS:BloombergTypes>
    $<TARGET_OBJECTS:HistoricalDataRequest>
    $<TARGET_OBJECTS:IntradayBarRequest>
    $<TARGET_OBJECTS:IntradayTickRequest>
    $<TARGET_OBJECTS:MarketDataRequest>
    $<TARGET_OBJECTS:ReferenceDataRequest>
)

target_link_libraries(${PROJECT_NAME}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_DATETIME_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
)
