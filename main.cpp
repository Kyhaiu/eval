#include <iostream>
#include "Expression.h"

int main(){
        std::string e = "-(5+4*-log((2+3)*4))";
        Expression* exp = new Expression(e);
        exp->eval(e);
}
