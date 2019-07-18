#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED
#include "TStack.cpp"
#include "Token.h"
#include "Operations.h"
#include <string>
#include <iostream>
#include <sstream>

class Expression{
    private:
        ///variavel que armazena a expressão recebida
        std::string expression;
        ///constante define os separadores entre os operandos
        const std::string separators = "+-*/^";
        std::tuple<std::string, bool, bool> previuosToken;
        ///pilha dos operandos
        TStack<std::string>* stackReversePolish;
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
        TStack<std::string>* getStackReversePolish();
        TStack<std::string>* getOperatorStack();
        std::tuple<std::string, bool, bool> getPreviousToken();
        ///setters da classe
        void setPreviousToken(std::string _previousToken, bool _operand, bool _unary);
        void setExpression(const std::string &exp);
        ///metodos que colocam os valor na pilha
        void StackReversePolish(const std::string &tk);
        void StackOperator(const std::string &tk);
        void PopReversePolish();
        void PopOperator();
        void PrintReversePolish();
        std::string TopReversePolish();
        std::string TopOperator();
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
        ///metodo usado para verificar a o peso dos operadores e então colocar na pilha
        bool reversePolish(Token* token);
        ///função que resolve a pilha que contem os valores na forma polonesa reversa
        double solving(std::string _op, bool unary);
};

#endif // EXPRESSION_H_INCLUDED
