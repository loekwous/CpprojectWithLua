
if(TEST)
    message(STATUS "Configuring some test")    
    add_gtest_executable(cmake-generator-tests SOURCES cmake_generator_tests.cpp DEPENDENCIES cmake-generator)
    add_gtest_executable(cmake-document-engine-tests SOURCES cmake_document_engine_tests.cpp DEPENDENCIES cmake-generator)
endif()