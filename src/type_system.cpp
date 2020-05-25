//
// Created by 郑文浩 on 2020/5/23.
//

#include "type_system.h"

using llvm::Type;
using llvm::CastInst;

TypePtr TypeSystem::getLlvmVarType(const IdentifierNode &type) {
    assert(type.isType);
    if (type.isArray) {     // array type when allocation, pointer type when pass parameters
        return llvm::PointerType::get(getLlvmVarType(type.name), 0);
    }

    return getLlvmVarType(type.name);
}

TypePtr TypeSystem::getLlvmVarType(string typeStr) {
    return typeCollection.getVarType(typeStr);
}


ValuePtr TypeSystem::getDefaultValue(string typeStr) {
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

