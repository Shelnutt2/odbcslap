cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(MergeStaticLibs)
#INCLUDE(EnableCoverageReport)

option(COVERAGE "Turn on coveralls support" OFF)
#option(COVERALLS_UPLOAD "Upload the generated coveralls json" ON)

# Add third party libraries before enabling code coverage
add_subdirectory(lib)

IF(COVERAGE)
    message(STATUS "Code coverage enabled")
    include(CodeCoverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g -O0 -fprofile-arcs -ftest-coverage -coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -g -O0 -fprofile-arcs -ftest-coverage -coverage")
ENDIF()

enable_testing() # needed on top-level CMakeLists.txt
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Target doc definition
# The challenge here is that the sub projects must all define a custom target but with different names to avoid
# conflicts. We also want to be able to issue "make doc" from the top dir while being able to issue "make doc"
# in the subdirs *when* we compile only a subproject.
# We define as well a function AddDocTarget in cmake/DoxygenTarget.cmake
# Taken from https://github.com/Barthelemy/CppProjectTemplate
add_custom_target(doc) # DEPENDS docProjA docProjB) Note: with CMake 3.X the DEPENDS would work
ADD_DEPENDENCIES(doc odbcslap-static odbcslap-bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


IF ( CMAKE_COMPILER_IS_GNUCC )
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
ENDIF()


IF (CMAKE_CXX_COMPILER MATCHES ".*clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weverything -pedantic")
ENDIF()

add_subdirectory(odbcslap)

add_subdirectory(test)

IF(COVERAGE)
    setup_target_for_coverage(odbcslap_coverage odbcslap_test coverage)
ENDIF()