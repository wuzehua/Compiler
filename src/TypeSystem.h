//
// Created by 郑文浩 on 2020/5/23.
//

#ifndef COMPILER_TYPESYSTEM_H
#define COMPILER_TYPESYSTEM_H

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <string>
#include <map>
#include <vector>

#include "ast.h"

using std::string;
using namespace llvm;

using TypeNamePair = std::pair<std::string, std::string>;

class TypeSystem {
private:

    LLVMContext &llvmContext;

    std::map<Type *, std::map<Type *, CastInst::CastOps>> _castTable;

    void addCast(Type *from, Type *to, CastInst::CastOps op);

public:
    Type *floatTy = Type::getFloatTy(llvmContext);
    Type *intTy = Type::getInt32Ty(llvmContext);
    Type *charTy = Type::getInt8Ty(llvmContext);
    Type *doubleTy = Type::getDoubleTy(llvmContext);
    Type *stringTy = Type::getInt8PtrTy(llvmContext);
    Type *voidTy = Type::getVoidTy(llvmContext);
    Type *boolTy = Type::getInt1Ty(llvmContext);


    TypeSystem(LLVMContext &context);

    Type *getVarType(const IdentifierNode &type);

    Type *getVarType(string typeStr);

    Value *getDefaultValue(string typeStr, LLVMContext &context);

    Value *cast(Value *value, Type *type, BasicBlock *block);

    static string llvmTypeToStr(Value *value);

    static string llvmTypeToStr(Type *type);

};


#endif //COMPILER_TYPESYSTEM_H
