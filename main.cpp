#include "tokens.hpp"
#include "output.hpp"
#include "aux.h"
#include <iostream>
#include <string>



using namespace output;
using namespace std;




int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        if(token == STRING){
            string res = handleString(yytext);
            printToken(yylineno,token,res.c_str());
        }
        else printToken(yylineno,token,yytext);
    }
    return 0;
}