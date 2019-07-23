#ifndef TSTACK_H_INCLUDED
#define TSTACK_H_INCLUDED
#include "TList.h"

template <typename T> class TStack{

    private:
        TList<T>* Stack;
    public:
        ///construtor da classe
        TStack();
        ///coloca a informação na pilha
        void push(T _info);
        ///remove o elemento do topo da pilha
        void pop();
        ///consulta o elemento do topo da pilha
        T top();
        ///verifica se a pilha está vazia
        bool isEmpty();
        ///printa a pilha(debug)
        void printStack();
        ///implementar
        ~TStack();
};

#endif // TSTACK_H_INCLUDED
