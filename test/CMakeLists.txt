include_directories("${gtest_SOURCE_DIR}/include" "${odbcslap_INCLUDE_DIR}")
# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME odbcslap_test)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)

target_link_libraries(${PROJECT_NAME} odbcslap-static gtest gtest_main)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
