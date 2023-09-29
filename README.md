# ModernCppTemplate 

### About 
This project is an attempt to create template for C/C++ projects using modern cmake. It's designed to suit my personal requirements, but it might be useful for other developers too. 

### Acknowledgements 
This template is mostly a combination of projects listed below: 
* https://github.com/filipdutescu/modern-cpp-template 
* https://github.com/TheLartians/ModernCppStarter 
* https://github.com/pabloariasal/modern-cmake-sample 
* https://github.com/StableCoder/cmake-scripts#sanitizer-builds-sanitizerscmake

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

# Getting Started 
1. Change project name in CmakeLists.txt
2. Rename cmake/TemplateConfig.cmake to match your project name
3. Change "ModernCppTemplate" inside every github file to match your project repo
4. Add header and source files to cmake/sources.cmake
5. Compile, build and run

## Available targets
* **\<project-name\>** - to build project
* **install** - to install project
* **doxygen-docs** - to generate documentation
* **clang-format** - to format code

## usefull commands
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

* running unit tests(two options)
```
./build/test/UnitTests
```

```
cd build && ctest -C -VV Debug
```
## TODO
* add cpm 
* add dependency graph and code coverage as a part of documentation
* add popular libs as optional 
* add version for ansi C 
* add version for QT 
* add version for STM 
* add version for rpi pico
