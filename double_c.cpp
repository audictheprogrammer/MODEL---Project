#include <iostream>

#include "double_c.hpp"



double_c add(double_c z1, double_c z2){
    double_c res = {z1.x + z2.x, z1.y + z2.y};
    return res;
}

double_c mul(double_c z1, double_c z2){
    double_c res = {z1.x * z2.x - z1.y * z2.y, z1.y*z2.x + z2.y*z1.x};
    return res;
}


double_c conj(double_c z) {
    double_c d = {z.x, -z.y};
    return d;
}

double Re(double_c z) {
    return z.x;
}

double Im(double_c z) {
    return z.y;
}

void print(double_c z) {
    printf("%lf + i%lf \n", z.x, z.y);
}





