cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(LinearObjects VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_library(${PROJECT_NAME} STATIC ${SRC})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /permissive /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PUBLIC -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -Werror)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
