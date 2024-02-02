#ifndef CMAKE_GENERATOR_H_
#define CMAKE_GENERATOR_H_

#include "error_values.h"

enum CMakeTargetType
{
    Executable,
    StaticLibrary,
    SharedLibrary
};

struct CMakeTarget
{
    char *target_name;
    enum CMakeTargetType target_type;
    struct CMakeTarget **dependencies;
    int dependency_count;
};

struct CMakeGenerator
{
    struct CMakeTarget **targets;
    int target_count;
};

int CMAKE_GENERATOR_init(struct CMakeGenerator *generator);

int CMAKE_GENERATOR_close(struct CMakeGenerator *generator);

int CMAKE_GENERATOR_generate(struct CMakeGenerator *generator);

/**
 * Adds a new target to the current project.
 *
 * @param target_name the name of the target to add
 * @param type the type of the target to add
 * @return RET_OK if the target was added successfully, RET_ERR_FAIL otherwise
 */
int CMAKE_GENERATOR_add_target(struct CMakeGenerator *generator, const char *target_name, enum CMakeTargetType type);

/**
 * Adds a new target dependency to the given target.
 *
 * @param target_name the name of the target to add the dependency to
 * @param dependency_name the name of the target that the given target depends on
 * @return RET_OK if the dependency was added successfully, RET_ERR_FAIL otherwise
 */
int CMAKE_GENERATOR_add_target_dependency(struct CMakeGenerator *generator, const char *target_name, char *dependency_name);

/**
 * Checks if a target with the given name exists in the current project.
 *
 * @param target_name the name of the target to check for
 * @return RET_OK if the target exists, RET_ERR_FAIL otherwise
 */
int CMAKE_GENERATOR_target_exists(struct CMakeGenerator *generator, const char *target_name);

#endif // CMAKE_GENERATOR_H_