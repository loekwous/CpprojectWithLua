cmake_minimum_required(VERSION 3.22.1)

project(LuaApplication VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_C_STANDARD_REQUIRED 11)

include(cmake/LuaLibrary.cmake)
include(cmake/GoogleTest.cmake)

get_lua_library(
    LUA_VERSION 5.4.6
    HASH 7d5ea1b9cb6aa0b59ca3dde1c6adcb57ef83a1ba8e5432c0ecd06bf439b3ad88
    DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/LuaLibrary
)

set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")

add_subdirectory(src)

if(TEST)
    get_google_test()
    enable_testing()
    add_subdirectory(tests)
endif()






