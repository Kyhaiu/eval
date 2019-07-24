#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED
#include "TStack.cpp"
#include "Token.h"
#include "Operations.h"
#include <string>
#include <tuple>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>

class Expression{
    private:
        std::string expression;
        TStack<std::tuple<std::string, int, bool, bool, int>>* operatorStack;
        TStack<std::tuple<std::string, int, bool, bool, int>>* operandStack;
        TStack<std::tuple<std::string, int, bool, bool, int>>* reversePolishStack;
        std::vector<std::tuple<std::string, int, bool, bool, int>> mapTokens;
    public:
        Expression();
        Expression(std::string &exp);
        ///getters da classe
        std::string getExpression();
        ///setters da classe
        void setExpression(std::string &exp);
        ///metodos das pilhas
        TStack<std::tuple<std::string, int, bool, bool, int>>* getStack(int op);
        void pushStack(TStack<std::tuple<std::string, int, bool, bool, int>>* pointerStack, std::tuple<std::string, int, bool, bool, int> token);
        void popStack(TStack<std::tuple<std::string, int, bool, bool, int>>* pointerStack);
        std::tuple<std::string, int, bool, bool, int> topStack(TStack<std::tuple<std::string, int, bool, bool, int>>* pointerStack);
        ///metodos da classe
        void eval(std::string &exp);
        void reversePolish(std::vector<std::tuple<std::string, int, bool, bool, int>> mapTkn);
        bool HigerPriority(int op1, int op2);
        void solve();
        void removeSpaces(std::string &exp);
        void removeVariables(std::string &exp);
};

#endif // EXPRESSION_H_INCLUDED
