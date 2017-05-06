#Include 3rd party libraries

#Disable NANODBC examples and tests
SET(NANODBC_EXAMPLES OFF CACHE BOOL "build examples")
SET(NANODBC_TEST OFF CACHE BOOL "build tests")
SET(NANODBC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nanodbc/nanodbc/" CACHE STRING "nanodbc include directory")
add_subdirectory(nanodbc)