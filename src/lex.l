%{
    #include<iostream>
    #include<string>
    #include"ast.h"
    #include"syn.hpp"

    #define SAVE_TOKEN  yylval.string = new std::string(yytext)
    #define TOKEN(t)    (yylval.token = t)
%}

%option noyywrap

integer [0-9]+
real [0-9]+\.[0-9]*
charconst \'.\'
id [a-zA-Z_][a-zA-Z0-9_]*

%%
[ \t\n]     ;

"int"       SAVE_TOKEN; return INT;
"char"      SAVE_TOKEN; return CHAR;
"bool"      SAVE_TOKEN; return BOOL;
"double"    SAVE_TOKEN; return DOUBLE;
"true"      return TOKEN(TRUE);
"false"     return TOKEN(FALSE);
"static"    return TOKEN(STATIC);
"if"        return TOKEN(IF);
"elif"      return TOKEN(ELIF);
"then"      return TOKEN(THEN);
"do"        return TOKEN(DO);
"else"      return TOKEN(ELSE);
"while"     return TOKEN(WHILE);
"loop"      return TOKEN(LOOP);
"forever"   return TOKEN(FOREVER);
"return"    return TOKEN(RETURN);
"break"     return TOKEN(BREAK);
"and"       return TOKEN(AND);
"or"        return TOKEN(OR);
"not"       return TOKEN(NOT);
"extern"    return TOKEN(EXTERN);

{real}      SAVE_TOKEN;return REAL;
{integer}   SAVE_TOKEN;return INTEGER;
{charconst} SAVE_TOKEN;return CHARACTER;
{id}        SAVE_TOKEN;return ID;

"="         return TOKEN(ASSIGN);
"=="        return TOKEN(EQUAL);
"!="        return TOKEN(NEQUAL);
"<="        return TOKEN(LE);
">="        return TOKEN(GE);
"<"         return TOKEN(LT);
">"         return TOKEN(GT);

"+"         return TOKEN(PLUS);
"-"         return TOKEN(MINUS);
"*"         return TOKEN(MUL);
"/"         return TOKEN(DIV);
"%"         return TOKEN(MOD);

"("         return TOKEN(LPAR);
")"         return TOKEN(RPAR);
"["         return TOKEN(LBRACKET);
"]"         return TOKEN(RBRACKET);
"{"         return TOKEN(LBRACE);
"}"         return TOKEN(RBRACE);

";"         return TOKEN(SEMI);
","         return TOKEN(COMMA);
":"         return TOKEN(COLON);
"."         return TOKEN(DOT);

.           printf("Unkown Token\n");



%%