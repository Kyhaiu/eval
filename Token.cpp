#include "Token.h"
#include <iostream>

Token::Token(const std::string &_char){
    operand = false;
    int priority;
    if(isOperator(_char)){
        typeOp = asOperator(_char);
        operand = false;
    } else{
        operand = true;
    }
}

bool Token::isOperator(const std::string &_char){
    for(int i = 0; i < (int)tokens.size(); i++){
        if(std::get<0>(tokens[i]) == _char){
            return true;
        }
    }
    return false;
}

double Token::asNumber(const std::string &_char){
    double number =0.0;
    number = std::stod(_char);
    return number;
}

std::tuple<std::string, int, bool> Token::asOperator(const std::string &_char){
    for(int i = 0; i < (int)tokens.size(); i++){
        if(std::get<0>(tokens[i]) == _char){
            return tokens[i];
        }
    }
}
