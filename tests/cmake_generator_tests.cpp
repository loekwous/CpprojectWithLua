#include "cmake_generator_tests.h"

TEST(CMakeGeneratorTests, init_nullAsInput)
{
    const int RETURN_VALUE = CMAKE_GENERATOR_init(NULL);
    EXPECT_EQ(RETURN_VALUE, RET_ERR_KEY);
}

TEST(CMakeGeneratorTests, init_successful)
{
    struct CMakeGenerator generator;
    const int RETURN_VALUE = CMAKE_GENERATOR_init(&generator);
    EXPECT_EQ(RETURN_VALUE, RET_OK);
}

TEST(CMakeGeneratorTests, close_successful)
{
    struct CMakeGenerator generator;
    (void)CMAKE_GENERATOR_init(&generator);
    const int RETURN_VALUE = CMAKE_GENERATOR_destroy(&generator);
    EXPECT_EQ(RETURN_VALUE, RET_OK);
}

TEST_F(CMakeGeneratorFixture, add_target_dependency_nullAsGenerator)
{
    (void)CMAKE_GENERATOR_add_target(&cmake_generator, "exec", CMakeTargetType::Executable);
    (void)CMAKE_GENERATOR_add_target(&cmake_generator, "lib", CMakeTargetType::StaticLibrary);
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target_dependency(NULL, "exec", "lib");
    EXPECT_EQ(RETURN_VALUE, RET_ERR_KEY);
}

TEST_F(CMakeGeneratorFixture, add_target_dependency_nullAsTarget)
{
    (void)CMAKE_GENERATOR_add_target(&cmake_generator, "lib", CMakeTargetType::StaticLibrary);
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target_dependency(&cmake_generator, NULL, "lib");
    EXPECT_EQ(RETURN_VALUE, RET_ERR_KEY);
}

TEST_F(CMakeGeneratorFixture, add_target_dependency_nullAsDependency)
{
    (void)CMAKE_GENERATOR_add_target(&cmake_generator, "exec", CMakeTargetType::Executable);
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target_dependency(&cmake_generator, "exec", NULL);
    EXPECT_EQ(RETURN_VALUE, RET_ERR_KEY);
}

TEST_F(CMakeGeneratorFixture, add_target_dependency_validDependency)
{
    (void)CMAKE_GENERATOR_add_target(&cmake_generator, "exec", CMakeTargetType::Executable);
    (void)CMAKE_GENERATOR_add_target(&cmake_generator, "lib", CMakeTargetType::StaticLibrary);
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target_dependency(&cmake_generator, "exec", "lib");
    EXPECT_EQ(RETURN_VALUE, RET_OK);
}

TEST_F(CMakeGeneratorFixture, add_target_nullTargetName)
{
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target(&cmake_generator, NULL, CMakeTargetType::Executable);
    EXPECT_EQ(RETURN_VALUE, RET_ERR_KEY);
}

TEST_P(CMakeGeneratorValidNames, add_target_validName)
{
    const char *target_name = GetParam();
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target(&cmake_generator, target_name, CMakeTargetType::Executable);
    EXPECT_EQ(RETURN_VALUE, RET_OK) << "Expected " << target_name << " to exist, instead got error: " << error_to_string(RETURN_VALUE);
}

TEST_P(CMakeGeneratorInvalidNames, add_target_invalidNames)
{
    const char *target_name = GetParam();
    const int RETURN_VALUE = CMAKE_GENERATOR_add_target(&cmake_generator, target_name, CMakeTargetType::Executable);
    EXPECT_NE(RETURN_VALUE, RET_OK) << "Expected " << target_name << " to give an error, instead got success";
    EXPECT_NE(RETURN_VALUE, RET_ERR_ALLOC) << "Expected " << target_name << " to return an error, but not an allocation error";
}

TEST_P(CMakeGeneratorValidNames, target_exists_nonExistingTargetNames)
{
    const char *target_name = GetParam();
    const int RETURN_VALUE = CMAKE_GENERATOR_target_exists(&cmake_generator, target_name);
    EXPECT_EQ(RETURN_VALUE, RET_ERR_FAIL);
}

TEST_P(CMakeGeneratorValidNames, target_exists_ExistingTargetNames)
{
    const char *target_name = GetParam();
    (void)CMAKE_GENERATOR_add_target(&cmake_generator, target_name, CMakeTargetType::Executable);
    const int RETURN_VALUE = CMAKE_GENERATOR_target_exists(&cmake_generator, target_name);
    EXPECT_EQ(RETURN_VALUE, RET_OK) << "Expected " << target_name << " to exist, instead got error: " << error_to_string(RETURN_VALUE);
}

TEST_P(CMakeGeneratorValidNames, get_target_ExistingTargetNames)
{
    const char *target_name = GetParam();
    (void)CMAKE_GENERATOR_add_target(&cmake_generator, target_name, CMakeTargetType::Executable);
    const struct CMakeTarget *RETURN_VALUE = CMAKE_GENERATOR_get_target(&cmake_generator, target_name);
    EXPECT_TRUE(RETURN_VALUE != NULL) << "Expected " << target_name << " to exist, instead got a NULL pointer";
}

TEST_P(CMakeGeneratorValidNames, get_target_nonExistingTargetNames)
{
    const char *target_name = GetParam();
    const struct CMakeTarget *RETURN_VALUE = CMAKE_GENERATOR_get_target(&cmake_generator, target_name);
    EXPECT_TRUE(RETURN_VALUE == NULL) << "Expected " << target_name << " to exist, instead got a NULL pointer";
}

TEST_P(CMakeGeneratorValidNames, set_project_name_validNames)
{
    const char *project_name = GetParam();
    int RETURN_VALUE = CMAKE_GENERATOR_set_project_name(&cmake_generator, project_name);
    EXPECT_EQ(RETURN_VALUE, RET_OK) << "Expected " << project_name << " to be valid, instead got error: " << error_to_string(RETURN_VALUE);
}

TEST_P(CMakeGeneratorValidNames, set_project_name_nullGenerator)
{
    const char *project_name = GetParam();
    int RETURN_VALUE = CMAKE_GENERATOR_set_project_name(NULL, project_name);
    EXPECT_EQ(RETURN_VALUE, RET_ERR_KEY) << "Expected a KEY error with project name" << project_name << " and NULL generator, instead got: " << error_to_string(RETURN_VALUE);
}
