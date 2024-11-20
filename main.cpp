#include "tokens.hpp"
#include "output.hpp"
#include <iostream>

using namespace output;

int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        printToken(yylineno,token,yytext);
    }
    return 0;
}