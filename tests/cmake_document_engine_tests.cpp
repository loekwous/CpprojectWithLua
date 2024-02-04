#include <gtest/gtest.h>

extern "C"
{
#include "cmake_document_engine.h"
#include "cmake_target.h"
}

TEST(CMakeDocumentEngineTests, link_for_target_nullAsTarget)
{
    char buffer[1024];
    const int RETURN_VALUE = CMAKE_DOCUMENT_ENGINE_link_for_target(NULL, buffer, 1024);
    EXPECT_EQ(RETURN_VALUE, 0);
}

TEST(CMakeDocumentEngineTests, link_for_target_nullAsBuffer)
{
    struct CMakeTarget *target = CMAKE_TARGET_create("my_target", Executable);
    struct CMakeTarget *dep = CMAKE_TARGET_create("my_target", StaticLibrary);
    (void)CMAKE_TARGET_add_dependency(target, dep);
    const int RETURN_VALUE = CMAKE_DOCUMENT_ENGINE_link_for_target(target, NULL, 1024);

    CMAKE_TARGET_destroy(target);
    CMAKE_TARGET_destroy(dep);

    EXPECT_EQ(RETURN_VALUE, 0);
}

TEST(CMakeDocumentEngineTests, link_for_target_zeroBufferSize)
{
    char buffer[1024];
    struct CMakeTarget *target = CMAKE_TARGET_create("my_target", Executable);
    struct CMakeTarget *dep = CMAKE_TARGET_create("my_target", StaticLibrary);
    (void)CMAKE_TARGET_add_dependency(target, dep);
    const int RETURN_VALUE = CMAKE_DOCUMENT_ENGINE_link_for_target(target, buffer, 0);

    CMAKE_TARGET_destroy(target);
    CMAKE_TARGET_destroy(dep);

    EXPECT_EQ(RETURN_VALUE, 0);
}

TEST(CMakeDocumentEngineTests, link_for_target_successFull)
{
    const char *expected_string = "target_link_libraries(my_target my_dep my_dep2)";

    char buffer[1024];
    struct CMakeTarget *target = CMAKE_TARGET_create("my_target", Executable);
    struct CMakeTarget *dep = CMAKE_TARGET_create("my_dep", StaticLibrary);
    struct CMakeTarget *dep2 = CMAKE_TARGET_create("my_dep2", StaticLibrary);
    (void)CMAKE_TARGET_add_dependency(target, dep);
    (void)CMAKE_TARGET_add_dependency(target, dep2);
    const int RETURN_VALUE = CMAKE_DOCUMENT_ENGINE_link_for_target(target, buffer, 1024);

    CMAKE_TARGET_destroy(target);
    CMAKE_TARGET_destroy(dep);
    CMAKE_TARGET_destroy(dep2);

    EXPECT_STREQ(buffer, expected_string);
    EXPECT_EQ(RETURN_VALUE, strlen(expected_string));
}

TEST(CMakeDocumentEngineTests, link_for_target_successFullNoDependencies)
{
    char buffer[1024] = {0};
    struct CMakeTarget *target = CMAKE_TARGET_create("my_target", Executable);
    const int RETURN_VALUE = CMAKE_DOCUMENT_ENGINE_link_for_target(target, buffer, 1024);

    CMAKE_TARGET_destroy(target);

    EXPECT_EQ(strlen(buffer), 0);
    EXPECT_EQ(RETURN_VALUE, 0);
}