//
// Created by rainzhong on 2020/5/24.
//

#pragma once

#include <iostream>
#include <string>
#include <llvm/IR/Value.h>

using std::string;

class Log{
public:
    static llvm::Value* raiseError(const string& message, std::ostream& os){
        os<<"[Error] "<<message<<std::endl;
        return nullptr;
    }

    static llvm::Value* raiseWarning(const string& message, std::ostream& os){
        os<<"[Warning] "<<message<<std::endl;
        return nullptr;
    }

};

