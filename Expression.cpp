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

TStack<std::tuple<std::string, int, bool, bool, int>>* Expression::getStack(int op){
    if(op == 1){
        return operatorStack;
    } else if(op == 2){
        return operandStack;
    } else if(op == 3){
        return reversePolishStack;
    } else if(op == 4){
        TStack<std::tuple<std::string, int, bool, bool, int>>* s = new TStack<std::tuple<std::string, int, bool, bool, int>>();
        return s;
    }
}

void Expression::pushStack(TStack<std::tuple<std::string, int, bool, bool, int>>* pointerStack, std::tuple<std::string, int, bool, bool, int> token){
    pointerStack->push(token);
    //std::cout << std::get<0>(token) << " ";
}

void Expression::popStack(TStack<std::tuple<std::string, int, bool, bool, int>>* pointerStack){
    std::cout << std::get<0>(topStack(pointerStack)) << " ";
    pointerStack->pop();
}

std::tuple<std::string, int, bool, bool, int> Expression::topStack(TStack<std::tuple<std::string, int, bool, bool, int>>* pointerStack){
    return pointerStack->top();
}

void Expression::eval(std::string &exp){
    exp = "(" + exp + ")";
    removeSpaces(exp);
    Token* token = new Token(exp);
    token->checkTokens();
    mapTokens = token->getMapToken();
    reversePolish(mapTokens);
}

void Expression::reversePolish(std::vector<std::tuple<std::string, int, bool, bool, int>> mapTkn){

    int l = mapTkn.size();
    for (int i = 0; i < l; i++){
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
		popStack(getStack(2));
	}
	system("pause");
}

bool Expression::HigerPriority(int op1, int op2){
    if(op1 <= op2){
        return true;
    }
    return false;
}

void Expression::solve(bool unary){
    std::string tk = std::get<0>(topStack(getStack(1)));
    Operations* op = new Operations();
    double result = 0.0, a = 0.0, b = 0.0, c = 0.0;


    if(unary){
        c = std::stod(std::get<0>(topStack(getStack(2))));
        popStack(getStack(2));
    } else{
        a = std::stod(std::get<0>(topStack(getStack(2))));
        popStack(getStack(2));
        b = std::stod(std::get<0>(topStack(getStack(2))));
        popStack(getStack(2));
    }

    if(tk == "+"){
        result = op->add(a, b);
    } else if(tk == "-"){
        result = op->sub(a, b);
    } else if(tk == "*"){
        result = op->mul(a, b);
    } else if(tk == "/"){
        result = op->div(a, b);
    } else if(tk == "^"){
        result = op->pow(a, b);
    } else if(tk == "sqrt"){
        //resultop->sqrt(c);
    } else if(tk == "abs"){
        result = op->abs(c);
    } else if(tk == "log"){
        result = op->log(c);
    } else if(tk == "sin"){
        result = op->sin(c);
    } else if(tk == "cos"){
        result = op->cos(c);
    } else if(tk == "tan"){
        result = op->tan(c);
    }
    std::tuple<std::string, int, bool, bool, int> r;

    std::ostringstream aux;
    aux << result;
    std::string str = aux.str();

    std::get<0>(r) = str;
    std::get<1>(r) = 0;
    std::get<2>(r) = false;
    std::get<3>(r) = false;
    std::get<4>(r) = 0;
    pushStack(getStack(3), r);
    popStack(getStack(1));
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
