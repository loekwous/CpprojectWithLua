#include "cmake_generator.h"
#include "error_values.h"

#include <string.h>
#include <stdlib.h>

#define N_TARGET_SLOTS 10

static int name_is_valid_for_target(const char *name)
{
    const char forbidden_chars[] = " \t\n\r\f\v\\/";

    if(name == NULL){
        return RET_ERR_KEY;
    }

    if(strlen(name) == 0){
        return RET_ERR_KEY;
    }
    
    // check if the name contains any forbidden characters
    for (size_t i = 0; i < sizeof(forbidden_chars); i++) {
        if (strchr(name, forbidden_chars[i]) != NULL) {
            return RET_ERR_KEY;
        }
    }

    return RET_OK;
}

int CMAKE_GENERATOR_init(struct CMakeGenerator *generator)
{
    if (generator == NULL)
    {
        return RET_ERR_KEY;
    }
    generator->target_count = 0;
    generator->targets = (struct CMakeTarget **)calloc(N_TARGET_SLOTS, sizeof(struct CMakeTarget *));

    return (generator->targets != NULL) ? RET_OK : RET_ERR_ALLOC;
}

int CMAKE_GENERATOR_close(struct CMakeGenerator *generator)
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

int CMAKE_GENERATOR_generate(struct CMakeGenerator *generator)
{
    return 0;
}

int CMAKE_GENERATOR_add_target(struct CMakeGenerator *generator, const char *target_name, enum CMakeTargetType type)
{
    if (generator == NULL || (name_is_valid_for_target(target_name) != RET_OK))
    {
        return RET_ERR_KEY;
    }

    if (CMAKE_GENERATOR_target_exists(generator, target_name) == RET_OK)
    {
        return RET_ERR_FAIL;
    }

    if (generator->target_count == N_TARGET_SLOTS)
    {
        return RET_ERR_FAIL;
    }

    generator->targets[generator->target_count] = (struct CMakeTarget *)calloc(1, sizeof(struct CMakeTarget));

    if(generator->targets[generator->target_count] != NULL){
        generator->targets[generator->target_count]->target_name = (char*)calloc(strlen(target_name) + 1, sizeof(char));
        strncpy(generator->targets[generator->target_count]->target_name, target_name, strlen(target_name) + 1);
        generator->targets[generator->target_count]->target_type = type;
        generator->target_count++;
    }

    return (generator->targets[generator->target_count] != NULL) ? RET_OK : RET_ERR_ALLOC;
}

int CMAKE_GENERATOR_add_target_dependency(struct CMakeGenerator *generator, const char *target_name, char *dependency_name)
{
    return 0;
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
    return RET_ERR_FAIL;
}
