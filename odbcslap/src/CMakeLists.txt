#Set source files
file( GLOB EXECUTABLE_SRC_FILES "password.cpp" "main.cpp")

file( GLOB LIBRARY_SRC_FILES "*.cpp")

list (REMOVE_ITEM LIBRARY_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/password.cpp")

include_directories(${NANODBC_INCLUDE_DIR})

add_library(odbcslap_static STATIC ${LIBRARY_SRC_FILES})

link_libraries(odbcslap_static nanodbc)

add_executable(odbcslap-bin ${EXECUTABLE_SRC_FILES})

# Set the build version. It will be used in thre name of the lib, with corresponding
# symlinks created. SOVERSION could also be specified for api version.
set_target_properties(odbcslap-bin PROPERTIES
        VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
        )

target_link_libraries(odbcslap-bin odbcslap_static)

# now we rename Odbcslap-bin executable to Odbcslap using target properties
set_target_properties(odbcslap-bin
        PROPERTIES OUTPUT_NAME odbcslap)

MERGE_STATIC_LIBS(odbcslap odbcslap_static nanodbc)