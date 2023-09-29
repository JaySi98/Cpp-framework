# Cpp-framework 

### About 
This project is an attempt to create c++ framework that can later be used to speed up other projects.

## TODO
* communication between components
* reading config files
* funcking around and finding out

## Features
* Unit testing using GoogleTest framework
* Documentation generation using Doxygen
* Code formatting and analizing uing clang-format and clang-tidy
* CI workflows for Windows, Linux and MacOS using GitHub Actions
* Building project as an executable, library or header only library
* Sanitizers
* Basics scripts for build mentioned features

## Requirements 
In order to be able to use this template, you must have installed: 
* **CMake** - version 3.15 and above 
* **C++ Compiler** - must support C++ 17 standard 
* **Doxygen** - for ability to generate docs
* **GoogleTest** - for unit testing
* **Clang-Tidy** - supported static analizer 
* **Clang-Format** - for code formatting

## Available targets
* **\<project-name\>** - to build project
* **install** - to install project
* **doxygen-docs** - to generate documentation
* **clang-format** - to format code

## usefull commands
* running project
```
./build/bin/Debug/<project-name>
```

* running unit tests(two options)
```
./build/test/UnitTests
```

```
cd build && ctest -C -VV Debug
```

* opening documentation
```
xdg-open docs/html/index.html
```

* installing project
```
cmake --build <build_directory> --target install --config <desired_config> 
```

* uninstalling project
```
sudo xargs rm < build/install_manifest.txt 
```