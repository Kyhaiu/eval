#ifndef TLIST_H_INCLUDED
#define TLIST_H_INCLUDED
#include "TTie.h"

template <typename T> class TList{

    private:
        ///Atributos da classe
        TList<T>* List;
        TTie<T>* head;
        TTie<T>* tail;
        int Size;
    public:
        ///contrutores da classe
        TList();
        TList(TTie<T>* _head, TTie<T>* _tail);
        ///getters da classe
        TTie<T>* getHead();
        TTie<T>* getTail();
        int getSize();
        ///setters da classe
        void setHead(TTie<T>* newHead);
        void setTail(TTie<T>* newTail);
        void updateSize(int newSize);
        ///metodos da classe
        ///insere no come�o da lista
        void setBegin(T &_info);
        ///remove do come�o da lista
        void removeBegin();
        ///imprime os valores da lista
        void printList();
};

#endif // TLIST_H_INCLUDED
