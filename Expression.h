#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED
#include "TStack.cpp"
#include "Token.h"
#include <string>
#include <iostream>

class Expression{
    private:
        ///variavel que armazena a expressão recebida
        std::string expression;
        ///constante define os separadores entre os operandos
        const std::string separators = "+-*/^";
        ///pilha dos operandos
        TStack<std::string>* stackOperand;
        ///pilha dos operadores(nessa pilha o Ordis pira)
        TStack<std::string>* stackOperator;
        ///cria as stacks caso elas não exitam
        TStack<std::string>* createStack();
    public:
        ///construtores da classe
        Expression();
        Expression(const std::string &_exp);
        ///getters da classe
        std::string getExpression();
        TStack<std::string>* getOperandStack();
        TStack<std::string>* getOperatorStack();
        ///setters da classe
        void setExpression(const std::string &exp);
        ///metodos que colocam o valor a pilha
        void StackOperand(const std::string &tk);
        void StackOperator(const std::string &tk);
        ///metodos da classe
        ///avaliador de expressões aritméticas
        void eval(std::string &exp);
        ///encontra o proximo separador e retorna o seu indice
        int findNextToken(const std::string &exp, int i);
        ///minha propria função replace
        ///remove os parenteses
        void removeParenthesesAndSpaces(std::string &exp);
        ///conta os parenteses(usado na função de cima)
        int countingParenthesesAndSpaces(std::string &exp);
};

#endif // EXPRESSION_H_INCLUDED
