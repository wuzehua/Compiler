cmake_minimum_required(VERSION 3.14)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(/usr/local/opt/llvm/lib)
add_definitions(${LLVM_DEFINITIONS})


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

set(LLVM_LINK_COMPONENTS all)

llvm_map_components_to_libnames(llvm_libs ${LLVM_LINK_COMPONENTS})

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${llvm_libs})
