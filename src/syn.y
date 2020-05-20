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
%type <expr> constant mutable immutable
%type <var_decl> paramType varDeclaration
%type <id> typeSpecifier identifier



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
                shared_ptr<ExpressionList> exprl = make_shared<ExpressionList>();
                exprl->emplace_back(shared_ptr<ExpressionNode>($4));
                $1->arraySize = exprl;
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

        
expressionStmt: expression SEMI { $$ = $1; } 
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
    
mutable: identifier 
    | mutable LBRACKET expression RBRACKET;
    
immutable: LPAR expression RPAR { $$ = $2; }
    | call { $$ = $1; }
    | constant { $$ = $1; }
    ;
    
call: identifier LPAR argList RPAR { $$ = new MethodCallNode($1, $3); }
    | identifier LPAR RPAR { $$ = new MethodCallNode($1); }
    ;


argList: argList COMMA expression { $1->emplace_back(shared_ptr<ExpressionNode>($3)); } 
    | expression { $$ = new ExpressionList(); $$->emplace_back(shared_ptr<ExpressionNode>($1)); }
    ;
    
constant: INTEGER { int_64 value; sscanf($1->c_str(), "%ld", &value); $$ = new IntegerNode(value); delete $1; } 
    | CHARACTER { $$ = new CharNode((*$1)[1]); delete $1; }
    | REAL { double value; sscanf($1->c_str(), "%lf", &value); $$ = new RealNode(value); delete $1; }
    | FALSE { $$ = new BoolNode(false); delete $1; }
    | TRUE; { $$ = new BoolNode(true); delete $1; }

%%