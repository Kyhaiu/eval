#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED
#include<vector>
#include<tuple>
#include<string>

class Token{
    private:
        ///constante que determina os operadores, preioridade de cada operador e se ele é unario
        const std::vector<std::tuple<std::string, int, bool>> operators =
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
             {"tan",  4, true}};
        ///variavel que armazena o Token recebido
        std::string receivedToken;
        ///variavel que armaena o tipo do token(1° parametro indica se é um operador ou operando, segundo parametro se é unário)
        std::tuple<bool, bool> typeToken;
        ///caso o token recebido seja um operador, essa variavel armazena a sua prioridade
        int priority;
        ///caso o token recebido seja um numero, essa variavel armazena seu valor
        double number;
        ///verifica se o operador é unario, consultando na constante "operators"
        bool isUnary(const std::string &_token);
        ///verifica se o operador é um operador aritimético(não fiz pra função ainda), consultando na constante "operators"
        bool isOperator(const std::string &_token);
        ///caso o token for um numero, converte a string para double
        double asNumber(const std::string &_token);
    public:
        ///contrutores da classe
        Token();
        Token(const std::string &_token);
        ///getters da classe
        std::string getRecivedToken();
        std::tuple<bool, bool> getTypeToken();
        int getPriority(std::string _token = "");
        double getNumber();
        ///setters da classe
        void setRecivedToken(const std::string &_token);
        void setTypeToken(bool typeOp, bool unary);
        void setPriority(int _priority);
        void setNumber(const double &_number);
        ///metodos da classe
        ///checa o token recebido e diz se ele é um numero
        void checkToken();
        bool checkPriorityOperator(Token* token, std::string tokenInStack);
};

#endif // TOKEN_H_INCLUDED
