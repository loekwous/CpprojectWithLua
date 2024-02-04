#ifndef CMAKE_GENERATOR_TESTS_H_
#define CMAKE_GENERATOR_TESTS_H_

#include <gtest/gtest.h>

extern "C"
{
#include "cmake_generator.h"
}

static std::string error_to_string(int error)
{
    switch (error)
    {
    case RET_OK:
        return "OK";
    case RET_ERR_FAIL:
        return "FAIL";
    case RET_ERR_KEY:
        return "KEY";
    case RET_ERR_ALLOC:
        return "ALLOC";
    default:
        return "UNKNOWN";
    };
}

class CMakeGeneratorFixture : public ::testing::Test
{
protected:
    struct CMakeGenerator cmake_generator;
    void SetUp() override
    {
        (void)CMAKE_GENERATOR_init(&cmake_generator);
    }
    void TearDown() override
    {
        (void)CMAKE_GENERATOR_destroy(&cmake_generator);
    }
};

class CMakeGeneratorValidNames : public CMakeGeneratorFixture, public ::testing::WithParamInterface<const char *>
{
};

class CMakeGeneratorInvalidNames : public CMakeGeneratorFixture, public ::testing::WithParamInterface<const char *>
{
};

INSTANTIATE_TEST_SUITE_P(
    CMakeGeneratorInvalidNames,
    CMakeGeneratorInvalidNames,
    ::testing::Values( // Invalid target names
                       // Invalid contains for example a space, is NULL or is empty
        "",
        " ",
        (const char *)NULL,
        "test name",
        "\n"));

// Add values for valid test names
//
INSTANTIATE_TEST_SUITE_P(
    CMakeGeneratorValidNames,
    CMakeGeneratorValidNames,
    ::testing::Values( // Valid target names with underscores and dashes
        "test_target",
        "test-target",
        "test-target-",
        "test_target-123",
        "test_target",
        "TEST_TARGET",
        "test_target_123",
        "TEST_TARGET_123",
        "test_target_123_456",
        "TEST_TARGET_123_456",
        "test_target_123_456_789",
        "TEST_TARGET_123_456_789",
        "test_target_123_456_789_012",
        "TEST_TARGET_123_456_789_012"));

#endif /* CMAKE_GENERATOR_TESTS_H_ */