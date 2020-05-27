cmake_minimum_required(VERSION 3.14)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)

link_directories(/usr/local/opt/llvm/lib)
include_directories(/usr/local/opt/llvm/include)



set(SRCS
        ast.h
        ast.cpp
        context.h
        lex.cpp
        syn.cpp
        syn.hpp
        type_helper.cpp
        type_helper.h
        context.cpp
        type_collection.h
        log.h
        main.cpp
        )

set(LLVM_LINK_COMPONENTS Core native Support)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME}

        LLVMCore
        LLVMSupport
        LLVMCodeGen
        )
