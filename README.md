# CpprojectWithLua
Create a project with the help of Lua. Integrated calls generate interactive objects that will be converted to a templated project. Inject templates to create custom project relations

## The idea
The idea is to make it easier and more versatile to create a project with
dependencies, complexity and version management.

After the creation of a project, there shouldn't be any hassles on how dependencies are organized.

## Functionalities

* Target language
* tasks to run
* OS to use
* Addons to use
* what dependencies to use
* task relations
* file templating

## Example
```lua
semantic_versioning()
application("MyApp", "C")
test("MyApp")
add_dependency("MyApp", "gtest", "1.2.0")
```