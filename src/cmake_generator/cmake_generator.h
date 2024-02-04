#ifndef CMAKE_GENERATOR_H_
#define CMAKE_GENERATOR_H_

#include "error_values.h"

#include "cmake_target.h"

#include <stddef.h>

#include "cmake_types.h"

int CMAKE_GENERATOR_init(struct CMakeGenerator *generator);

int CMAKE_GENERATOR_set_version(struct CMakeGenerator *generator, size_t major_version, size_t minor_version, size_t patch_version);

int CMAKE_GENERATOR_set_project_name(struct CMakeGenerator *generator, const char *project_name);

int CMAKE_GENERATOR_destroy(struct CMakeGenerator *generator);

int CMAKE_GENERATOR_generate(struct CMakeGenerator *generator, char *const buffer, size_t buffer_size);

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
int CMAKE_GENERATOR_add_target_dependency(struct CMakeGenerator *generator, const char *target_name, const char *dependency_name);

/**
 * Checks if a target with the given name exists in the current project.
 *
 * @param target_name the name of the target to check for
 * @return RET_OK if the target exists, RET_ERR_FAIL otherwise
 */
int CMAKE_GENERATOR_target_exists(struct CMakeGenerator *generator, const char *target_name);

/**
 * Returns the target with the given name, or NULL if no target with the given name exists.
 *
 * @param generator the generator to search in
 * @param target_name the name of the target to search for
 * @return the target with the given name, or NULL if no target with the given name exists
 */
struct CMakeTarget *CMAKE_GENERATOR_get_target(struct CMakeGenerator *generator, const char *target_name);

#endif // CMAKE_GENERATOR_H_