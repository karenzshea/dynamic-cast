cmake_minimum_required(VERSION 3.9)

project(virtual-creatures LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -pedantic -std=c++17")

set(vc_incl_SOURCES
    include)

set(vc_app_SOURCES
    main.cpp)

add_executable(${PROJECT_NAME}
    ${vc_app_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE ${vc_incl_SOURCES})
