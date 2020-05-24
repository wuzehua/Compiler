//
// Created by rainzhong on 2020/5/24.
//

#pragma once

#include <string>
#include <llvm/IR/Value.h>

using std::string;

class Log{
public:
    static llvm::Value* raiseError(const string&);


};

