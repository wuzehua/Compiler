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

extern BlockNode *programBlock;

using namespace std;

int main(int argc, char **argv) {
    extern FILE *yyin;
    extern int yyparse(void);

    yyin = nullptr;
    char *filename;
    string outputName = "a.o";
    string astName = "ast.puml";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            i++;
            assert(i < argc);
            filename = argv[i];
            yyin = fopen(filename, "r");
        } else if (strcmp(argv[i], "-o") == 0) {
            i++;
            assert(i < argc);
            outputName = string(argv[i]);
        } else if (strcmp(argv[i], "-d") == 0) {
            i++;
            assert(i < argc);
            astName = string(argv[i]);
        } else if (strcmp(argv[i], "-v") == 0) {
            std::cout << "version 1.0.0-Beta\n";
        }

    }

    if (yyin != nullptr) {
        yyparse();
        programBlock->debugPrint("");
        CodeGenerationContext maincontext;
//        maincontext.drawAST(programBlock, astName);
        maincontext.generateCode(programBlock);
        maincontext.exportToObj(outputName);

        delete programBlock;

        fclose(yyin);
    }


    return 0;
}