%{
    #include<cstdio>
    #include<cstdlib>
    #include<string>
    #include<memory>
    #include"ast.h"

    using std::shared_ptr;
    using std::make_shared;

    BlockNode* programBlock;

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
    ArrayIndexNode* array_index;
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
%token <token> IF ELIF ELSE RETURN STATIC BREAK THEN EXTERN 


%type <block> program declarationList statementList codeBlock
%type <stat> statement declaration funDeclaration expressionStmt selectionStmt iterationStmt returnStmt
%type <expr> constant mutable immutable simpleExpression expression andExpression sumExpression unaryExpression unaryRelExpression relExpression mulExpression call factor
%type <var_decl> paramType varDeclaration
%type <id> typeSpecifier identifier
%type <array_index> arrayElement
%type <var_list> paramList params
%type <expr_list> argList
%type <token> relop sumop mulop

%left PLUS MINUS
%left MUL DIV

%start program

%%

 program: declarationList { programBlock = $1; };
 
 declarationList: declarationList declaration { $1->statements.emplace_back(shared_ptr<StatementNode>($2));}
    | declaration { $$ = new BlockNode(); 
                    $$->statements.emplace_back(shared_ptr<StatementNode>($1));
                }
    ;

declaration: varDeclaration { $$ = $1; }
    | funDeclaration { $$ = $1; }
    ;

identifier: ID { $$ = new IdentifierNode(*$1); delete $1;};

statementList:  statement { $$ = new BlockNode(); $$->statements.emplace_back(shared_ptr<StatementNode>($1));}
    | statementList statement {  $1->statements.emplace_back(shared_ptr<StatementNode>($2)); }
    ;

varDeclaration: typeSpecifier identifier SEMI { 
                    $$ = new VariableDeclarationNode($1, $2); 
                    }
            |   typeSpecifier identifier COLON simpleExpression SEMI{
                    $$ = new VariableDeclarationNode($1, $2, $4);
                }
            |   typeSpecifier identifier LBRACKET INTEGER RBRACKET SEMI {
                $1->isArray = true;
                int64_t value; 
                sscanf($4->c_str(), "%ld", &value); 
                auto in = new IntegerNode(value); 
                delete $4;
                ExpressionList* exprl = new ExpressionList();

                exprl->emplace_back(shared_ptr<ExpressionNode>(in));
                $1->arraySize = shared_ptr<ExpressionList>(exprl);
                $$ = new VariableDeclarationNode($1, $2);
            }
            ;

typeSpecifier: INT { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; } 
            | BOOL { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; }
            | CHAR { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; }
            | DOUBLE { $$ = new IdentifierNode(*$1); $$->isType = true; delete $1; }
            ;

codeBlock: LBRACE RBRACE { $$ = new BlockNode();}
        |  LBRACE statementList RBRACE { $$ = $2; }
        ;    

funDeclaration: typeSpecifier identifier LPAR params RPAR codeBlock { $$ = new FunctionDeclarationNode($1, $2, $4, $6); }
    | identifier LPAR params RPAR codeBlock { $$ = new FunctionDeclarationNode(nullptr, $1, $3, $5); }
    ;
    
params:  { $$ = new VariableList(); }
    | paramList { $$ = $1; }
    ; 

paramList: paramList COMMA paramType { $1->emplace_back(shared_ptr<VariableDeclarationNode>($3)); }
    | paramType { $$ = new VariableList(); $$->emplace_back(shared_ptr<VariableDeclarationNode>($1)); }
    ;
    
paramType: typeSpecifier identifier { $$ = new VariableDeclarationNode($1, $2); }
    |   typeSpecifier identifier LBRACKET RBRACKET {
            $1->isArray = true;
            $$ = new VariableDeclarationNode($1, $2);
        }
    ;

statement: expressionStmt 
    | selectionStmt 
    | iterationStmt 
    | returnStmt
    | varDeclaration
    | codeBlock
    ;

        
expressionStmt: expression SEMI { $$ = new ExpressionStatementNode($1); } 
    | SEMI { $$ = nullptr; }
    ;
    
selectionStmt: IF simpleExpression THEN codeBlock { $$ = new IfStatementNode($2, $4, nullptr);}
    | IF simpleExpression THEN codeBlock ELSE codeBlock { $$ = new IfStatementNode($2, $4, $6); }
    | IF simpleExpression THEN codeBlock ELSE selectionStmt { 
                            BlockNode* elseBlock = new BlockNode();
                            elseBlock->statements.emplace_back(shared_ptr<StatementNode>($6));
                            $$ = new IfStatementNode($2, $4, elseBlock);
                    }
    ;


    
iterationStmt: WHILE simpleExpression DO codeBlock { $$ = new WhileStatementNode($2, $4); }
    ;
    
returnStmt: RETURN SEMI { $$ = new ReturnStatementNode(nullptr);}
    | RETURN expression SEMI { $$ = new ReturnStatementNode($2); }
    ;
    

expression: identifier ASSIGN expression { $$ = new AssignmentNode($1, $3); }
    | arrayElement ASSIGN expression { $$ = new ArrayIndexAssignmentNode($1, $3); }
    | simpleExpression { $$ = $1; }
    ;

arrayElement: identifier LBRACKET expression RBRACKET { $$ = new ArrayIndexNode($1, $3); }
    ;
    
simpleExpression: simpleExpression OR andExpression { $$ = new BinaryOperatorNode($1, $2, $3);}
    | andExpression { $$ = $1; }
    ;
    
andExpression: andExpression AND unaryRelExpression  { $$ = new BinaryOperatorNode($1, $2, $3);}
    | unaryRelExpression { $$ = $1; }
    ;
    
unaryRelExpression: NOT unaryRelExpression { /*Not implement*/ $$ = nullptr; }
    | relExpression { $$ = $1; }
    ;
    
relExpression: sumExpression relop sumExpression { $$ = new BinaryOperatorNode($1, $2, $3);} 
    | sumExpression { $$ = $1; }
    ;
    
relop: LE | LT | GT | GE | EQUAL | NEQUAL;

sumExpression: sumExpression sumop mulExpression { $$ = new BinaryOperatorNode($1, $2, $3);}
    | mulExpression { $$ = $1; }
    ;
    
sumop: PLUS | MINUS;

mulExpression: mulExpression mulop unaryExpression { $$ = new BinaryOperatorNode($1, $2, $3);}
    | unaryExpression { $$ = $1; }
    ;
    
mulop: MUL | DIV;

unaryExpression: factor { $$ = $1; }
    ;
    

factor: immutable { $$ = $1; }
    | mutable { $$ = $1; }
    ;
    
mutable: identifier { $$ = $1; }
    | identifier LBRACKET expression RBRACKET { $$ = new ArrayIndexNode($1, $3); }
    ;
    
immutable: LPAR expression RPAR { $$ = $2; }
    | call { $$ = $1; }
    | constant { $$ = $1; }
    ;
    
call: identifier LPAR argList RPAR { $$ = new FunctionCallNode($1, $3); }
    | identifier LPAR RPAR { $$ = new FunctionCallNode($1); }
    ;


argList: argList COMMA expression { $1->emplace_back(shared_ptr<ExpressionNode>($3)); } 
    | expression { $$ = new ExpressionList(); $$->emplace_back(shared_ptr<ExpressionNode>($1)); }
    ;
    
constant: INTEGER { int64_t value; sscanf($1->c_str(), "%ld", &value); $$ = new IntegerNode(value); delete $1; } 
    | CHARACTER { $$ = new CharNode((*$1)[1]); delete $1; }
    | REAL { double value; sscanf($1->c_str(), "%lf", &value); $$ = new RealNode(value); delete $1; }
    | FALSE { $$ = new BoolNode(false); }
    | TRUE { $$ = new BoolNode(true); }
    ;
%%

extern int dbg_on;
extern void compile_and_run(BlockNode* b);
