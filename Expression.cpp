#include "Expression.h"


Expression::Expression(){
    setExpression("");
    stackOperand = nullptr;
    stackOperator = nullptr;
}


Expression::Expression(const std::string &_exp){
    setExpression(_exp);
    stackOperand = createStack();
    stackOperator = createStack();
}

TStack<std::string>* Expression::createStack(){
    TStack<std::string>* Stack = new TStack<std::string>();
    return Stack;
}

std::string Expression::getExpression(){
    return expression;
}

TStack<std::string>* Expression::getOperandStack(){
    if(stackOperand == nullptr){
        stackOperand = createStack();
    }
    return stackOperand;
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

void Expression::StackOperand(const std::string &tkn){
    TStack<std::string>* operandStack = getOperandStack();
    operandStack->push(tkn);
    operandStack->printStack();
}

void Expression::StackOperator(const std::string &tkn){
    TStack<std::string>* operatorStack = getOperatorStack();
    operatorStack->push(tkn);
    operatorStack->printStack();
}

void Expression::eval(std::string &exp){
    removeParenthesesAndSpaces(exp);
    int i = 0, j = 0;
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
            StackOperator(token->getRecivedToken());
        } else{
            StackOperand(token->getRecivedToken());
        }
        delete token;
        i++;
        j = 0;
    }
}

int Expression::findNextToken(const std::string &exp, int i){
    while(exp[i] != '\0'){
        if(separators.find(exp[i]) != -1){
            i--;
            return i;
        } else{
            i++;
        }
    }
    i--;
    return i;
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
