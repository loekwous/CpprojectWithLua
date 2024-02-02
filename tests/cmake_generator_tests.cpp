#include <gtest/gtest.h>

extern "C"
{
#include "cmake_generator.h"
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
        (void)CMAKE_GENERATOR_close(&cmake_generator);
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
    ::testing::Values( // Valid target names
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

TEST(CMakeGeneratorTests, InitWithNullReturnFail)
{
    const int RETURN_VALUE = CMAKE_GENERATOR_init(NULL);
    EXPECT_EQ(RETURN_VALUE, RET_ERR_KEY);
}

TEST(CMakeGeneratorTests, successfullyInitialized)
{
    struct CMakeGenerator generator;
    const int RETURN_VALUE = CMAKE_GENERATOR_init(&generator);
    EXPECT_EQ(RETURN_VALUE, RET_OK);
}

TEST(CMakeGeneratorTests, successfullyClosed)
{
    struct CMakeGenerator generator;
    (void)CMAKE_GENERATOR_init(&generator);
    const int RETURN_VALUE = CMAKE_GENERATOR_close(&generator);
    EXPECT_EQ(RETURN_VALUE, RET_OK);
}

TEST_F(CMakeGeneratorFixture, AddTargetNameNull)
{
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target(&cmake_generator, NULL, CMakeTargetType::Executable);
    EXPECT_EQ(RETURN_VALUE, RET_ERR_KEY);
}

TEST_P(CMakeGeneratorValidNames, AddTargetNamevalid)
{
    const char* target_name = GetParam();
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target(&cmake_generator, target_name, CMakeTargetType::Executable);
    EXPECT_EQ(RETURN_VALUE, RET_OK);
}

TEST_P(CMakeGeneratorInvalidNames, AddTargetInvalidNames)
{
    const char *target_name = GetParam();
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target(&cmake_generator, target_name, CMakeTargetType::Executable);
    EXPECT_EQ(RETURN_VALUE, RET_ERR_KEY);
}

TEST_P(CMakeGeneratorValidNames, NonExistingTargetNames)
{
    const char *target_name = GetParam();
    const int RETURN_VALUE = CMAKE_GENERATOR_target_exists(&cmake_generator, target_name);
    EXPECT_EQ(RETURN_VALUE, RET_ERR_FAIL);
}

TEST_P(CMakeGeneratorValidNames, ExistingTargetNames)
{
    const char *target_name = GetParam();
    (void)CMAKE_GENERATOR_add_target(&cmake_generator, target_name, CMakeTargetType::Executable);
    const int RETURN_VALUE = CMAKE_GENERATOR_target_exists(&cmake_generator, target_name);
    EXPECT_EQ(RETURN_VALUE, RET_OK);
}
