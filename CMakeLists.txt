cmake_minimum_required(VERSION 3.1)
project(stacklang)

include_directories("${stacklang_SOURCE_DIR}/include")

add_executable(stacklang
  "${stacklang_SOURCE_DIR}/src/main.c"
  "${stacklang_SOURCE_DIR}/src/lexer.c"
  "${stacklang_SOURCE_DIR}/src/syntax.c")
