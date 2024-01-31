cmake_minimum_required(VERSION 3.22.1)

project(LuaApplication VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/LuaLibrary.cmake)
include(cmake/GoogleTest.cmake)

get_lua_library(
    LUA_VERSION 5.4.6
    HASH 7d5ea1b9cb6aa0b59ca3dde1c6adcb57ef83a1ba8e5432c0ecd06bf439b3ad88
    DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/LuaLibrary
)



if(NOT TEST)
    message(STATUS "Configuring for application")
    add_executable(CpprojectWithLua "main.c")
    target_link_libraries(CpprojectWithLua LibLua)
else()
    get_google_test()
    enable_testing()
endif()
add_subdirectory(tests)






