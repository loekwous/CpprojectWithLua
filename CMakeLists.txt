cmake_minimum_required(VERSION 3.22.1)

project(LuaApplication VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(LUA_VERSION "5.4.6")
set(LUA_URL "https://www.lua.org/ftp/lua-${LUA_VERSION}.tar.gz")

FetchContent_Declare(
    LuaLibDownload
    PREFIX lib
    URL ${LUA_URL}
    URL_HASH SHA256=7d5ea1b9cb6aa0b59ca3dde1c6adcb57ef83a1ba8e5432c0ecd06bf439b3ad88
    SOURCE_DIR ${CMAKE_BINARY_DIR}/LuaLibDownload
    )

    FetchContent_MakeAvailable(LuaLibDownload)
    
set(LUA_LIB_SOURCE_DIR ${CMAKE_BINARY_DIR}/LuaLibDownload/src)
message("LuaLib source dir: ${LUA_LIB_SOURCE_DIR}")

set(LUA_LIB_SOURCES 
lbaselib.c
lmathlib.c
lstring.c
lparser.c
ldo.c
lutf8lib.c
lzio.c
lctype.c
lmem.c
lstrlib.c
lundump.c
loslib.c
ldebug.c
lobject.c
ldump.c
ldblib.c
ltm.c
ltable.c
lstate.c
lua.c
loadlib.c
lcorolib.c
lcode.c
lapi.c
lgc.c
lvm.c
lfunc.c
luac.c
lauxlib.c
ltablib.c
linit.c
lopcodes.c
llex.c
liolib.c)

list(TRANSFORM LUA_LIB_SOURCES PREPEND ${LUA_LIB_SOURCE_DIR}/)

add_library(LibLua STATIC ${LUA_LIB_SOURCES})
target_compile_options(LibLua PRIVATE -std=gnu99 -w)
target_include_directories(LibLua INTERFACE ${LUA_LIB_SOURCE_DIR})
target_link_libraries(LibLua m)
target_link_libraries(LibLua c)

add_executable(LuaApp "main.c")
target_link_libraries(LuaApp LibLua)
add_dependencies(LuaApp LibLua)









