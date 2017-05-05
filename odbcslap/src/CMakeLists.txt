#Set source files
file( GLOB EXECUTABLE_SRC_FILES "password.cpp" "main.cpp")

file( GLOB LIBRARY_SRC_FILES "*.cpp")

list (REMOVE_ITEM LIBRARY_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/password.cpp")

add_library(odbcslap ${LIBRARY_SRC_FILES})

link_libraries(odbcslap nanodbc)

add_executable(odbcslap-bin ${EXECUTABLE_SRC_FILES})

# Set the build version. It will be used in the name of the lib, with corresponding
# symlinks created. SOVERSION could also be specified for api version.
set_target_properties(odbcslap-bin PROPERTIES
        VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
        )

link_libraries(odbcslap-bin odbcslap)

# now we rename Odbcslap-bin executable to Odbcslap using target properties
set_target_properties(odbcslap-bin
        PROPERTIES OUTPUT_NAME odbcslap)