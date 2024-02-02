
include(FetchContent)

function(get_google_test)

    set(GTEST_TAG "v1.13.0")
    set(GTEST_URL "https://github.com/google/googletest.git")

    FetchContent_Declare(gtest
        GIT_REPOSITORY 
        ${GTEST_URL}
        GIT_TAG
        ${GTEST_TAG}
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(gtest)

endfunction()

macro(add_gtest_executable gtest_target_name)
    set(positional_args SOURCES DEPENDENCIES)
    cmake_parse_arguments(gtest_args "" "" "${positional_args}" ${ARGN})

    enable_testing()
    message(STATUS "Added test \"${gtest_target_name}\" with sources: ${gtest_args_SOURCES}")

    add_executable(
    ${gtest_target_name}
    ${gtest_args_SOURCES}
    )
    target_link_libraries(
    ${gtest_target_name}
    GTest::gtest_main
    )

    if(gtest_args_DEPENDENCIES)
        message(STATUS "For library ${gtest_target_name} adding dependencies: ${gtest_args_DEPENDENCIES}")
        target_link_libraries(${gtest_target_name} ${gtest_args_DEPENDENCIES})
    endif()

    include(GoogleTest)
    gtest_discover_tests(${gtest_target_name})

endmacro()
