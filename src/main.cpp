#include<cstdio>
#include<cstdlib>
#include<string>
#include<memory>
#include"ast.h"
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/ADT/Optional.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/IR/LegacyPassManager.h>


using std::shared_ptr;
using std::make_shared;

extern BlockNode* programBlock;

using namespace std;

int main(){
    extern FILE* yyin;
    extern int yyparse(void);

    char filename[50];

    printf("Input file:");
    scanf("%s", filename);
    yyin = fopen(filename, "r");
    yyparse();

    
    if(programBlock != nullptr) {
        programBlock->debugPrint("");

    CodeGenerationContext maincontext;
    maincontext.generateCode(programBlock);

    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    auto targetTriple = sys::getDefaultTargetTriple();
    maincontext.theModule->setTargetTriple(targetTriple);

    string err;
    auto tgt = TargetRegistry::lookupTarget(targetTriple, err);
    delete programBlock;

    if(!tgt)
    {
        cout << "Error !" << endl;
        return;
    }

    string CPU("generic");
    TargetOptions option;
    auto RM = Optional<Reloc::Model>();
    auto tgtMachine = tgt->createTargetMachine(targetTriple, CPU, "", option, RM);
    
    error_code errcode;
    raw_fd_ostream of1("whatthefuckisthis.o", errcode, sys::fs::F_None);
    raw_fd_ostream of2("andwhatthefuckisthis.o", errcode, sys::fs::F_None);

    legacy::PassManager pass;
    auto fileType = CGFT_ObjectFile;

    if(tgtMachine->addPassesToEmitFile(pass, of1, &of2, fileType)) {
        cout << "Fuck you prick! This fu cking file type is not goddamn supported!" << endl;
    }

    pass.run(*(maincontext.theModule.get()));
    of1.flush();
    of2.flush();

    fclose(yyin);
    return 0;
}