#include <iostream>
#include "Expression.h"

int main(){
        std::string e = "(C - log(B))";
        Expression* exp = new Expression(e);
        exp->eval(e);
}
