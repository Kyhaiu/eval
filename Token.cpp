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

std::tuple<std::string, int, bool, bool> Token::getToken(int i){
    return tkns[i];
}

std::vector<std::tuple<std::string, int, bool, bool>>& Token::getMapToken(){
    return tkns;
}

int Token::getPriority(std::string &tk){
    int i = 0;
    while(tk != std::get<0>(operations[i])){
        i++;
    }
    return std::get<1>(operations[i]);
}

void Token::setToken(std::tuple<std::string, int, bool, bool> _tkns){
    tkns.push_back(_tkns);
}

std::string Token::findNextToken(std::string exp, int &i){
    int j = i, k = 0, aux = 0;
    while(exp[j] != '\0'){
        while(aux <= 5){
            if(exp.substr(j,1) == std::get<0>(operations[aux]) || exp.substr(j,1) == "(" || exp.substr(j,1) == ")"){
                j--;
                aux = -1;
                break;
            }
            aux++;
        }
        if(aux == -1){
            break;
        }
        aux = 0;
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
    while(i < (int)operations.size()){
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
    int j = 5;
    while(j <= (int)operations.size()){
        if(std::get<0>(operations[j]) == exp.substr(i, 4) || std::get<0>(operations[j]) == exp.substr(i, 3)){
            return true;
        }
        j++;
    }
    return false;
}

void Token::checkTokens(){
    std::string exp = getExpression();
    std::string tk = "";
    std::tuple<std::string, int, bool, bool> tkn;
    int i = 0, j = 0, priority = 0;
    while(i < (int)exp.length()){
        tk = findNextToken(exp, i);
        if(tk == "(" || tk == ")"){
            if(tk == "("){
                priority += 4;
            } else{
                priority -= 4;
            }
            std::get<0>(tkn) = tk;
            std::get<1>(tkn) = priority;
            std::get<2>(tkn) = true;
            std::get<3>(tkn) = true;
        } else{
            std::get<0>(tkn) = tk;
            if(isOperator(tk)){
                std::get<1>(tkn) = priority + getPriority(tk);
                std::get<2>(tkn) = true;
                if(tk == "-" && (std::get<2>(getToken(j-1)) || std::get<0>(getToken(j-1)) == "(")){
                    std::get<3>(tkn) = true;
                }else if(isUnary(tk)){
                    std::get<3>(tkn) = true;
                } else{
                    std::get<3>(tkn) = false;
                }
            } else{
                std::get<1>(tkn) = 0;
                std::get<2>(tkn) = false;
                std::get<3>(tkn) = false;
            }
        }
        setToken(tkn);
        j++;
    }
        for(int y = 0; y < (int)tkns.size(); y++)
        std::cout << std::get<0>(tkns[y]) << " ";

    system("cls");
    solveUnarySub(j);
}

void Token::solveUnarySub(int i){
    int j;
    for(j = 0; j < i ; j++){
        if(std::get<0>(tkns[j]) == "-" && std::get<3>(tkns[j])){
            if(std::get<1>(tkns[j+1]) == 0){
                std::get<0>(tkns[j]) = std::get<0>(tkns[j]) + std::get<0>(tkns[j+1]);
                std::get<1>(tkns[j]) = 0;
                std::get<2>(tkns[j]) = false;
                std::get<3>(tkns[j]) = false;
                tkns.erase(tkns.begin()+j+1);
            }else if(std::get<2>(tkns[j+1])){
                std::string aux;
                aux = getExpression().substr(j+1,1);
                if(aux.compare("(") == 0){
                    aux = getExpression().substr(0, j) + "(-1*(" + getExpression().substr(j+1, getExpression().length()) + "))";
                } else{
                    aux = getExpression().substr(0, j+1) + "(-1*(" + getExpression().substr(j+2, getExpression().length()) + "))";
                }
                expression = aux;
                tkns.clear();
                checkTokens();
                break;
            }
        }
    }
}
