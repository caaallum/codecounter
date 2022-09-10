cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME codecounter)
set(VERSION 0.1.0)

project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

enable_testing()
add_subdirectory(tests)

find_package(PkgConfig REQUIRED)

pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)

set(SRC
    src/codecounter.c
    src/codecounter.h)

add_definitions(-DVERSION="${VERSION}")

add_executable(${PROJECT_NAME} ${SRC})

add_library(${PROJECT_NAME} ${SRC})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -fprofile-arcs -ftest-coverage -O0)
target_link_libraries(${PROJECT_NAME} PkgConfig::deps)

# Add build target to generate Coverage Test Report to all compiled object files
find_program(GCOV gcov)
find_program(LCOV lcov)
find_program(GENHTML genhtml)
if(NOT GCOV)
  message(FATAL_ERROR "gcov not found!")
endif()
if(NOT LCOV)
  message(FATAL_ERROR "lcov not found!")
endif()
if(NOT GENHTML)
  message(FATAL_ERROR "genhtml not found!")
endif()

add_custom_target(gcov
  COMMAND mkdir -p Coverage
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Testing
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET gcov POST_BUILD
  COMMAND find ${CMAKE_BINARY_DIR} -type f -name *.c.o -exec ${GCOV} {} "\;"
  COMMAND echo "Coverage reports generated."
  COMMAND echo "You can find them on ${CMAKE_BINARY_DIR}/Coverage"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage
  COMMENT "Coverage Reports Generated"
)

add_custom_target(lcov
  COMMAND mkdir -p Coverage
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Testing
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET lcov POST_BUILD
  COMMAND ${LCOV} --directory .. --capture --output-file lcov.info
  COMMAND ${GENHTML} -o . lcov.info
  COMMAND echo "Coverage reports generated."
  COMMAND echo "You can find them on ${CMAKE_BINARY_DIR}/Coverage"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage
  COMMENT "Coverage Reports Generated"
)
