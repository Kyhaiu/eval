#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED
#include<tuple>
#include<vector>
#include<string>

class Token{
    private:
        const std::vector<std::tuple<std::string, int, bool>> tokens =
            {{"+",   1, false},
             {"-",   1, false},
             {"*",   2, false},
             {"/",   2, false},
             {"^",   3, false},
             {"sqrt", 4, true},
             {"abs",  4, true},
             {"log",  4, true},
             {"sin",  4, true},
             {"cos",  4, true},
             {"tan",  4, true},
             {"NaOP", 0, true}};///Not a Operation
        std::tuple<std::string, int, bool> typeOp;
        bool operand;
    public:
        Token(const std::string &_char);
        bool isOperator(const std::string &_char);
        bool isNumber(const std::string &_char);
        double asNumber(const std::string &_char);
        std::tuple<std::string, int, bool> asOperator(const std::string &_char);
};

#endif // TOKEN_H_INCLUDED
