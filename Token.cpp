#include "Token.h"

Token::Token(){
    setTypeToken(false, false);
    setRecivedToken("");
}

Token::Token(const std::string &_token){
    setTypeToken(false, false);
    setRecivedToken(_token);
}

bool Token::isUnary(const std::string &_token){
    for(int i = 0; i < (int)operators.size(); i++){
        if(std::get<0>(operators[i]) == _token && std::get<2>(operators[i]) == true){
            return true;
        }
    }
    return false;
}

bool Token::isOperator(const std::string &_token){
    for(int i = 0; i < (int)operators.size(); i++){
        if(std::get<0>(operators[i]) == _token){
            return true;
        }
    }
    return false;
}

double Token::asNumber(const std::string &_token){
    double number = std::stod(_token);
    return number;
}

std::string Token::getRecivedToken(){
    return receivedToken;
}

std::tuple<bool, bool> Token::getTypeToken(){
    return typeToken;
}
double Token::getNumber(){
    return number;
}

void Token::setRecivedToken(const std::string &_token){
    receivedToken = _token;
}

void Token::setTypeToken(bool typeOp, bool unary){
    std::get<0>(typeToken) = typeOp;
    std::get<1>(typeToken) = unary;
}

void Token::setNumber(const double &_number){
    number = _number;
}

void Token::checkToken(){
    std::string _token = getRecivedToken();
    if(isOperator(_token)){
        if(isUnary(_token)){
            setTypeToken(true, true);
        } else{
            setTypeToken(true, false);
        }
    } else{
        setTypeToken(false, false);
        double _number = asNumber(_token);
        setNumber(_number);
    }
}
