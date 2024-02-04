#include "cmake_generator.h"

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "cmake_document_engine.h"

int CMAKE_GENERATOR_init(struct CMakeGenerator *generator)
{
    if (generator == NULL)
    {
        return RET_ERR_KEY;
    }
    generator->target_count = 0;
    // Placeholder
    generator->targets = (struct CMakeTarget **)calloc(0, sizeof(struct CMakeTarget *));

    return (generator->targets != NULL) ? RET_OK : RET_ERR_ALLOC;
}

int CMAKE_GENERATOR_destroy(struct CMakeGenerator *generator)
{
    if (generator == NULL)
    {
        return RET_ERR_KEY;
    }

    for (size_t target = 0; target < generator->target_count; target++)
    {
        free(generator->targets[target]);
    }
    free(generator->targets);

    return RET_OK;
}

int CMAKE_GENERATOR_set_project_name(struct CMakeGenerator *generator, const char *project_name)
{
    if (generator == NULL || project_name == NULL)
    {
        return RET_ERR_KEY;
    }
    generator->project_name = strdup(project_name);
    return (generator->project_name != NULL) ? RET_OK : RET_ERR_ALLOC;
}

int CMAKE_GENERATOR_generate(struct CMakeGenerator *generator, char *const buffer, size_t buffer_size)
{
    if (generator == NULL || buffer == NULL || buffer_size == 0)
    {
        return 0;
    }

    char *practical_buffer = buffer;
    char *buffer_end = buffer + buffer_size;

    practical_buffer += CMAKE_DOCUMENT_ENGINE_get_cmake_required_version(practical_buffer, buffer_end - practical_buffer);
    practical_buffer += CMAKE_DOCUMENT_ENGINE_get_project(generator, practical_buffer, buffer_end - practical_buffer);
    for (size_t target_index = 0; target_index < generator->target_count; target_index++)
    {
        struct CMakeTarget *target = generator->targets[target_index];
        practical_buffer += CMAKE_DOCUMENT_ENGINE_add_target(target, practical_buffer, buffer_end - practical_buffer);
        practical_buffer += CMAKE_DOCUMENT_ENGINE_link_for_target(target, practical_buffer, buffer_end - practical_buffer);
    }
    return (practical_buffer - buffer) + 1;
}

int CMAKE_GENERATOR_set_version(struct CMakeGenerator *generator, size_t major_version, size_t minor_version, size_t patch_version)
{
    generator->major_version = major_version;
    generator->minor_version = minor_version;
    generator->patch_version = patch_version;
    return RET_OK;
}

int CMAKE_GENERATOR_add_target(struct CMakeGenerator *generator, const char *target_name, enum CMakeTargetType type)
{
    if ((generator == NULL) || (target_name == NULL))
    {
        return RET_ERR_KEY;
    }

    if (CMAKE_GENERATOR_target_exists(generator, target_name) == RET_OK)
    {
        return RET_ERR_FAIL;
    }

    struct CMakeTarget *target = CMAKE_TARGET_create(target_name, type);

    if (target == NULL)
    {
        return CMAKE_TARGET_get_error();
    }

    // Reallocate generator targets array
    generator->targets = (struct CMakeTarget **)realloc(generator->targets, (generator->target_count + 1) * sizeof(struct CMakeTarget *));

    if (generator->targets == NULL)
    {
        return RET_ERR_ALLOC;
    }

    generator->targets[generator->target_count] = target;
    generator->target_count++;

    return RET_OK;
}

int CMAKE_GENERATOR_add_target_dependency(struct CMakeGenerator *generator, const char *target_name, const char *dependency_name)
{
    if ((generator == NULL) || (target_name == NULL) || (dependency_name == NULL))
    {
        return RET_ERR_KEY;
    }

    struct CMakeTarget *target = CMAKE_GENERATOR_get_target(generator, target_name);
    struct CMakeTarget *dependency = CMAKE_GENERATOR_get_target(generator, dependency_name);

    return CMAKE_TARGET_add_dependency(target, dependency);
}

int CMAKE_GENERATOR_target_exists(struct CMakeGenerator *generator, const char *target_name)
{
    if (generator == NULL || target_name == NULL)
    {
        return RET_ERR_FAIL;
    }

    for (size_t target_index = 0; target_index < generator->target_count; target_index++)
    {
        if (strcmp(generator->targets[target_index]->target_name, target_name) == 0)
        {
            return RET_OK;
        }
    }
    return (CMAKE_GENERATOR_get_target(generator, target_name) == NULL) ? RET_ERR_FAIL : RET_OK;
}

struct CMakeTarget *CMAKE_GENERATOR_get_target(struct CMakeGenerator *generator, const char *target_name)
{
    if (generator == NULL || target_name == NULL)
    {
        return NULL;
    }

    if ((generator->target_count == 0) || generator->targets == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < generator->target_count; i++)
    {
        if (generator->targets[i]->target_name == NULL)
        {
            continue;
        }
        if (strcmp(generator->targets[i]->target_name, target_name) == 0)
        {
            return generator->targets[i];
        }
    }
    return NULL;
}
