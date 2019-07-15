#include"TTie.h"

template <typename T> TTie<T>::TTie(){
    setNext(nullptr);
}

template <typename T> TTie<T>::TTie(T &_info, TTie<T>* _next){
    setInfo(_info);
    setNext(_next);
}

template <typename T> T TTie<T>::getInfo(){
    return info;
}

template <typename T> TTie<T>* TTie<T>::getNext(){
    return next;
}

template <typename T> void TTie<T>::setInfo(T &newInfo){
    info = newInfo;
}

template <typename T> void TTie<T>::setNext(TTie<T>* _next){
    next = _next;
}
