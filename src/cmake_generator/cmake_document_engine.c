#include "cmake_document_engine.h"

#include <stdio.h>
#include <string.h>

#ifndef CMAKE_MINIMUM_REQUIRED_VERSION
#define CMAKE_MINIMUM_REQUIRED_VERSION "3.22.1"
#endif

#ifndef CMAKE_MINIMUM_REQUIRED_FUNCTION
#define CMAKE_MINIMUM_REQUIRED_FUNCTION "cmake_minimum_required"
#endif

#ifndef CMAKE_TARGET_LINK_LIBRARIES_FUNCTION
#define CMAKE_TARGET_LINK_LIBRARIES_FUNCTION "target_link_libraries"
#endif

#ifndef CMAKE_ADD_EXECUTABLE_FUNCTION
#define CMAKE_ADD_EXECUTABLE_FUNCTION "add_executable"
#endif

#ifndef CMAKE_ADD_LIBRARY_FUNCTION
#define CMAKE_ADD_LIBRARY_FUNCTION "add_library"
#endif

int CMAKE_DOCUMENT_ENGINE_get_project(struct CMakeGenerator *generator, char *text_buffer, size_t text_buffer_size)
{
    if (generator == NULL || text_buffer == NULL || text_buffer_size == 0)
    {
        return RET_ERR_KEY;
    }

    const char *project_input_text = "PROJECT(%s VERSION %lu.%lu.%lu)\n";
    int bytes = snprintf(text_buffer, text_buffer_size, project_input_text, generator->project_name, generator->major_version, generator->minor_version, generator->patch_version);
    return bytes;
}

int CMAKE_DOCUMENT_ENGINE_get_cmake_required_version(char *text_buffer, size_t text_buffer_size)
{
    if (text_buffer == NULL || text_buffer_size == 0)
    {
        return 0;
    }

    char *functional_buffer = text_buffer;

    const char *cmake_required_version_input_text = "%s(VERSION %s)\n";
    functional_buffer += snprintf(functional_buffer, text_buffer_size, cmake_required_version_input_text, CMAKE_MINIMUM_REQUIRED_FUNCTION, CMAKE_MINIMUM_REQUIRED_VERSION);
    return (functional_buffer - text_buffer);
}

int CMAKE_DOCUMENT_ENGINE_add_target(struct CMakeTarget *target, char *text_buffer, size_t text_buffer_size)
{
    if (target == NULL || text_buffer == NULL || text_buffer_size == 0)
    {
        return 0;
    }

    char *functional_buffer = text_buffer;
    char *end_of_buffer = text_buffer + text_buffer_size;

    const char *target_input_text = "%s(%s";

    const char *function_name = (target->target_type == Executable) ? CMAKE_ADD_EXECUTABLE_FUNCTION : CMAKE_ADD_LIBRARY_FUNCTION;

    functional_buffer += snprintf(functional_buffer, end_of_buffer - functional_buffer, target_input_text, function_name, target->target_name);

    if (functional_buffer == text_buffer)
    {
        return 0;
    }

    switch (target->target_type)
    {
    case StaticLibrary:
        functional_buffer += snprintf(functional_buffer, end_of_buffer - functional_buffer, " STATIC)\n");
        break;
    case SharedLibrary:
        functional_buffer += snprintf(functional_buffer, end_of_buffer - functional_buffer, " SHARED)\n");
        break;
    default:
        functional_buffer += snprintf(functional_buffer, end_of_buffer - functional_buffer, ")\n");
        break;
    };

    return (functional_buffer - text_buffer);
}

int CMAKE_DOCUMENT_ENGINE_link_for_target(struct CMakeTarget *target, char *const text_buffer, size_t text_buffer_size)
{
    if (target == NULL || text_buffer == NULL || text_buffer_size == 0)
    {
        return 0;
    }

    if (target->dependency_count == 0)
    {
        return 0;
    }

    char *functional_buffer = text_buffer;
    char *end_of_buffer = text_buffer + text_buffer_size;

    const char *link_for_target_input_text = "%s(%s";
    functional_buffer += snprintf(functional_buffer, end_of_buffer - functional_buffer, link_for_target_input_text, CMAKE_TARGET_LINK_LIBRARIES_FUNCTION, target->target_name);

    if (functional_buffer <= text_buffer)
    {
        return 0;
    }

    for (size_t i = 0; i < target->dependency_count; i++)
    {
        struct CMakeTarget *dependency = target->dependencies[i];
        char *functional_buffer_backup = functional_buffer;
        functional_buffer += snprintf(functional_buffer, end_of_buffer - functional_buffer, " %s", dependency->target_name);
        if (functional_buffer <= functional_buffer_backup)
        {
            return 0;
        }
    }
    functional_buffer += snprintf(functional_buffer, end_of_buffer - functional_buffer, ")\n");

    return (functional_buffer - text_buffer);
}