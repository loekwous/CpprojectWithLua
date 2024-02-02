include(FetchContent)

set(LUA_URL "https://www.lua.org/ftp/lua-")
set(LUA_URL_SUFFIX ".tar.gz")

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
loadlib.c
lcorolib.c
lcode.c
lapi.c
lgc.c
lvm.c
lfunc.c
lauxlib.c
ltablib.c
linit.c
lopcodes.c
llex.c
liolib.c)



function(get_lua_library)
    set(single_value_args LUA_VERSION HASH DOWNLOAD_DIR)

    cmake_parse_arguments(lua_arguments "" "${single_value_args}" "" ${ARGN})

    if(NOT lua_arguments_DOWNLOAD_DIR)
        message(FATAL_ERROR "DOWNLOAD_DIR is required!")
    endif()

    if(NOT lua_arguments_HASH)
        message(STATUS "Downloading LUA version ${lua_arguments_LUA_VERSION} without HASH")
        FetchContent_Declare(
            lua-download
            PREFIX lib
            URL "${LUA_URL}${lua_arguments_LUA_VERSION}${LUA_URL_SUFFIX}"
            SOURCE_DIR ${lua_arguments_DOWNLOAD_DIR}
        )
    else()
    message(STATUS "Downloading LUA version ${lua_arguments_LUA_VERSION} with sha256 HASH")
        FetchContent_Declare(
            lua-download
            PREFIX lib
            URL "${LUA_URL}${lua_arguments_LUA_VERSION}${LUA_URL_SUFFIX}"
            URL_HASH SHA256=${lua_arguments_HASH}
            SOURCE_DIR ${lua_arguments_DOWNLOAD_DIR}
        )
    endif()

    FetchContent_MakeAvailable(lua-download)

    set(LUA_LIB_SOURCE_DIR ${lua_arguments_DOWNLOAD_DIR}/src)
    list(TRANSFORM LUA_LIB_SOURCES PREPEND ${LUA_LIB_SOURCE_DIR}/)

    add_library(lua SHARED ${LUA_LIB_SOURCES})
    target_compile_options(lua PRIVATE -std=gnu99 -w)
    target_include_directories(lua INTERFACE ${LUA_LIB_SOURCE_DIR})
    target_link_libraries(lua m)

endfunction()

