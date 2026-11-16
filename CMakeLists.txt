cmake_minimum_required(VERSION 4.0)

find_package(cmake-prelude REQUIRED PATHS node_modules/cmake-prelude)
find_package(cmake-test REQUIRED PATHS node_modules/cmake-test)

project(rlimit LANGUAGES C VERSION 0.0.0)

add_library_targets(
  rlimit
  HEADERS
    include/rlimit.h
  FEATURES
    c_std_99
)

if(WIN32)
  target_sources(
    rlimit
    PRIVATE
      src/win32.c
  )
elseif(CMAKE_SYSTEM_NAME STREQUAL "FreeRTOS")
  target_sources(
    rlimit
    PRIVATE
      src/freertos.c
  )
else()
  target_sources(
    rlimit
    PRIVATE
      src/posix.c
  )
endif()

add_test_subdirectory(test)
