#include "aux.h"

using namespace std;
using namespace output;

bool printable(const char c){
    return ((c >= 0x20) && (c <= 0x7e));
}


string handleString(const char* val)
{
    string res;
    string v = val;
    char c = v.back();
    if(c!= '\"') errorUnclosedString();
    v = v.substr(1,v.length()-2);
    for(string::iterator it = v.begin();it!=v.end();){
        if(*it=='"'||*it=='\n'||*it=='\r') errorUndefinedEscape(val);
        if(*it == '\\'){
            c = *(it+1);
            unsigned int hex_num;
            string s;
            string error;
            switch(c){
                case('t'):
                    res+="\t";
                    break;
                case('r'):
                    res+="\r";
                    break;
                case('n'):
                    res+="\n";
                    //yylineno++;
                    break;
                case('\\'):
                    res+="\\";
                    break;
                case('"'):
                    res+="\"";
                    break;
                case('x'):
                    s = s + *(it+2) + *(it+3);
                    hex_num = stoi(s,0,16);
                    if(!printable(hex_num)){
                        error = 'x' + s;
                        errorUndefinedEscape(error.c_str());
                        break;
                    }
                    res += static_cast<char>(hex_num);
                    it+=2;
                    break;
                default:
                error = c;
                    errorUndefinedEscape(error.c_str());
            }
            it+=2;
        }
        else {
            res += *it;
            it++;
        }
    }
    return res;
}