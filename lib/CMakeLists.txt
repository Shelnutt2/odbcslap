#Include 3rd party libraries

#Disable NANODBC examples and tests
SET(NANODBC_EXAMPLES OFF CACHE BOOL "build examples")
SET(NANODBC_TEST OFF CACHE BOOL "build tests")
add_subdirectory(nanodbc)