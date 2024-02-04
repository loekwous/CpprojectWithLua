#include <stdio.h>
#include <math.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#include <cmake_generator.h>

void test_cmake_generator()
{
  struct CMakeGenerator generator;
  CMAKE_GENERATOR_init(&generator);
  CMAKE_GENERATOR_set_project_name(&generator, "test_project");
  CMAKE_GENERATOR_set_version(&generator, 0, 1, 0);

  CMAKE_GENERATOR_add_target(&generator, "test_target", Executable);
  CMAKE_GENERATOR_add_target(&generator, "test_library", StaticLibrary);
  CMAKE_GENERATOR_add_target(&generator, "test_sharedLibrary", SharedLibrary);

  CMAKE_GENERATOR_add_target_dependency(&generator, "test_target", "test_library");
  CMAKE_GENERATOR_add_target_dependency(&generator, "test_target", "test_sharedLibrary");

  char dataBuffer[1024];

  CMAKE_GENERATOR_generate(&generator, dataBuffer, 1024);

  printf("%s\n", dataBuffer);

  CMAKE_GENERATOR_destroy(&generator);
}

int some_function(lua_State *L)
{
  printf("This is some function\n");
  lua_pushinteger(L, 20);
  return 1;
}

int main(int argc, char *argv[])
{

  test_cmake_generator();

  if (argc < 2)
  {
    fprintf(stderr, "Add file as argument \n");
    return EXIT_FAILURE;
  }

  if (strstr(argv[1], ".lua") == NULL)
  {
    fprintf(stderr, "File should be of .lua extension\n");
    return EXIT_FAILURE;
  }

  const char *luaFileName = argv[1];

  FILE *luaFile = fopen(luaFileName, "r");

  if (luaFile == NULL)
  {
    fprintf(stderr, "File does not exist\n");
    return EXIT_FAILURE;
  }

  fclose(luaFile);

  char buff[256];
  int error;
  lua_State *L = luaL_newstate();
  luaL_openlibs(L); /* opens Lua */

  lua_register(L, "some_function", some_function);

  if (L == NULL)
  {
    fprintf(stderr, "Lua is not initialized properly\n");
    return 1;
  }

  error = luaL_dofile(L, luaFileName);

  if (error)
  {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    lua_pop(L, 1); /* pop error message from the stack */
  }

  lua_close(L);
  return 0;
}

