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

std::tuple<std::string, bool, bool> Expression::getPreviousToken(){
    return previuosToken;
}

void Expression::setPreviousToken(std::string _previousToken, bool _operand, bool _unary){
    std::get<0>(previuosToken) = _previousToken;
    std::get<1>(previuosToken) = _operand;
    std::get<2>(previuosToken) = _unary;
}

void Expression::setExpression(const std::string &exp){
    expression = exp;
}

void Expression::StackReversePolish(const std::string &tkn){
    TStack<std::string>* polishReverseStack = getStackReversePolish();
    polishReverseStack->push(tkn);
    system("cls");
}

void Expression::StackOperator(const std::string &tkn){
    TStack<std::string>* operatorStack = getOperatorStack();
    operatorStack->push(tkn);
    system("cls");
}

void Expression::PopReversePolish(){
    TStack<std::string>* polishReverseStack = getStackReversePolish();
    polishReverseStack->pop();
}

void Expression::PopOperator(){
    TStack<std::string>* operatorStack = getOperatorStack();
    operatorStack->pop();
}

void Expression::PrintReversePolish(){
    TStack<std::string>* polishReverseStack = getStackReversePolish();
    system("cls");
    polishReverseStack->printStack();
}

std::string Expression::TopReversePolish(){
    TStack<std::string>* polishReverseStack = getStackReversePolish();
    return polishReverseStack->top();
}

std::string Expression::TopOperator(){
    TStack<std::string>* operatorStack = getOperatorStack();
    return operatorStack->top();
}

void Expression::eval(std::string &exp){
    removeParenthesesAndSpaces(exp);
    int i = 0, j = 0;
    std::ostringstream result;
    double aux = 0.0;
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

        std::tuple<bool, bool> tpTkn = token->getTypeToken();
        std::tuple<std::string, bool, bool> previousTkn = getPreviousToken();

        if(std::get<1>(previousTkn) == true && token->getRecivedToken() == "-"){
            j = findNextToken(exp, i);
        } else if(){
        } else if(){
        } else if(std::get<0>(tpTkn)){ ///caso seja um operador
            if(reversePolish(token)){ /// coloca ele na pilha caso não viole a regra da Polonesa reversa
                StackOperator(token->getRecivedToken());
                setPreviousToken(token->getRecivedToken(), std::get<0>(tpTkn), std::get<1>(tpTkn));
            } else{ ///se violar a regra da polonesa reversa, então resolve(isso ta cheirando recursividade)
                aux = solving(token->getRecivedToken(), std::get<1>(token->getTypeToken()));
                result << aux;
                std::string str = result.str();
                StackReversePolish(str);
                StackReversePolish(TopOperator());
                PopOperator();
                PrintReversePolish();
                setPreviousToken(token->getRecivedToken(), std::get<0>(tpTkn), std::get<1>(tpTkn));
            }
        } else{
            StackReversePolish(token->getRecivedToken());
            setPreviousToken(token->getRecivedToken(), std::get<0>(tpTkn), std::get<1>(tpTkn));
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

double Expression::solving(std::string _op, bool unary){
    Operations* operation = new Operations();
    double a = 0.0, b = 0.0;

    if(_op == "+"){
        a = std::stod(TopReversePolish());
        PopReversePolish();
        b = std::stod(TopReversePolish());
        PopReversePolish();
        return operation->add(a, b);
    } else if(_op == "-" && unary == false){
        a = std::stod(TopReversePolish());
        PopReversePolish();
        b = std::stod(TopReversePolish());
        PopReversePolish();
        return operation->sub(a, b);
    } else if(unary == true){
        a = std::stod(_op);
        b = -1;
        return operation->mul(a, b);
    } else if(_op == "*"){
        a = std::stod(TopReversePolish());
        PopReversePolish();
        b = std::stod(TopReversePolish());
        PopReversePolish();
        return operation->mul(a, b);
    } else if(_op == "/"){
        a = std::stod(TopReversePolish());
        PopReversePolish();
        b = std::stod(TopReversePolish());
        PopReversePolish();
        return operation->div(a, b);
    } else if(_op == "^"){
        a = std::stod(TopReversePolish());
        PopReversePolish();
        b = std::stod(TopReversePolish());
        PopReversePolish();
        return operation->pow(a, b);
    }
}
