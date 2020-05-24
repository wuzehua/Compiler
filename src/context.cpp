//
// Created by 郑文浩 on 2020/5/23.
//

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

using legacy::PassManager;
#define ISTYPE(value, id) (value->getType()->getTypeID() == id)
