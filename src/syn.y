%{
    #include<cstdio>
    #include<cstdlib>
    #include<string>
    #include<memory>
    #include"ast.h"

    using std::shared_ptr;
    using std::make_shared;

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

%token <string> ID INTEGER CHARACTER REAL INT CHAR BOOL DOUBLE
%token <token> TRUE FALSE 
%token <token> EQUAL GE GT LE LT NEQUAL ASSIGN
%token <token> LBRACE RBRACE LBRACKET RBRACKET LPAR RPAR COMMA SEMI DOT COLON
%token <token> WHILE DO LOOP FOREVER 
%token <token> PLUS MINUS MUL DIV NOT AND OR
%token <token> IF ELIF ELSE WHILE RETURN STATIC BREAK THEN


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

identifier: ID { $$ = new IdentifierNode(*$1); delete $1;};

statementList:  statement
    | statementList statement;

statement: expressionStmt 
    | compoundStmt 
    | selectionStmt 
    | iterationStmt 
    | returnStmt
    | varDeclaration;

varDeclaration: typeSpecifier identifier SEMI { 
                    $$ = new VariableDeclarationNode($1, $2); 
                    }
            |   typeSpecifier identifier COLON simpleExpression SEMI{
                    $$ = new VariableDeclarationNode($1, $2, $4);
                }
            |   typeSpecifier identifier LBRACKET INTEGER RBRACKET SEMI {
                $1->isArray = true;
                shared_ptr<ExpressionList> exprl = make_shared<ExpressionList>();
                exprl->emplace_back(shared_ptr<ExpressionNode>($4));
                $1->arraySize = exprl;
                $$ = new VariableDeclarationNode($1, $2);
            }
            ;

typeSpecifier: INT { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; } 
            | BOOL { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; }
            | CHAR { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; }
            ;

codeBlock: LBRACE RBRACE { $$ = new BlockNode();}
        |  LBRACE statementList RBRACE { $$ = $2; }
        ;    

funDeclaration: typeSpecifier ID LPAR params RPAR codeBlock 
    | ID LPAR params RPAR codeBlock;
    
params:  
    | paramList; 

paramList: paramList SEMI paramTypeList 
    | paramTypeList;
    
paramTypeList: typeSpecifier paramIdList;

paramIdList: paramIdList COMMA paramId 
    | paramId;
    
paramId: ID 
    | ID LBRACKET RBRACKET;
    

    
expressionStmt: expression SEMI 
    | SEMI;
    
compoundStmt: LBRACE localDeclarations statementList RBRACE;


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
    

expression: mutable ASSIGN expression 
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