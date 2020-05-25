#include<cstdio>
#include<cstdlib>
#include<string>
#include<memory>
#include"ast.h"

using std::shared_ptr;
using std::make_shared;

extern BlockNode* programBlock;



int main(){
    extern FILE* yyin;
    extern int yyparse(void);

    char filename[50];

    printf("Input file:");
    scanf("%s", filename);
    yyin = fopen(filename, "r");
    yyparse();

    compile_and_run(programBlock);

    fclose(yyin);
    return 0;
}