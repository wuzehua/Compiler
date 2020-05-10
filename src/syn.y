%{
    #include<cstdio>
    #include<cstdlib>
    #include<string>

    extern int yylex();
    void yyerror(const char *s) { 
        std::printf("Error: %s\n", s);
        std::exit(1); 
    }
%}

%union {
    std::string *string;
    int token;
}

%%

program: 
    program_head  routine  TDOT {
        //TODO 
    }
    ;

program_head: 
    TPROGRAM  id  TSEMI{
        //TODO 
    }
    ;

id: 
    TNAME {}
|   TSYS_CON {}
|   TSYS_FUNCT {}
|   TSYS_PROC {}
|   TSYS_TYPE {}
;

routine: 
    routine_head  routine_body {
        //TODO 
    }
    ;

sub_routine: 
    routine_head  routine_body {
        //TODO 
    }
    ;

routine_head: 
    label_part  const_part  type_part  var_part  routine_part {
        //TODO 
    }
    ;


label_part: {
    //label_part: ε
    }
    ;

const_part:
    TCONST  const_expr_list { 
        //TODO
    } 
    |  
    ;
const_expr_list:
    const_expr_list  TNAME  TEQUAL  const_value  TSEMI {
        //TODO
    }
|   TNAME  TEQUAL  const_value  TSEMI {
        //TODO
    }
    ;

const_value:TINTEGER {}
|  TREAL  {}
|  TCHAR  {}
|  TSYS_CON  {}
;

type_part:
    TTYPE type_decl_list {}
|
;

type_decl_list:
    type_decl_list  type_definition {} 
|   type_definition {}
;

type_definition:
    TNAME  TEQUAL  type_decl  TSEMI {}
;

type_decl:
    simple_type_decl {}  
|   array_type_decl  {}
|   record_type_decl {}
;

simple_type_decl:
    TSYS_TYPE  {}
|   TNAME  {}
|   TLP  name_list  TRP {} 
|   const_value  TDOTDOT  const_value {} 
|   TMINUS  const_value  TDOTDOT  const_value {}
|   TMINUS  const_value  TDOTDOT  TMINUS  const_value {}
|   TNAME  TDOTDOT  TNAME {}
;

array_type_decl:
    TARRAY  TLB  simple_type_decl  TRB  TOF  type_decl {}
;

record_type_decl:
    TRECORD  field_decl_list  TEND {}
;

field_decl_list:
    field_decl_list  field_decl  {}
|   field_decl {}
;

field_decl:
    name_list  TCOLON  type_decl  TSEMI {}
;

name_list:
    name_list  TCOMMA  id  {}
|   id {}
;

var_part:
    TVAR  var_decl_list  {}
|  {}
;

var_decl_list:  
    var_decl_list  var_decl  {}
|   var_decl {}
;

var_decl:  
    name_list  TCOLON  type_decl  TSEMI {}
;    

routine_part:  
    routine_part  function_decl  {}
|   routine_part  procedure_decl {}
|   function_decl  {}
|   procedure_decl  {}
|   {}
;

function_decl: 
    function_head  TSEMI  sub_routine  TSEMI {}
;

function_head:  
    TFUNCTION  TNAME  parameters  TCOLON  simple_type_decl {}
;

procedure_decl:  
    procedure_head  TSEMI  sub_routine  TSEMI {}
;    

procedure_head:  
    TPROCEDURE TNAME parameters {}
;

parameters:
    TLP  para_decl_list  TRP  {}
|  
;

para_decl_list:
    para_decl_list  TSEMI  para_type_list 
|   para_type_list
;

para_type_list:
    var_para_list TCOLON  simple_type_decl  
|   val_para_list TCOLON  simple_type_decl
;

var_para_list:
    TVAR  name_list
;

val_para_list:
    name_list
;

routine_body:
    compound_stmt
;

compound_stmt:
    TBEGIN  stmt_list  TEND
;

stmt_list:
    stmt_list  stmt  TSEMI  
|  
;

stmt:
    TINTEGER  TCOLON  non_label_stmt  
|   non_label_stmt
;

non_label_stmt:
    assign_stmt 
|   proc_stmt 
|   compound_stmt 
|   if_stmt 
|   repeat_stmt 
|   while_stmt 
|   for_stmt 
|   case_stmt 
|   goto_stmt
;

assign_stmt:
    id  TASSIGN  expression
|   id TLB expression TRB TASSIGN expression
|   id  TDOT  id  TASSIGN  expression
;

proc_stmt:
    id
|   id  TLP  args_list  TRP
|   TSYS_PROC
|   TSYS_PROC  TLP  expression_list  TRP
|   TREAD  TLP  factor  TRP
;

if_stmt:
    TIF  expression  TTHEN  stmt  else_clause
;

else_clause:
    TELSE stmt 
|  
;

repeat_stmt:
    TREPEAT  stmt_list  TUNTIL  expression
;

while_stmt:
    TWHILE  expression  TDO stmt
;

for_stmt:
    TFOR  id  TASSIGN  expression  direction  expression  TDO stmt
;

direction:
    TTO 
|   TDOWNTO
;

case_stmt:
    TCASE expression TOF case_expr_list  TEND
;

case_expr_list:
    case_expr_list  case_expr  
|   case_expr
;

case_expr:
    const_value  TCOLON  stmt  TSEMI
|   id  TCOLON  stmt  TSEMI
;

goto_stmt:
    TGOTO  TINTEGER
;

expression_list:
    expression_list  TCOMMA  expression  
|   expression
;

expression:
    expression  TGE  expr  
|   expression  TGT  expr  
|   expression  TLE  expr
|   expression  TLT  expr  
|   expression  TEQUAL  expr  
|   expression  TUNEQUAL  expr  
|   expr
;

expr:
    expr  TPLUS  term  
|   expr  TMINUS  term  
|   expr  TOR  term  
|   term
;

term:
    term  TMUL  factor  
|   term  TDIV  factor  
|   term  TMOD  factor 
|   term  TAND  factor  
|   factor
;

factor:
    TNAME  
|   TNAME  TLP  args_list  TRP  
|   TSYS_FUNCT 
|   TSYS_FUNCT  TLP  args_list  TRP  
|   const_value  
|   TLP  expression  TRP
|   TNOT  factor  
|   TMINUS  factor  
|   TID  TLB  expression  TRB
|   id  TDOT  id
;

args_list:
    args_list  TCOMMA  expression  
|   expression
;

%%

