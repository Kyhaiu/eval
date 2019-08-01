#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED
#include<vector>
#include<tuple>
#include <iostream>

class Token{
    private:
        const std::vector<std::tuple<std::string, int, bool, bool>> operations =
            {{"+", 1, true, false},
             {"-", 1, true, false},
             {"*", 2, true, false},
             {"/", 2, true, false},
             {"^", 3, true, false},
             {"sqrt", 4, true, true},
             {"abs", 4, true, true},
             {"log", 4, true, true},
             {"sen", 4, true, true},
             {"cos", 4, true, true},
             {"tan", 4, true, true}};
        const std::string separators = "+-*/^()";
        std::string expression;
        std::vector<std::tuple<std::string, int, bool, bool>> tkns;
    public:
        Token();
        Token(std::string &exp);
        ///getters da classe
        std::string getExpression();
        std::tuple<std::string, int, bool, bool> getToken(int i);
        std::vector<std::tuple<std::string, int, bool, bool>>& getMapToken();
        int getPriority(std::string &tk);
        ///setters da classe
        void setToken(std::tuple<std::string, int, bool, bool> tkn);
        ///metodos da classe
        std::string findNextToken(std::string exp, int &i);
        bool isUnary(std::string tk);
        bool isOperator(std::string tkn);
        bool isVariable(std::string tk);
        bool isFunction(std::string exp, int j);
        void checkTokens();
        void solveUnarySub(int i);
};

#endif // TOKEN_H_INCLUDED
