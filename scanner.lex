%{
#include "tokens.hpp"
%}

%option noyywrap



%%

[1-9]+[0-9]*    {return NUM;}
\n  {yylineno++;}
. {return VOID;}

%%


