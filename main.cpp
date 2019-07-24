#include <iostream>
#include "Expression.h"

int main(){
        std::string e = "A+B+PI";
        Expression* exp = new Expression(e);
        exp->eval(e);
}
