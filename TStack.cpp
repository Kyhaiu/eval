#include "TStack.h"
#include "TList.cpp"
#include <iostream>

template <typename T> TStack<T>::TStack(){
    Stack = new TList<T>();
}

template <typename T> void TStack<T>::push(T _info){
    Stack->setBegin(_info);
}

template <typename T> void TStack<T>::pop(){
    Stack->removeBegin();
}

template <typename T> T TStack<T>::top(){
    TTie<T> *aux = Stack->getHead();
    return aux->getInfo();
}

template <typename T> TStack<T>::~TStack(){
    delete Stack;
}

template <typename T> bool TStack<T>::isEmpty(){
    return (Stack->getSize()==0);
}

template <typename T> void TStack<T>::printStack(){
    Stack->printList();
}
