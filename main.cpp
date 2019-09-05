#include <iostream>
#include "Expression.h"

int main(){
    std::string e;
    while(1 > 0){
        system("cls");
        std::cout << "Avaliador de expressoes aritmeticas - by Igor E. and Marcos A." << std::endl;
        std::cout << "Para saber quais operacoes sao suportadas digite 'help', e para sair digite 'quit'" << std::endl;
        std::cout << "Caso queira rodar os casos de teste propostos no trabalho, digite 'tioadair'" << std::endl;
        std::cout << "Aviso ! O avaliador de expresoes so suporta somente variaveis com letras maiusculas" << std::endl;
        std::cout << "Aviso 2 !! Caso deseje utilizar alguma funcao, colocar os parenteses corretamente Ex.: 'sen(60)'" << std::endl;
        std::cout << "Informe a expressao a ser avaliada: " << std::endl;
        std::cin >> e;
        Expression* exp = new Expression(e);
        if(e == "help"){
            system("cls");
            std::cout << "Tudo que estiver dentro de '' eh operacao/funcao/constante" << std::endl;
            std::cout << "Adicao '+'"<< std::endl;
            std::cout << "Subtracao '-'" << std::endl;
            std::cout << "Multiplicacao '*'" << std::endl;
            std::cout << "Divisao '/'" << std::endl;
            std::cout << "Potenciacao '^'" << std::endl;
            std::cout << "Logaritimo na base 10 'log()'" << std::endl;
            std::cout << "Modulo 'abs()'" << std::endl;
            std::cout << "Seno 'sen()'" << std::endl;
            std::cout << "Cosseno 'cos()'" << std::endl;
            std::cout << "Tangente 'tan()'" << std::endl;
            std::cout << "A Constante 'PI' esta definida como sendo:  3,1415926535898" << std::endl;
            system("pause");
        }else if(e == "quit"){
            break;
        } else if(e == "tioadair"){
            system("cls");
            e = "A + B * C";
            std::cout << "Expressao : " << e << std::endl;
            exp->eval(e);
            e = "-A * (B + C/D)";
            std::cout << "Expressao : " << e << std::endl;
            exp->eval(e);
            e = "-A*(-B+C)";
            std::cout << "Expressao : " << e << std::endl;
            exp->eval(e);
            e = "A*(-B+C)";
            std::cout << "Expressao : " << e << std::endl;
            exp->eval(e);
            e = "A*-(C-log(B))";
            std::cout << "Expressao : " << e << std::endl;
            exp->eval(e);
            e = "A + 4 * log(3/abs(1 - X))+ sen(-B/4+PI)";
            std::cout << "Expressao : " << e << std::endl;
            exp->eval(e);
            e = "(3*sen(PI*X))^2-(2*cos(PI*Y))^2";
            std::cout << "Expressao : " << e << std::endl;
            exp->eval(e);
        } else{
            exp->eval(e);
        }
    }
}
