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

TStack<std::string>* Expression::createStack(){ /// cria a pilha
    TStack<std::string>* Stack = new TStack<std::string>();
    return Stack;
}

std::string Expression::getExpression(){ ///retorna a express�o digitada pelo usu�rio
    return expression;
}

TStack<std::string>* Expression::getStackReversePolish(){ /// retorna a pilha da express�o na forma polonesa reversa
    if(stackReversePolish == nullptr){
        stackReversePolish = createStack();
    }
    return stackReversePolish;
}

TStack<std::string>* Expression::getOperatorStack(){ /// retorna a pilha dos operadores/fun��es
    if(stackOperator == nullptr){
        stackOperator = createStack();
    }
    return stackOperator;
}

std::tuple<std::string, bool, bool> Expression::getPreviousToken(){ ///retorna o token anterior
    return previuosToken;
}

void Expression::setPreviousToken(std::string _previousToken, bool _operand, bool _unary){ /// seta o token anterior
    std::get<0>(previuosToken) = _previousToken;
    std::get<1>(previuosToken) = _operand;
    std::get<2>(previuosToken) = _unary;
}

void Expression::setExpression(const std::string &exp){ ///seta a expressao que o usuario digitou
    expression = exp;
}

void Expression::StackReversePolish(const std::string &tkn){///empilha os valores/operadores na pilha da polonesa reversa
    TStack<std::string>* polishReverseStack = getStackReversePolish();
    polishReverseStack->push(tkn);
    system("cls");
}

void Expression::StackOperator(const std::string &tkn){/// empilha os operadores na pilha deles
    TStack<std::string>* operatorStack = getOperatorStack();
    operatorStack->push(tkn);
    system("cls");
}

void Expression::PopReversePolish(){ /// remove do topo da pilha da polonesa reversa
    TStack<std::string>* polishReverseStack = getStackReversePolish();
    polishReverseStack->pop();
}

void Expression::PopOperator(){ /// remove da pilha dos operadores
    TStack<std::string>* operatorStack = getOperatorStack();
    operatorStack->pop();
}

void Expression::PrintReversePolish(){///printa a pilha da polonesa reversa(teste/debug)
    TStack<std::string>* polishReverseStack = getStackReversePolish();
    system("cls");
    polishReverseStack->printStack();
}

std::string Expression::TopReversePolish(){///consulta o topo da pilha da poloesa reversa
    TStack<std::string>* polishReverseStack = getStackReversePolish();
    return polishReverseStack->top();
}

std::string Expression::TopOperator(){///consulta o topo da pilha dos operadores
    TStack<std::string>* operatorStack = getOperatorStack();
    return operatorStack->top();
}

void Expression::solvingExpression(std::string &exp){///fun��o chamada no main
    removeParenthesesAndSpaces(exp);
    /*std::ostringstream result;
    double aux = 0.0;
    result << aux;
    std::string str = result.str();*/
    int aux = findNextToken(exp, 0);
    std::string _token = exp.substr(0, aux);
    eval(exp, getPreviousToken(), _token, aux+1);
}

///a inte��o dessa fun��o recursiva � ir percorrendo at� achar um caso onde viole a polonesa reversa(ou final de string, mas o segundo caso falta implementar, e to com mto sono) ou quando achar um menos un�rio
void Expression::eval(std::string &exp, std::tuple<std::string, bool, bool> _previuosToken, std::string _token, int i){
    Token* token = new Token(_token);
    token->checkToken();
    if(std::get<1>(_previuosToken) == true && _token == "-"){ ///caso o token anterior for um operador e o token atual seja um -, isso significa que � um menos unario

    } else if(std::get<1>(_previuosToken) == true && std::get<1>(token->getTypeToken()) == true){ /// significa que � uma fun��o un�ria(sqrt, log, tan, ...)

    } else if(std::get<0>(token->getTypeToken()) == true){///caso o token atual seja um operador
        if(token->checkPriorityOperator(token, std::get<0>(_previuosToken))){ /// violou a polonesa reversa, ent�o precisa resolver

        } else{
            StackOperator(_token); /// empilha o operador
        }
    } else if(std::get<0>(token->getTypeToken()) == false){///caso o token atual seja um numero
        StackReversePolish(_token);
    }
    ///monta a tuple do token anterior
    std::tuple<std::string, bool, bool> prevTk = {_token, std::get<0>(token->getTypeToken()), std::get<1>(token->getTypeToken())};
    int aux = findNextToken(exp, 0); ///procura o proximo token
    eval(exp, prevTk, exp.substr(i, aux), i+1); ///chama de novo
}

int Expression::findNextToken(const std::string &exp, int i){///fun��o procura o indice do proximo token
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

void Expression::removeParenthesesAndSpaces(std::string &exp){///remove parenteses e espa�os
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

int Expression::countingParenthesesAndSpaces(std::string &exp){///fun��o s� � usada na fun��o acima para remover os espa�os, ela basicamente conta o tamanho da string sem os parenteses e espa�os
    int i = 0,  j = 0;
    while(exp[i] != '\0'){
        if(exp[i] != ' ' && exp[i] != '(' && exp[i] != ')'){
            j++;
        }
        i++;
    }
    return j;
}

bool Expression::reversePolish(Token* token){///checa se violou a regra da polonesa reversa(reformular)
    ///para violar a polonesa reversa, � preciso tentar empilhar um operador com menor prioridade na pilha, ou acabar a string
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

double Expression::solving(std::string _op, bool unary){///fun��o que resolve depois de ter colocado na forma polonesa reversa(reformular talvez)
    Operations* operation = new Operations();
    double a = 0.0, b = 0.0;

    if(_op == "+"){
        a = std::stod(TopReversePolish());
        PopReversePolish();
        b = std::stod(TopReversePolish());
        PopReversePolish();
        return operation->add(a, b);
    } else if(_op == "-"){
        a = std::stod(TopReversePolish());
        PopReversePolish();
        b = std::stod(TopReversePolish());
        PopReversePolish();
        return operation->sub(a, b);
    } else if(unary == true){///caso seja o - un�rio
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
