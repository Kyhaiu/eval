#include "Expression.h"


Expression::Expression(){
    setExpression("");
    stackReversePolish = nullptr;
    stackOperator = nullptr;
}


Expression::Expression(const std::string &_exp){
    setExpression(_exp);
    stackReversePolish = createStack();
    stackOperator = createStack();
}

TStack<std::string>* Expression::createStack(){
    TStack<std::string>* Stack = new TStack<std::string>();
    return Stack;
}

std::string Expression::getExpression(){
    return expression;
}

TStack<std::string>* Expression::getStackReversePolish(){
    if(stackReversePolish == nullptr){
        stackReversePolish = createStack();
    }
    return stackReversePolish;
}

TStack<std::string>* Expression::getOperatorStack(){
    if(stackOperator == nullptr){
        stackOperator = createStack();
    }
    return stackOperator;
}

void Expression::setExpression(const std::string &exp){
    expression = exp;
}

void Expression::StackReversePolish(const std::string &tkn){
    TStack<std::string>* polishReverseStack = getStackReversePolish();
    polishReverseStack->push(tkn);
    polishReverseStack->printStack();
}

void Expression::StackOperator(const std::string &tkn){
    TStack<std::string>* operatorStack = getOperatorStack();
    operatorStack->push(tkn);
    operatorStack->printStack();
}

void Expression::eval(std::string &exp){
    removeParenthesesAndSpaces(exp);
    int i = 0, j = 0;
    std::string result;
    while(exp[i] != '\0'){
        j = findNextToken(exp, i);
        if(j == -1){
            i++;
            continue;
        }else if(j == 0){
            j++;
        }
        Token* token = new Token(exp.substr(i, j));
        token->checkToken();
        if(std::get<0>(token->getTypeToken())){
            if(reversePolish(token)){
                StackOperator(token->getRecivedToken());
            } else{
                //result = solving(token->getRecivedToken());
                //StackReversePolish(result);
                //result = "";
                ///ta aqui, precisa pensar num jeito de resolver o tamanho da string, pq quando vc cria uma string vazia ele coloca
                ///como 0 o tamanho dela, só que quando vc faz uma nova atribuição ele até coloca o valor, porem não atualiza o tamanho
                ///e quando vc passa uma string na função, ele pega a quantidade de caracteres informado no tamanho da string ou seja 0
            }
        } else{
            StackReversePolish(token->getRecivedToken());
        }
        delete token;
        i++;
        j = 0;
    }
}

int Expression::findNextToken(const std::string &exp, int i){
    int j = 0;
    while(exp[i] != '\0'){
        if(separators.find(exp[i]) != -1){
            return j;
        } else{
            i++;
            j++;
        }
    }
    j--;
    return j;
}

void Expression::removeParenthesesAndSpaces(std::string &exp){
    int i = 0, j = 0;
    std::string aux;
    aux.resize(countingParenthesesAndSpaces(exp));
    while(exp[i] != '\0'){
        if(exp[i] != ' ' && exp[i] != '(' && exp[i] != ')'){
            aux[j] = exp[i];
            j++;
        }
        i++;
    }
    exp.resize(aux.size());
    exp = aux;
}

int Expression::countingParenthesesAndSpaces(std::string &exp){
    int i = 0,  j = 0;
    while(exp[i] != '\0'){
        if(exp[i] != ' ' && exp[i] != '(' && exp[i] != ')'){
            j++;
        }
        i++;
    }
    return j;
}

bool Expression::reversePolish(Token* token){
    TStack<std::string>* operatorStack = getOperatorStack();
    if(operatorStack->isempty()){
        return true;
    }
    std::string operatorInStack = operatorStack->top();
    if(token->checkPriorityOperator(token, operatorInStack)){
        return true;
    }
    return false;
}
