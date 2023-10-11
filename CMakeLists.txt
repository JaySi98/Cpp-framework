cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(
    "Cpp-framework" 
    VERSION 0.1.0 
    LANGUAGES CXX
)

# Prevention from building in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a build directory and run CMake from there.\n")
endif()

# ===========================
# Project options
# ===========================
include(cmake/package-managers.cmake)
include(cmake/doxygen.cmake)
include(cmake/compiler.cmake)
include(cmake/settings.cmake)
include(cmake/utils.cmake)
include(cmake/sources.cmake)
include(cmake/sanitizers.cmake)
# include(cmake/code-coverage.cmake) # todo

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...\n")

# Set the compiler standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC_VERSION GREATER_EQUAL "1900" AND CMAKE_VERSION LESS 3.10)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("/std:c++17" _cpp_latest_flag_supported)
    if(_cpp_latest_flag_supported)
        add_compile_options("/std:c++17")
    endif()
endif()


# ===========================
# adding exec/lib
# ===========================
if(BUILD_EXECUTABLE)
    add_executable(${PROJECT_NAME} ${EXE_SOURCES})

    message(STATUS "Found the following sources:")
    foreach(SOURCE IN LISTS EXE_SOURCES)
        message(STATUS "* ${SOURCE}")
    endforeach()

    if(ENABLE_UNIT_TESTING)
        add_library(${PROJECT_NAME}_LIB ${HEADERS} ${SOURCES})

        message(STATUS "Found the following headers:")
        foreach(HEADER IN LISTS HEADERS)
            message(STATUS "* ${HEADER}")
        endforeach()
    endif()

elseif(BUILD_HEADERS_ONLY)
    add_library(${PROJECT_NAME} INTERFACE)

    message(STATUS "Found the following headers:")
    foreach(HEADER IN LIST HEADERS)
        message(STATUS "* ${HEADER}")
    endforeach()

else()
    add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

    message(STATUS "Found the following sources:")
    foreach(SOURCE IN LISTS SOURCES)
        message(STATUS "* ${SOURCE}")
    endforeach()

    message(STATUS "Found the following headers:")
    foreach(HEADER IN LISTS HEADERS)
        message(STATUS "* ${HEADER}")
    endforeach()
endif()

# ===========================
# Project properties
# ===========================

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}"
)

if(BUILD_EXECUTABLE AND ENABLE_UNIT_TESTING)
    set_target_properties(
        ${PROJECT_NAME}_LIB
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
        OUTPUT_NAME ${PROJECT_NAME}
    )
endif()

message(STATUS "Added all header and implementation files.\n")

# ===========================
# Project standard and warnings
# ===========================

if(BUILD_HEADERS_ONLY)
    target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
else()
    target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

    if(BUILD_EXECUTABLE AND ENABLE_UNIT_TESTING)
        target_compile_features(${PROJECT_NAME}_LIB PUBLIC cxx_std_17)
    endif()
endif()
set_project_warnings(${PROJECT_NAME})

message(STATUS "Applied compiler warnings. Using standard C++${CMAKE_CXX_STANDARD}.\n")

# ===========================
# Project dependencies
# ===========================

# Boost
set(Boost_FIND_REQUIRED TRUE)
set(Boost_FIND_QUIETLY TRUE)
set(Boost_DEBUG FALSE)
set(Boost_USE_MULTITHREADED TRUE)
set(Boost_USE_STATIC_LIBS TRUE)
find_package(Boost COMPONENTS program_options)

target_link_libraries(${PROJECT_NAME}
  PRIVATE 
#   Boost::signals2 
  Boost::program_options
)

# find_package(package_name package_version REQUIRED package_type [other_options])
#target_link_libraries(
#  ${PROJECT_NAME}
#  PUBLIC
#    dependency1 ...
#  PRIVATE
#    dependency2 ...
#    PROJECT_OPTIONS
#    PROJECT_WARNINGS
#)

#if(BUILD_EXECUTABLE AND ENABLE_UNIT_TESTING)
#  target_link_libraries(
#    ${PROJECT_NAME}_LIB
#    PUBLIC
#      dependency1 ...
#  )
#endif()

# For Windows, it is necessary to link with the MultiThreaded library.
# On Linux and Mac this variable is ignored. 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

message(STATUS "Successfully added all dependencies and linked against them.\n")


# ===========================
# Set the build/user include directories
# ===========================

# Allow usage of header files in the `src` directory, but only for utilities
if(BUILD_HEADERS_ONLY)
    target_include_directories(
        ${PROJECT_NAME}
        INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
else()
    target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

    if(BUILD_EXECUTABLE AND ENABLE_UNIT_TESTING)
        target_include_directories(
            ${PROJECT_NAME}_LIB
            PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )
    endif()
endif()

message(STATUS "Finished setting up include directories.\n")

# ===========================
# Provide alias to library
# ===========================

if(BUILD_EXECUTABLE)
  add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
else()
  add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
endif()

message(STATUS "Project is now aliased as ${PROJECT_NAME}::${PROJECT_NAME}.\n")

# ===========================
# Format the project using the `clang-format` target 
# ===========================
if(ENABLE_CLANG_FORMAT)
    add_clang_format_target()
endif()

# ===========================
# Code coverage
# ===========================
# if(ENABLE_CODE_COVERAGE)
#     add_code_coverage_all_targets(EXCLUDE test/*) 
#     target_code_coverage(${PROJECT_NAME})
# endif()

# ===========================
# Installation
# ===========================
# Install library for easy downstream inclusion
include(GNUInstallDirs)
install(
    TARGETS
    ${PROJECT_NAME}
    EXPORT
    ${PROJECT_NAME}Targets
    LIBRARY DESTINATION
    ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION
    ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION
    ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION
    include
    PUBLIC_HEADER DESTINATION
    include
)

install(
    EXPORT
    ${PROJECT_NAME}Targets
    FILE
    ${PROJECT_NAME}Targets.cmake
    NAMESPACE
    ${PROJECT_NAME}::
    DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Add version header
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/version.hpp.in
    include/${PROJECT_NAME_LOWERCASE}/version.hpp
    @ONLY
)

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME_LOWERCASE}/version.hpp
    DESTINATION
    include/${PROJECT_NAME_LOWERCASE}
)

# Install the `include` directory
install(
    DIRECTORY
    include/${PROJECT_NAME_LOWERCASE}
    DESTINATION
    include
)

message(STATUS "Install targets successfully built.\n")

# Quick `ConfigVersion.cmake` creation
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION
    ${PROJECT_VERSION}
    COMPATIBILITY
    SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

message(STATUS "Finished building requirements for installing the package.\n")

# ===========================
# Unit testing
# ===========================

if(ENABLE_UNIT_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
