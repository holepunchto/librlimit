if(TARGET rlimit_shared)
  set(library rlimit::shared)
else()
  set(library rlimit::static)
endif()

add_test_executables(
  open-files-infer.c
  LINK
    ${library}
)
