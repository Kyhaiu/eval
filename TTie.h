#ifndef TTIE_H_INCLUDED
#define TTIE_H_INCLUDED

template <typename T> class TTie{

    private:
        ///atributos da classe
        T info;
        TTie<T>* next;
    public:
        ///construtores da classe
        TTie();
        TTie(T &_info, TTie<T>* _next);
        ///getters da classe
        T getInfo();
        TTie<T>* getNext();
        ///setters da classe
        void setInfo(T &newInfo);
        void setNext(TTie<T>* next);
};

#endif // TTIE_H_INCLUDED
