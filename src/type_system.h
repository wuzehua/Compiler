//
// Created by 郑文浩 on 2020/5/23.
//

#pragma once

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <string>
#include <map>
#include <vector>

#include "ast.h"
#include "type_collection.h"

using std::string;
using llvm::LLVMContext;
using llvm::BasicBlock;

class TypeSystem {
private:

    LLVMContext &llvmContext;
    TypeCollection typeCollection;

public:

    explicit TypeSystem(LLVMContext &context):llvmContext(context), typeCollection(context) {}

    TypePtr getVarType(const IdentifierNode &type);

    TypePtr getVarType(string typeStr);

    ValuePtr getDefaultValue(string typeStr);

    ValuePtr cast(ValuePtr value, TypePtr type, BasicBlock *block);

    static string llvmTypeToStr(ValuePtr value);

    static string llvmTypeToStr(TypePtr type);

};


