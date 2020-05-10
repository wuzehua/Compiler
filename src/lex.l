%{
    #include<string>

    #define SAVE_TOKEN  yylval.string = new std::string(yytext, yyleng)
    #define TOKEN(t)    (yylval.token = t)
%}

%option noyywrap

keyword and|array|begin|case|const|div|do|downto|else|end|for|function|goto|if|in|mod|not|of|or|packed|procedure|program|record|repeat|set|then|to|type|until|var|while
sys_con false|true|maxint
sys_funct abs|chr|odd|ord|pred|sqr|sqrt|succ
sys_proc write|writeln
sys_type boolean|char|integer|real
read read

%%
[ \t\n]                 ;

"and"                   return TOKEN(TAND);
"array"                 return TOKEN(TARRAY);
"begin"                 return TOKEN(TBEGIN);
"case"                  return TOKEN(TCASE);
"const"                 return TOKEN(TCONST);
"do"                    return TOKEN(TDO);
"downto"                return TOKEN(TDOWNTO);
"else"                  return TOKEN(TELSE);
"end"                   return TOKEN(TEND);
"for"                   return TOKEN(TFOR);
"function"              return TOKEN(TFUNCTION);
"goto"                  return TOKEN(TGOTO);
"if"                    return TOKEN(TIF);
"not"                   return TOKEN(TNOT);
"mod"                   return TOKEN(TMOD);
"of"                    return TOKEN(TOF);
"or"                    return TOKEN(TOR);
"packed"                return TOKEN(TPACKED);
"procedure"             return TOKEN(TPROCEDURE);
"program"               return TOKEN(TPROGRAM);
"record"                return TOKEN(TRECORD);
"then"                  return TOKEN(TTHEN);
"to"                    return TOKEN(TTO);
"type"                  return TOKEN(TTYPE);
"until"                 return TOKEN(TUNTIL);
"var"                   return TOKEN(TVAR);
"while"                 return TOKEN(TWHILE);
"read"                  return TOKEN(TREAD);

{sys_type}              SAVE_TOKEN; return TSYS_TYPE;
{sys_con}               SAVE_TOKEN; return TSYS_CON;
{sys_proc}              SAVE_TOKEN; return TSYS_PROC;
{sys_funct}             SAVE_TOKEN; return TSYS_FUNCT;


[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN; return TNAME;
[0-9]+                  SAVE_TOKEN; return TINTEGER;
[0-9]+\.[0-9]*          SAVE_TOKEN; return TREAL;
\'.\'                   SAVE_TOKEN; return TCHAR;


"="                     return TOKEN(TEQUAL);
":="                    return TOKEN(TASSIGN);
"<>"                    return TOKEN(TCNE);
">="                    return TOKEN(TGE);
"<="                    return TOKEN(TLE);
">"                     return TOKEN(TGT);
"<"                     return TOKEN(TLT);

"("                     return TOKEN(TLP);
")"                     return TOKEN(TRP);
"["                     return TOKEN(TLB);
"]"                     return TOKEN(TRB);

","                     return TOKEN(TCOMMA);
".."                    return TOKEN(TDOTDOT);
"."                     return TOKEN(TDOT);
":"                     return TOKEN(TCOLON);
";"                     return TOKEN(TSEMI);

"+"                     return TOKEN(TPLUS);
"-"                     return TOKEN(TMINUS);
"*"                     return TOKEN(TMUL);
"/"                     return TOKEN(TDIV);



%%