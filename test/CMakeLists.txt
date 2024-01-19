cmake_minimum_required(VERSION 3.15)

project(${CMAKE_PROJECT_NAME}Tests LANGUAGES CXX)

message(STATUS "Adding tests under ${CMAKE_PROJECT_NAME}Tests...")

add_executable(UnitTests ${TEST_SOURCES})
target_compile_features(UnitTests PUBLIC cxx_std_17)
if(BUILD_EXECUTABLE)
	set(${CMAKE_PROJECT_NAME}_TEST_LIB ${CMAKE_PROJECT_NAME}_LIB)
else()
	set(${CMAKE_PROJECT_NAME}_TEST_LIB ${CMAKE_PROJECT_NAME})
endif()

# Load GoogleTest and GoogleMock
find_package(GTest REQUIRED)
set(GOOGLE_MOCK_LIBRARIES GTest::gmock GTest::gmock_main)
target_link_libraries(
	UnitTests
	PUBLIC
	GTest::GTest
	GTest::Main
	${GOOGLE_MOCK_LIBRARIES}
	${${CMAKE_PROJECT_NAME}_TEST_LIB}
)
gtest_discover_tests(UnitTests)

message(STATUS "Finished adding unit tests for ${CMAKE_PROJECT_NAME}.\n")
