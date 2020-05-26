//
// Created by 郑文浩 on 2020/5/23.
//

#include "type_system.h"

using llvm::Type;
using llvm::CastInst;

TypePtr TypeSystem::getLLVMType(shared_ptr<TypeNode>& type) {
    if (type->isArray) {     // array type when allocation, pointer type when pass parameters
        return llvm::PointerType::get(getLLVMVarType(type->name), 0);
    }

    return getLLVMVarType(type->name);
}

TypePtr TypeSystem::getLLVMVarType(const string& typeStr) {
    return typeCollection.getVarType(typeStr);
}


bool TypeSystem::castAvailable(ValuePtr v1, ValuePtr v2) {
    return v1->getType()->getTypeID() == v2->getType()->getTypeID() ||
            (v1->getType() == Type::getInt64Ty(llvmContext) && v2->getType() == Type::getDoubleTy(llvmContext)) ||
            (v2->getType() == Type::getInt64Ty(llvmContext) && v1->getType() == Type::getDoubleTy(llvmContext));
}

bool TypeSystem::isNumber(ValuePtr v) {
    return v->getType() == Type::getInt64Ty(llvmContext) || v->getType() == Type::getDoubleTy(llvmContext);
}

bool TypeSystem::isBool(ValuePtr v) {
    return v->getType() == typeCollection.getVarType("bool");
}

ValuePtr TypeSystem::getDefaultValue(const string& typeStr) {
    return typeCollection.getTypeDefault(typeStr);
}




ValuePtr TypeSystem::cast(ValuePtr value, TypePtr type, BasicBlock *block) {
    TypePtr origin = value->getType();
    if(origin == type){
        return value;
    }

    CastInst::CastOps ops;
    if(origin == typeCollection.getVarType("int") && type == typeCollection.getVarType("double")){
        ops = CastInst::SIToFP;
    } else if(origin == typeCollection.getVarType("double") && type == typeCollection.getVarType("int")){
        ops = CastInst::FPToSI;
    }else{
        string errorMessage = "Casting from type: " + llvmTypeToStr(value) + " to type: " + llvmTypeToStr(type) + "is not allowed";
        Log::raiseError(errorMessage, std::cout);
        return value;
    }

    return CastInst::Create(ops, value, type, "castNumber", block);

}


string TypeSystem::llvmTypeToStr(ValuePtr value) {
    if (value)
        return llvmTypeToStr(value->getType());
    else
        return "Value is nullptr";
}

string TypeSystem::llvmTypeToStr(TypePtr value) {
    Type::TypeID typeID;
    if (value)
        typeID = value->getTypeID();
    else
        return "Value is nullptr";

    switch (typeID) {
        case Type::VoidTyID:
            return "VoidTyID";
        case Type::HalfTyID:
            return "HalfTyID";
        case Type::DoubleTyID:
            return "DoubleTyID";
        case Type::IntegerTyID:
            return "IntegerTyID";
        case Type::FunctionTyID:
            return "FunctionTyID";
        case Type::ArrayTyID:
            return "ArrayTyID";
        default:
            return "Unknown";
    }
}

