#ifndef CMAKE_TYPES_H_
#define CMAKE_TYPES_H_

#include <stddef.h>

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
    char *project_name;
    size_t major_version;
    size_t minor_version;
    size_t patch_version;
};

#endif /* CMAKE_TYPES_H_ */