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

#include <llvm/Support/Host.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/ADT/Optional.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/FileSystem.h>


#include "context.h"
#include "ast.h"
#include "type_helper.h"

using llvm::Type;
using std::vector;
using llvm::LLVMContext;

using legacy::PassManager;


void CodeGenerationContext::generateCode(BlockNode* blockNode) {
    std::cout<<"Start to generate LLVM IR\n";

    vector<Type*> args;

    FunctionType* mainType = FunctionType::get(Type::getInt64Ty(llvmContext), makeArrayRef(args), false);
    Function* main = Function::Create(mainType, GlobalValue::ExternalLinkage, "main");

    BasicBlock* block = BasicBlock::Create(llvmContext, "entry");

    pushCodeBlock(block);
    auto value = blockNode->generateCode(*this);
    popCurrentCodeBlock();

    std::cout<<"Finish generating LLVM IR\n";

//    PassManager pm;
//    pm.add(createPrintModulePass(outs()));
//    pm.run(*theModule);
}

void CodeGenerationContext::exportToObj(const string &filename) {
    // Initialize the target registry etc.
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    Log::raiseMessage("Set Triple");
    auto TargetTriple = sys::getDefaultTargetTriple();
    theModule->setTargetTriple(TargetTriple);
    Log::raiseMessage("Finish Triple");

    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    Log::raiseMessage("Look up target");
    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target) {
        errs() << Error;
        return;
    }

    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TheTargetMachine =
            Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
    Log::raiseMessage("Target Machine");

    theModule->setDataLayout(TheTargetMachine->createDataLayout());

    auto Filename = "output.o";
    std::error_code EC;
    raw_fd_ostream dest(Filename, EC, sys::fs::OF_None);

    Log::raiseMessage("OStream");

    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return;
    }


    PassManager pass;
    auto FileType = CGFT_ObjectFile;

    Log::raiseMessage("Pass");

    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        errs() << "TheTargetMachine can't emit a file of this type";
        return;
    }

    Log::raiseMessage("Emit");


    pass.run(*theModule); //TODO: Export obj failed

    Log::raiseMessage("Run");

    dest.flush();

    outs() << "Wrote " << Filename << "\n";

}