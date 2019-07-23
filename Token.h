#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED
#include<vector>
#include<tuple>

class Token{
    private:
        const std::vector<std::tuple<std::string, int, bool, bool>> operations =
            {{"+", 1, false, false},
             {"-", 1, false, false},
             {"*", 2, false, false},
             {"/", 3, false, false},
             {"^", 4, false, false},
             {"sqrt", 4, true, true},
             {"abs", 4, true, true},
             {"log", 4, true, true},
             {"sin", 4, true, true},
             {"cos", 4, true, true},
             {"tan", 4, true, true}};
        const std::string separators = "+-*/^()";
        std::string expression;
        std::vector<std::tuple<std::string, int, bool, bool, int>> tkns;
    public:
        Token();
        Token(std::string &exp);
        ///getters da classe
        std::string getExpression();
        std::tuple<std::string, int, bool, bool, int> getToken(int i);
        std::vector<std::tuple<std::string, int, bool, bool, int>>& getMapToken();
        int getPriority(std::string &tk);
        ///setters da classe
        void setToken(std::tuple<std::string, int, bool, bool, int> tkn, int i);
        ///metodos da classe
        std::string findNextToken(std::string exp, int &i);
        bool isUnary(std::string tk);
        bool isOperator(std::string tkn);
        bool isVariable(std::string tk);
        bool isFunction(std::string exp, int j);
        void checkTokens();
};

#endif // TOKEN_H_INCLUDED
