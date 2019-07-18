#include "Operations.h"
#include <cmath>

///classe contem as funções que o eval deve resolver

double Operations::add(double a, double b){
    return a + b;
}

double Operations::sub(double a, double b){
    return a - b;
}

double Operations::mul(double a, double b){
    return a * b;
}

double Operations::div(double a, double b){
    return a / b;
}

double Operations::pow(double a, double b){
    return std::pow(a, b);
}

double Operations::abs(double a){
    return std::abs(a);
}

double Operations::log(double a){
    return std::log10(a);
}

double Operations::sin(double a){
    return std::sin (a);
}

double Operations::cos(double a){
    return std::cos(a);
}

double Operations::tan(double a){
    return std::tan(a);
}

