#include<cstdio>
#include<cstdlib>
#include<string>
#include<memory>
#include"ast.h"
#include "context.h"
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
//        programBlock->debugPrint("");
    }

    CodeGenerationContext maincontext;
    maincontext.generateCode(programBlock);

    delete programBlock;


    fclose(yyin);
    return 0;
}