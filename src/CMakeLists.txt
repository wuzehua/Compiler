cmake_minimum_required(VERSION 3.14)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)

link_directories(/usr/local/opt/llvm/lib)
include_directories(/usr/local/opt/llvm/include)

set(SRCS ast.h ast.cpp context.h lex.cpp syn.cpp syn.hpp TypeSystem.cpp TypeSystem.h context.cpp)

add_executable(${PROJECT_NAME} ${SRCS})