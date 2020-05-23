cmake_minimum_required(VERSION 3.14)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)

set(SRCS ast.h ast.cpp context.h lex.cpp syn.cpp syn.hpp)

add_executable(${PROJECT_NAME} ${SRCS})