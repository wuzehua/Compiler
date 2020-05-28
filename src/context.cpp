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

    Log::raiseMessage("Start to generate LLVM IR\n", std::cout);

    BasicBlock* block = BasicBlock::Create(llvmContext, "entry");

    pushCodeBlock(block);
    auto value = blockNode->generateCode(*this);
    popCurrentCodeBlock();

    std::error_code EC;
    raw_fd_ostream dest("test.ll", EC, sys::fs::OF_None);

    PassManager pass;
    pass.add(createPrintModulePass(dest));
    pass.run(*theModule);

    Log::raiseMessage("Finish generating LLVM IR\n", std::cout);

}

void CodeGenerationContext::exportToObj(const string &filename) {
    // Initialize the target registry etc.
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    auto TargetTriple = sys::getDefaultTargetTriple();
    theModule->setTargetTriple(TargetTriple);

    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

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

    theModule->setDataLayout(TheTargetMachine->createDataLayout());

    std::error_code EC;
    raw_fd_ostream dest(filename, EC, sys::fs::OF_None);


    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return;
    }


    PassManager pass;
    auto FileType = CGFT_ObjectFile;


    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        errs() << "TheTargetMachine can't emit a file of this type";
        return;
    }



    pass.run(*theModule); //TODO: Export obj failed


    dest.flush();

    Log::raiseMessage("Export to " + filename, std::cout);

}