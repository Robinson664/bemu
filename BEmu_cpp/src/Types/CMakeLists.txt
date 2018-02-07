cmake_minimum_required (VERSION 2.8)
project (Types)

set(sources
    BEmuTimer.cpp
    CanConvertToStringType.cpp
    DisplayFormats.cpp
    IndentType.cpp
    ObjectType.cpp
    RandomDataGenerator.cpp
    Rules.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})
