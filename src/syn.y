%{
    #include<cstdio>
    #include<cstdlib>
    #include<string>
    #include<memory>
    #include"ast.h"

    BlockNode* program;

    extern int yylex();
    void yyerror(const char *s) { 
        std::printf("Error: %s\n", s);
        std::exit(1); 
    }
%}

%union {
    BlockNode* block;
    ExpressionNode* expr;
    StatementNode* stat;
    IdentifierNode* id;
    VariableDeclarationNode* var_decl;
    ExpressionList* expr_list;
    VariableList* var_list;
    std::string* string;
    int token;
}

%token <string> ID INTEGER CHARACTER REAL


%type <block> program declarationList
%type <stat> declaration varDeclaration funDeclaration



%left PLUS MINUS
%left MUL DIV

%start program

%%

 program: declarationList { program = $1; };
 
 declarationList: declarationList declaration { $1->statements.emplace_back(shared_ptr<StatementNode>($2));}
    | declaration { $$ = new BlockNode(); 
                    $$->statements.emplace_back(shared_ptr<StatementNode>($1));
                }
    ;

declaration: varDeclaration { $$ = $1; }
    | funDeclaration { $$ = $1; }
    ;

varDeclaration: typeSpecifier varDeclInitialize {}
            |   typeSpecifier ID LBRACKET INTEGER RBRACKET {}
            |   ;

typeSpecifier: INT { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; } 
            | BOOL { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; }
            | CHAR { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; }
            ;

scopedVarDeclaration: scopedTypeSpecifier varDeclInitialize;

localDeclarations:  
    | localDeclarations scopedVarDeclaration;


varDeclInitialize: ID 
    | ID COLON simpleExpression;


scopedTypeSpecifier: STATIC typeSpecifier 
    | typeSpecifier;
    

funDeclaration: typeSpecifier ID LPAR params RPAR statement 
    | ID LPAR params RPAR statement;
    
params:  
    | paramList; 

paramList: paramList SEMI paramTypeList 
    | paramTypeList;
    
paramTypeList: typeSpecifier paramIdList;

paramIdList: paramIdList COMMA paramId 
    | paramId;
    
paramId: ID 
    | ID LBRACKET RBRACKET;
    
statement: expressionStmt 
    | compoundStmt 
    | selectionStmt 
    | iterationStmt 
    | returnStmt
    | breakStmt;
    
expressionStmt: expression SEMI 
    | SEMI;
    
compoundStmt: LBRACE localDeclarations statementList RBRACE;
    
statementList:  
    | statementList statement;

elsifList:  
    | elsifList ELIF simpleExpression THEN statement;

selectionStmt: IF simpleExpression THEN statement elsifList 
    | IF simpleExpression THEN statement elsifList ELSE statement;
    
iterationRange: ID = simpleExpression .. simpleExpression 
    | ID = simpleExpression ..simpleExpression : simpleExpression;
    
iterationStmt: WHILE simpleExpression DO statement 
    | LOOP FOREVER statement 
    | loopiterationRange DO statement;
    
returnStmt: RETURN SEMI 
    | RETURN expression SEMI;
    
breakStmt: BREAK SEMI;

expression: mutable ASSIGN expression 
    // | mutable += expression 
    // | mutable −= expression
    // | mutable ∗= expression 
    // | mutable /= expression 
    // | mutable ++ 
    // | mutable −−
    | simpleExpression;
    
simpleExpression: simpleExpression OR andExpression 
    | andExpression;
    
andExpression: andExpression AND unaryRelExpression 
    | unaryRelExpression;
    
unaryRelExpression: NOT unaryRelExpression 
    | relExpression;
    
relExpression: sumExpression relop sumExpression 
    | sumExpression;
    
relop: LE | LT | GT | GE | EQUAL | NEQUAL;

sumExpression: sumExpression sumop mulExpression 
    | mulExpression;
    
sumop: PLUS | MINUS;

mulExpression: mulExpression mulop unaryExpression 
    | unaryExpression;
    
mulop: MUL | DIV;

unaryExpression: unaryop unaryExpression 
    | factor;
    
unaryop: MINUS;

factor: immutable 
    | mutable;
    
mutable: ID 
    | mutable LBRACKET expression RBRACKET;
    
immutable: LPAR expression RPAR 
    | call 
    | constant;
    
call: ID LPAR args RPAR;

args:  
    | argList;

argList: argList COMMA expression 
    | expression;
    
constant: INTEGER | CHARACTER | REAL | FALSE | TRUE;

%%