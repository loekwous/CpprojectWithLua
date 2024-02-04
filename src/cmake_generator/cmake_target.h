#ifndef CMAKE_TARGET_H_
#define CMAKE_TARGET_H_

#include "cmake_types.h"

struct CMakeTarget *CMAKE_TARGET_create(const char *target_name, enum CMakeTargetType target_type);

int CMAKE_TARGET_add_dependency(struct CMakeTarget *target, struct CMakeTarget *dependency);

int CMAKE_TARGET_has_dependency(struct CMakeTarget *target, struct CMakeTarget *dependency);

int CMAKE_TARGET_destroy(struct CMakeTarget *target);

int CMAKE_TARGET_get_error();

#endif /* CMAKE_TARGET_H_ */