cmake_minimum_required(VERSION 3.1)

include(CTest)
enable_testing()

add_executable(stacktest
  "${stacklang_SOURCE_DIR}/src/test/stack.c"
  "${stacklang_SOURCE_DIR}/src/stack.c")

add_test(test0 stacktest "100" "64532" "1000000" "42" "1235642312")
