%{
#include "tokens.hpp"

void my_print(){
    printf("what\n");
}
%}

%option noyywrap

digit [0-9]
first_digit [1-9]
whitespace [ \t\r]  
letter [a-zA-Z]
relop "=="|"!="|"<"|">"|"<="|">="
binop "-"|"*"|"+"|"/"

%x comment id string hexa


%%

void    return VOID;
int     return INT;
byte     return BYTE;
bool     return BOOL;
and     return AND;
or     return OR;
not     return NOT;
true     return TRUE;
false     return FALSE;
return     return RETURN;
if     return IF;
else     return ELSE;
while     return WHILE;
break     return BREAK;
continue     return CONTINUE;
;           return SC;
,           return COMMA;
\(           return LPAREN;
\)           return RPAREN;
=           return ASSIGN;
{relop}     return RELOP;
{binop}     return BINOP;
"//"         {
    BEGIN (comment);
}
<comment>[^\n]*     {
    BEGIN (INITIAL);
    return COMMENT;
}

[a-zA-Z]+[a-zA-Z0-9]*     return ID;


[1-9][0-9]*b|0b       return NUM_B;
[1-9][0-9]*|0         return NUM;

\"          yymore();BEGIN(string);
<string>\x                  yymore();BEGIN(hexa);
<hexa>[0-9][0-9]            yymore();BEGIN(string);
<string>.*\"                   BEGIN(INITIAL);return STRING;

{whitespace}+ ;


\n  {yylineno++;}
. {return VOID;}

%%

void my_print();

