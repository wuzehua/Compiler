#include<cstdio>
#include<cstdlib>
#include<string>
#include<memory>
#include<fstream>
#include<ostream>
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

void showHelp() {
    std::cout
            << "Usage: clang-- -i [input filename] -o [output obj filename] -d [ast uml filename] -ol [ir filename]\n";
    std::cout << "\nOptions:\n";
    std::cout << "-i\tThe src file to compile\n";
    std::cout << "-o\tThe output obj file path\n";
    std::cout << "-d\tEnable AST uml output, and set the AST uml file path, you need to use related software to open the uml file to get the picture\n";
    std::cout << "-ol\tThe output obj file path\n";
    std::cout << "-h\tShow this help\n\n";
}

int main(int argc, char **argv) {
    extern FILE *yyin;
    extern int yyparse(void);

    yyin = nullptr;
    bool printAst = false;
    char *filename;
    string outputName = "a.o";
    string irFilename = "ir.ll";

    if (argc == 1) {
        showHelp();
        return 0;
    }
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
            printAst = true;
        } else if (strcmp(argv[i], "-v") == 0) {
            std::cout << "version 1.0.0-Beta\n";
        } else if (strcmp(argv[i], "-ol") == 0) {
            i++;
            assert(i < argc);
            irFilename = string(argv[i]);
        } else if (strcmp(argv[i], "-h")) {
            showHelp();
            return 0;
        } else {
            std::cout << "Undefined args\n";
            showHelp();
            return 0;
        }

    }

    if (yyin != nullptr) {
        yyparse();
        CodeGenerationContext maincontext;
        if (printAst) {
//            ofstream file;
//            file.open(astName, ios::out);
//            programBlock->debugPrint("", file);
//            file.close();
            maincontext.drawAST(programBlock, astName);
        }
        maincontext.generateCode(programBlock, irFilename);
        maincontext.exportToObj(outputName);

        delete programBlock;

        fclose(yyin);
    }


    return 0;
}