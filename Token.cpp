#include "Token.h"

Token::Token(){
    setTypeToken(false, false);
    setRecivedToken("");
    setPriority(0);
}

Token::Token(const std::string &_token){
    setTypeToken(false, false);
    setRecivedToken(_token);
    setPriority(0);
}

bool Token::isUnary(const std::string &_token){///verifica se o operador é unário
    for(int i = 0; i < (int)operators.size(); i++){
        if(std::get<0>(operators[i]) == _token && std::get<2>(operators[i]) == true){
            return true;
        }
    }
    return false;
}

bool Token::isOperator(const std::string &_token){///verifica se é um operador aritimético/função
    for(int i = 0; i < (int)operators.size(); i++){
        if(std::get<0>(operators[i]) == _token){
            return true;
        }
    }
    return false;
}

std::string Token::getRecivedToken(){
    return receivedToken;
}

std::tuple<bool, bool> Token::getTypeToken(){
    return typeToken;
}

int Token::getPriority(std::string _token){///procura na constante operators a prioridade do operador e retorna ela
    int i = 0;
    while(std::get<1>(operators[i]) <= 4){
        if(std::get<0>(operators[i]) == _token){
            priority = std::get<1>(operators[i]);
        }
        i++;
    }
    return priority;
}

void Token::setRecivedToken(const std::string &_token){
    receivedToken = _token;
}

void Token::setTypeToken(bool typeOp, bool unary){
    std::get<0>(typeToken) = typeOp;///1° paremetro indica se é numero ou função(true pra função, false pra numero)
    std::get<1>(typeToken) = unary;///2° parametro indica se é unario ou nao
}

void Token::setPriority(int _priority){
    priority = _priority;
}

void Token::checkToken(){///checa o token e seta o tipo(se é numero ou função e se é unario ou não)
    std::string _token = getRecivedToken();
    if(isOperator(_token)){
        if(isUnary(_token)){
            setTypeToken(true, true); ///função unária(sqrt,sin, cos, tan,...)
        } else{
            setTypeToken(true, false); ///operadores aritiméticos e função ^(potencia)
        }
    } else{
        setTypeToken(false, false); ///numero normal
    }
}

bool Token::checkPriorityOperator(Token* token, std::string tokenInStack){///verifica se a prioridade de um operador aritimético é maior do que a outra(usado na função pra verificar se viola a polonesa reversa)
    int tokenInStackPriority = getPriority(tokenInStack);
    int tokenCompared = token->getPriority(token->getRecivedToken());

    if(tokenCompared < tokenInStackPriority){
        return true;
    }
    return false;
}
