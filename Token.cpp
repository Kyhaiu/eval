#include "Token.h"

Token::Token(){
    expression = "";
}

Token::Token(std::string &exp){
    expression = exp;
}

std::string Token::getExpression(){
    return expression;
}

std::tuple<std::string, int, bool, bool, int> Token::getToken(int i){
    return tkns[i];
}

std::vector<std::tuple<std::string, int, bool, bool, int>>& Token::getMapToken(){
    return tkns;
}

int Token::getPriority(std::string &tk){
    int i = 0;
    while(tk != std::get<0>(operations[i])){
        i++;
    }
    return std::get<1>(operations[i]);
}

void Token::setToken(std::tuple<std::string, int, bool, bool, int> _tkns, int j){
    int i = 0;
    for(i; i < j; i++){}
    tkns.push_back(_tkns);
}

std::string Token::findNextToken(std::string exp, int &i){
    int j = i, k = 0;
    while(exp[j] != '\0'){
        if(separators.find(exp[j]) != std::string::npos){
            j--;
            break;
        }
        if(isFunction(exp, j)){
            if(exp[j+1] == 'q'){
                k = 4;
                j = j + k-1;
                break;
            } else{
                k = 3;
                j = j + k-1;
                break;
            }
        }
        j++;
        k++;
    }
    if(k == 0){
        k++;
    }
    std::string tk = exp.substr(i, k);
    if(i == j){
        j++;
    } else if(i > j){
        j = j + 2;
    } else{
        j++;
    }
    i = j;
    return tk;
}

bool Token::isUnary(std::string tk){
    int i = 0;
    while(std::get<0>(operations[i]) != tk){
        i++;
    }
    return std::get<3>(operations[i]);
}

bool Token::isOperator(std::string tk){
    int i = 0;
    while(i < operations.size()){
        if(std::get<0>(operations[i]) == tk){
            return true;
        }
        i++;
    }
    return false;
}

bool Token::isVariable(std::string tk){
    return false;
}

bool Token::isFunction(std::string exp, int i){
    std::string functions = "sqrtabslogsincostan";
    if(functions.find(exp.substr(i, 4)) != -1 || functions.find(exp.substr(i, 3)) != -1){
        return true;
    }
    return false;
}

void Token::checkTokens(){
    std::string exp = getExpression();
    std::string tk = "";
    std::tuple<std::string, int, bool, bool, int> tkn;
    int i = 0, j = 0;
    while(exp[i] != '\0'){
        tk = findNextToken(exp, i);
        if(tk == "(" || tk == ")"){
            std::get<0>(tkn) = tk;
            std::get<1>(tkn) = 0;
            std::get<2>(tkn) = true;
            std::get<3>(tkn) = true;
            std::get<4>(tkn) = 0;
        } else{
            std::get<0>(tkn) = tk;
            if(isOperator(tk)){
                std::get<1>(tkn) = getPriority(tk);
                std::get<2>(tkn) = true;
                if(isUnary(tk)){
                    std::get<3>(tkn) = true;
                } else{
                    std::get<3>(tkn) = false;
                }
            } else{
                std::get<1>(tkn) = 0;
                std::get<2>(tkn) = false;
                ///resolver aqui se o menos é unario, pegando o ultimo operador no map e vendo se ele é uma função
                std::get<3>(tkn) = false;
            }
        }
        std::get<4>(tkn) = i;
        setToken(tkn, j);
        j++;
    }
}
