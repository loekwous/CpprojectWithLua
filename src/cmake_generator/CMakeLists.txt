
add_library(cmake-generator STATIC "cmake_generator.c")

target_link_libraries(cmake-generator generics)

target_include_directories(cmake-generator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})