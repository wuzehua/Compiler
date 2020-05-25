//
// Created by 郑文浩 on 2020/5/23.
//


#include <iostream>
#include <vector>

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>
//#include <llvm/IR/Verifier.h>
#include "context.h"
#include "ast.h"
#include "type_system.h"

using llvm::Type;
using std::vector;
using llvm::LLVMContext;

using legacy::PassManager;
#define ISTYPE(value, id) (value->getType()->getTypeID() == id)


void CodeGenerationContext::generateCode(BlockNode* blockNode) {
    std::cout<<"Start to generate LLVM IR\n";

    vector<Type*> args;

    FunctionType* mainType = FunctionType::get(Type::getInt64Ty(llvmContext), makeArrayRef(args), false);
    Function* main = Function::Create(mainType, GlobalValue::ExternalLinkage, "main", theModule.get());

    BasicBlock* block = BasicBlock::Create(llvmContext, "entry", main);

    pushCodeBlock(block);
    auto value = blockNode->generateCode(*this);
    popCurrentCodeBlock();
}