#ifndef COMPLEX_H
#define COMPLEX_H

 typedef struct double_c {
     double x;
     double y;
 } double_c;


double_c add(double_c z1, double_c z2);

double_c mul(double_c z1, double_c z2);

double_c conj(double_c z);

void print(double_c z);




#endif 