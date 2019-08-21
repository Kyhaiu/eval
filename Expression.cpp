#include "Expression.h"

Expression::Expression(){
    std::string e = "";
    setExpression(e);
    operatorStack = nullptr;
    operandStack = nullptr;
    reversePolishStack = nullptr;
}

Expression::Expression(std::string &exp){
    setExpression(exp);
    operatorStack = getStack(4);
    operandStack = getStack(4);
    reversePolishStack = getStack(4);
}

std::string Expression::getExpression(){
    return expression;
}

void Expression::setExpression(std::string &exp){
    expression = exp;
}

TStack<std::tuple<std::string, int, bool, bool>>* Expression::getStack(int op){
    if(op == 1){
        return operatorStack;
    } else if(op == 2){
        return operandStack;
    } else if(op == 3){
        return reversePolishStack;
    } else if(op == 4){
        TStack<std::tuple<std::string, int, bool, bool>>* s = new TStack<std::tuple<std::string, int, bool, bool>>();
        return s;
    }
    return nullptr; //apenas para tirar o warning
}

void Expression::pushStack(TStack<std::tuple<std::string, int, bool, bool>>* pointerStack, std::tuple<std::string, int, bool, bool> token){
    pointerStack->push(token);
    //std::cout << std::get<0>(token) << " ";
}

void Expression::popStack(TStack<std::tuple<std::string, int, bool, bool>>* pointerStack){
    std::cout << std::get<0>(topStack(pointerStack)) << " " << std::flush;
    pointerStack->pop();
}

std::tuple<std::string, int, bool, bool> Expression::topStack(TStack<std::tuple<std::string, int, bool, bool>>* pointerStack){
    return pointerStack->top();
}

void Expression::eval(std::string &exp){
    exp = "(" + exp + ")";
    removeVariables(exp);
    removeSpaces(exp);
    Token* token = new Token(exp);
    token->checkTokens();
    mapTokens = token->getMapToken();
    system("cls");
    for(int i = 0; i < (int)mapTokens.size(); i++)
        std::cout << std::get<0>(mapTokens[i]) << " ";
    reversePolish(mapTokens);
}

void Expression::reversePolish(std::vector<std::tuple<std::string, int, bool, bool>> mapTkn){
    for (int i = 0; i < (int)mapTkn.size(); i++){
        if(std::get<2>(mapTkn[i])){
            if(std::get<0>(mapTkn[i]) == "("){
                pushStack(getStack(1), mapTkn[i]);
            } else if(std::get<0>(mapTkn[i]) == ")"){
                while(std::get<0>(topStack(getStack(1))) != "("){
                    pushStack(getStack(2), topStack(getStack(1)));
                    popStack(getStack(1));
                }
                popStack(getStack(1));
            } else if(std::get<2>(mapTkn[i])){
                while(HigerPriority(std::get<1>(mapTkn[i]), std::get<1>(topStack(getStack(1))))){
                    pushStack(getStack(2), topStack(getStack(1)));
                    popStack(getStack(1));
                }
                pushStack(getStack(1), mapTkn[i]);
            }
        } else {///caso for numero
            pushStack(getStack(2), mapTkn[i]);
        }
    }
    std::cout << std::endl;
    system("cls");
	while(!getStack(2)->isEmpty()) {
		pushStack(getStack(3), getStack(2)->top());
		popStack(getStack(2));
	}
	system("pause");
    solve();
}

bool Expression::HigerPriority(int op1, int op2){
    if(op1 <= op2){
        return true;
    }
    return false;
}

void Expression::solve(){
    system("cls");
    double num1, num2;
    std::tuple<std::string, int, bool, bool> aux;
    while(!getStack(3)->isEmpty()){
        if(!std::get<2>(getStack(3)->top())){
            pushStack(getStack(2), getStack(3)->top());
            popStack(getStack(3));
        }else{
            if(std::get<0>(getStack(3)->top()) == "+"){
                num2 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::add(num1, num2));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "-"){
                num2 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::sub(num1, num2));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "*"){
                num2 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::mul(num1, num2));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "/"){
                num2 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::div(num1, num2));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "^"){
                num2 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::pow(num1, num2));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "sqrt"){
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::sqrt(num1));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "log"){
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::log(num1));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "abs"){
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::abs(num1));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "sen"){
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::sin(num1));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "cos"){
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::cos(num1));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            } else if(std::get<0>(getStack(3)->top()) == "tan"){
                num1 = std::stod(std::get<0>(topStack(getStack(2))));
                popStack(getStack(2));
                std::get<0>(aux) = std::to_string(Operations::tan(num1));
                std::get<2>(aux) = 0;
                std::get<2>(aux) = false;
                std::get<2>(aux) = false;
                popStack(getStack(3));
                pushStack(getStack(2), aux);
            }
        }
    }
    system("cls");
    popStack(getStack(2));
    system("pause");
}

void Expression::removeSpaces(std::string &exp){
    int i = 0, j = 0, k = 0;
    while(exp[i] != '\0'){
        if(exp[i] != ' '){
            j++;
        }
        i++;
    }
    std::string aux;
    aux.resize(j);
    i = 0;
    while(exp[i] != '\0'){
        if(exp[i] != ' '){
            aux[k] = exp[i];
            k++;
        }
        i++;
    }
    exp.resize(j);
    exp = aux;
}

void Expression::removeVariables(std::string &exp){
    int i = 0;
    std::regex e("[A-Z]");
    std::smatch m;
    while(exp[i] != '\0'){
        std::string newExp, variable;
        std::string temp = exp.substr(i, 1);
        if(exp.substr(i, 2) == "PI"){
            newExp = exp.substr(0, i) + "3.1415926535898" + exp.substr(i+2, exp.size());
            exp = newExp;
            newExp = "";
            i = i + 14;
        } else if(std::regex_search(temp ,m,e)){
            std::cout << "Informe o valor da variavel 0 " << exp[i] << ": ";
            std::cin >> variable;
            newExp = exp.substr(0, i) + variable + exp.substr(i+1, exp.size());
            exp = newExp;
            variable = "";
            continue;
        }
        i++;
    }
}
