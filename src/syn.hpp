/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SYN_HPP_INCLUDED
# define YY_YY_SYN_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTEGER = 259,
    CHARACTER = 260,
    REAL = 261,
    INT = 262,
    CHAR = 263,
    BOOL = 264,
    DOUBLE = 265,
    TRUE = 266,
    FALSE = 267,
    EQUAL = 268,
    GE = 269,
    GT = 270,
    LE = 271,
    LT = 272,
    NEQUAL = 273,
    ASSIGN = 274,
    LBRACE = 275,
    RBRACE = 276,
    LBRACKET = 277,
    RBRACKET = 278,
    LPAR = 279,
    RPAR = 280,
    COMMA = 281,
    SEMI = 282,
    DOT = 283,
    COLON = 284,
    WHILE = 285,
    DO = 286,
    LOOP = 287,
    FOREVER = 288,
    PLUS = 289,
    MINUS = 290,
    MUL = 291,
    DIV = 292,
    NOT = 293,
    AND = 294,
    OR = 295,
    IF = 296,
    ELIF = 297,
    ELSE = 298,
    RETURN = 299,
    STATIC = 300,
    BREAK = 301,
    THEN = 302,
    EXTERN = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "syn.y" /* yacc.c:1921  */

    BlockNode* block;
    ExpressionNode* expr;
    StatementNode* stat;
    IdentifierNode* id;
    ArrayIndexNode* array_index;
    VariableDeclarationNode* var_decl;
    ExpressionList* expr_list;
    VariableList* var_list;
    TypeNode* type;
    std::string* string;
    int token;

#line 121 "syn.hpp" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYN_HPP_INCLUDED  */
