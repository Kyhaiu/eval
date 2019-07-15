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
        TList(TTie<T>* _head, TTie<T>* _tail, int &_size);
        ///getters da classe
        TTie<T>* getHead();
        TTie<T>* getTail();
        int getSize();
        ///setters da classe
        void setHead(TTie<T>* newHead);
        void setTail(TTie<T>* newTail);
        void updateSize(int newSize);
        ///metodos da classe
        void setBegin(T &_info);
        void removeBegin();
        void printList();
};

#endif // TLIST_H_INCLUDED
