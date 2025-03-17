cmake_minimum_required(VERSION 3.25)

project(rlimit C)

add_library(rlimit OBJECT)

set_target_properties(
  rlimit
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ON
)

target_sources(
  rlimit
  INTERFACE
    include/rlimit.h
)

if(WIN32)
  target_sources(
    rlimit
    PRIVATE
      src/win32.c
  )
else()
  target_sources(
    rlimit
    PRIVATE
      src/posix.c
  )
endif()

target_include_directories(
  rlimit
  PUBLIC
    include
)

add_library(rlimit_shared SHARED)

set_target_properties(
  rlimit_shared
  PROPERTIES
  OUTPUT_NAME rlimit
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries(
  rlimit_shared
  PUBLIC
    rlimit
)

add_library(rlimit_static STATIC)

set_target_properties(
  rlimit_static
  PROPERTIES
  OUTPUT_NAME rlimit
  PREFIX lib
)

target_link_libraries(
  rlimit_static
  PUBLIC
    rlimit
)

install(TARGETS rlimit_shared rlimit_static)

install(FILES include/rlimit.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
endif()
