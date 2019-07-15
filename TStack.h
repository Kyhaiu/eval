#ifndef TSTACK_H_INCLUDED
#define TSTACK_H_INCLUDED
#include "TList.h"

template <typename T> class TStack{

    private:
        TList<T>* Stack;
    public:
        TStack();
        void push(T _info);
        void pop();
        void top();
        bool isempty();
        ~TStack();
};

#endif // TSTACK_H_INCLUDED
