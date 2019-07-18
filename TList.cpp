#include "TList.h"
#include "TTie.cpp"
#include <iostream>

///classe template da lista encadeada, usada somente para criar a pilha

template <typename T> TList<T>::TList(){
    setHead(nullptr);
    setTail(nullptr);
    updateSize(0);
}

template <typename T> TList<T>::TList(TTie<T>* _head, TTie<T>* _tail){
    setHead(_head);
    setTail(_tail);
    updateSize(0);
}

template <typename T> TTie<T>* TList<T>::getHead(){
    return head;
}

template <typename T> TTie<T>* TList<T>::getTail(){
    return tail;
}

template <typename T> int TList<T>::getSize(){
    return Size;
}

template <typename T> void TList<T>::setHead(TTie<T>* newHead){
    head = newHead;
}

template <typename T> void TList<T>::setTail(TTie<T>* newTail){
    tail = newTail;
}

template <typename T> void TList<T>::updateSize(int newSize){
    if(newSize == 0){
        Size = 0;
    }
    Size =  Size + newSize;
}

template <typename T> void TList<T>::setBegin(T &_info){
    if(getSize() == 0){
        TTie<T>* tie = new TTie<T>(_info, nullptr);
        setHead(tie);
        setTail(tie);
        updateSize(1);
    } else{
        TTie<T>* newTie = new TTie<T>(_info, getHead());
        setHead(newTie);
        updateSize(1);
    }
}

template <typename T> void TList<T>::removeBegin(){
    if(getSize() == 0){
        std::cout << "Erro!" << std::endl;
    } else if(getSize() == 1){
        delete getHead();
        updateSize(-1);
    } else{
        TTie<T>* oldHead = getHead();
        TTie<T>* newHead = oldHead->getNext();
        setHead(newHead);
        updateSize(-1);
        delete oldHead;
    }
}

template <typename T> void TList<T>::printList(){
    if(getSize() == 0){
        std::cout << "Lista Vazia!!" << std::endl;
    } else {
        TTie<T> *p = head;
        while(p != nullptr){
            std::cout << p->getInfo() << " ";
            p = p->getNext();
        }
    }
}
