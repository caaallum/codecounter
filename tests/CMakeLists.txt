find_package(Check REQUIRED)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

set(TEST_NAME codecounter_test)

add_executable(${TEST_NAME} codecounter_test.c)
target_link_libraries(${TEST_NAME} codecounter ${CHECK_LIBRARIES} pthread)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 30)

include(FindValgrind)

add_custom_target(valgrind_test_sample
    COMMAND ${VALGRIND_PROGRAM} --leak-check=full $<TARGET_FILE:${TEST_NAME}
    DEPENDS ${TEST_NAME}
)
