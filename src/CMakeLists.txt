

add_library(generics INTERFACE)
target_include_directories(generics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cmake_generator)

if(NOT TEST)
    add_executable(cpp-project-lua "main.c")
    target_link_libraries(cpp-project-lua cmake-generator lua)
endif()