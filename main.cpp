#include <iostream>
#include "Expression.h"

int main(){
        std::string e = "(1+2)";
        Expression* exp = new Expression(e);
        exp->eval(e);
}
