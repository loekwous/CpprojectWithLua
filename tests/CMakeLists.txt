
if(TEST)
    message(STATUS "Configuring some test")    
    add_gtest_executable(SomeTest SOURCES mytest.cpp)
endif()