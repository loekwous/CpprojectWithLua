#include "cmake_target.h"

#include <string.h>
#include <stdlib.h>

static int internal_error = RET_OK;

static int name_is_valid_for_target(const char *name)
{
    const char forbidden_chars[] = " \t\n\r\f\v\\/";

    if (name == NULL)
    {
        return RET_ERR_KEY;
    }

    if (strlen(name) == 0)
    {
        return RET_ERR_KEY;
    }

    // check if the name contains any forbidden characters
    for (size_t i = 0; i < sizeof(forbidden_chars) - 1u; i++)
    {
        if (strchr(name, forbidden_chars[i]) != NULL)
        {
            return RET_ERR_KEY;
        }
    }

    return RET_OK;
}

int CMAKE_TARGET_get_error()
{
    int error = internal_error;
    internal_error = RET_OK;
    return error;
}

struct CMakeTarget *CMAKE_TARGET_create(const char *target_name, enum CMakeTargetType target_type)
{
    if (name_is_valid_for_target(target_name) != RET_OK)
    {
        internal_error = RET_ERR_KEY;
        return NULL;
    }

    struct CMakeTarget *target = (struct CMakeTarget *)calloc(1, sizeof(struct CMakeTarget));

    if (target == NULL)
    {
        internal_error = RET_ERR_ALLOC;
        return NULL;
    }

    target->target_name = (char *)calloc(strlen(target_name) + 1, sizeof(char));
    if (target->target_name == NULL)
    {
        internal_error = RET_ERR_ALLOC;
        free(target);
        return NULL;
    }

    target->dependency_count = 0;
    target->target_type = target_type;
    strncpy(target->target_name, target_name, strlen(target_name));

    return target;
}

int CMAKE_TARGET_add_dependency(struct CMakeTarget *target, struct CMakeTarget *dependency)
{
    if (target == NULL || dependency == NULL)
    {
        return RET_ERR_KEY;
    }

    if (target->dependencies == NULL)
    {
        target->dependencies = (struct CMakeTarget **)calloc(1, sizeof(struct CMakeTarget *));
    }
    else
    {

        if (CMAKE_TARGET_has_dependency(target, dependency) == RET_OK)
        {
            return RET_ERR_FAIL;
        }

        target->dependencies = (struct CMakeTarget **)realloc(target->dependencies, (target->dependency_count + 1) * sizeof(struct CMakeTarget *));
    }

    if (target->dependencies == NULL)
    {
        target->dependency_count = 0;
        return RET_ERR_ALLOC;
    }

    target->dependencies[target->dependency_count] = dependency;
    target->dependency_count++;
    return RET_OK;
}

int CMAKE_TARGET_has_dependency(struct CMakeTarget *target, struct CMakeTarget *dependency)
{
    if (target == NULL || dependency == NULL)
    {
        return RET_ERR_KEY;
    }

    if (target->dependency_count == 0 || target->dependencies == NULL)
    {
        return RET_ERR_FAIL;
    }

    for (int i = 0; i < target->dependency_count; i++)
    {
        if (target->dependencies[i] == dependency)
        {
            return RET_OK;
        }
    }

    return RET_ERR_FAIL;
}

int CMAKE_TARGET_destroy(struct CMakeTarget *target)
{
    if (target == NULL)
    {
        return RET_ERR_KEY;
    }

    if (target->target_name != NULL)
    {
        free(target->target_name);
    }

    if (target->dependencies != NULL)
    {
        free(target->dependencies);
    }

    free(target);
    return RET_OK;
}