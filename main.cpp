#include "tokens.hpp"
#include "output.hpp"
#include <iostream>
#include <string>



using namespace output;
using namespace std;

bool printable(const char c){
    return ((c >= 0x20) && (c <= 0x7e));
}


string handleString(const char* val)
{
    string res;
    char prev = 0;
    string v = val;
    for(string::iterator it = v.begin();it!=v.end();){
        if(*it == '\\'){
            if(*(it+1) == 't'){
                res += "\t";
                it+=2;
            }
            else if(*(it+1) == 'r'){
                res += "\r";
                it+=2;
            }
            else if(*(it+1) == 'n'){
                res += "\n";
                it+=2;
                yylineno++;
            }
            else errorUndefinedEscape(val);
        }
        else {
            res += *it;
            it++;
        }
    }
    cout<<"result after fixing the string is: "<<res<<endl;
    return res;
}


int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        if(token == STRING){
            string res = handleString(yytext);
            res = res.substr(1,res.length()-2);
            printToken(yylineno,token,res.c_str());
        }
        else printToken(yylineno,token,yytext);
    }
    return 0;
}