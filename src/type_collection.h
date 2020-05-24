//
// Created by rainzhong on 2020/5/24.
//

#pragma once

#include <string>
#include <map>
#include <llvm/IR/Type.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>


#include "log.h"
#include "ast.h"

using std::string;

typedef llvm::Type* TypePtr;


struct TypeWrapper{
    TypePtr type;
    ValuePtr defaultValue;
    explicit TypeWrapper(TypePtr& type, ValuePtr defaultValue = nullptr):
            type(type),
            defaultValue(defaultValue){}

    bool operator < (const TypeWrapper& wrapper) const {
        return type < wrapper.type;
    }

    bool operator == (const TypeWrapper& wrapper) const {
        return type == wrapper.type;
    }

    bool operator == (const TypePtr& typePtr) const {
        return this->type == typePtr;
    }

};


class TypeCollection{
private:
    std::map<string, struct TypeWrapper> typeMap;

public:

    explicit TypeCollection(llvm::LLVMContext& context){
        TypePtr type = llvm::Type::getInt32Ty(context);
        ValuePtr defaultValue = llvm::ConstantInt::get(type, 0, true);

        typeMap.insert({"int", TypeWrapper(type, defaultValue)});

        type = llvm::Type::getDoubleTy(context);
        defaultValue = llvm::ConstantFP::get(type, 0);

        typeMap.insert({"double", TypeWrapper(type, defaultValue)});

        type = llvm::Type::getInt8Ty(context);
        defaultValue = llvm::ConstantInt::get(type, 0);

        typeMap.insert({"char", TypeWrapper(type, defaultValue)});

        type = llvm::Type::getInt1Ty(context);
        defaultValue = llvm::ConstantInt::get(type, 0);

        typeMap.insert({"bool", TypeWrapper(type, defaultValue)});
    }


    TypePtr getVarType(const string& name){
        auto it = typeMap.find(name);
        if(it == typeMap.end()){
            Log::raiseError("Type: " + name + " not defined");
            return nullptr;
        }

        return it->second.type;
    }

    TypePtr getVarType(const IdentifierNode& type){
        return getVarType(type.name);
    }


    ValuePtr getTypeDefault(const string& type){
        auto it = typeMap.find(type);
        if(it == typeMap.end()){
            Log::raiseError("Type: " + type + " not defined");
            return nullptr;
        }

        return it->second.defaultValue;
    }

};

