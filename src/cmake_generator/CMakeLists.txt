
add_library(cmake-generator STATIC "cmake_generator.c" "cmake_target.c" "cmake_document_engine.c")

target_compile_options(cmake-generator PRIVATE "-Wall")

target_link_libraries(cmake-generator generics)

target_include_directories(cmake-generator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})