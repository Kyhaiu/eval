#include <iostream>
#include "Expression.h"

int main(){
        std::string e = "-(-5+4/5-5)";
        Expression* exp = new Expression(e);
        exp->eval(e);
}
