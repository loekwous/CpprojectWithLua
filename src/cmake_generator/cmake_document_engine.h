#ifndef CMAKE_DOCUMENT_ENGINE_H_
#define CMAKE_DOCUMENT_ENGINE_H_

#include "cmake_types.h"

int CMAKE_DOCUMENT_ENGINE_get_project(struct CMakeGenerator *generator, char *text_buffer, size_t text_buffer_size);

int CMAKE_DOCUMENT_ENGINE_get_cmake_required_version(char *text_buffer, size_t text_buffer_size);

int CMAKE_DOCUMENT_ENGINE_add_target(struct CMakeTarget *target, char *text_buffer, size_t text_buffer_size);

int CMAKE_DOCUMENT_ENGINE_link_for_target(struct CMakeTarget *target, char *text_buffer, size_t text_buffer_size);

#endif // CMAKE_DOCUMENT_ENGINE_H_