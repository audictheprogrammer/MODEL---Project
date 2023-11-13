#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
using namespace std;

class ComplexD{
    public:
    double x;
    double y;

    ComplexD(const double& x, const double& y){
        this->x = x;
        this->y = y;
    }

    ComplexD operator +(ComplexD z2){
        ComplexD z1 = *this;
        return ComplexD(z1.x + z2.x, z2.y + z2.y);
    }

    ComplexD operator *(ComplexD z2){
        ComplexD z1 = *this;
        return ComplexD(z1.x * z2.x - z1.y * z2.y, z1.y*z2.x + z2.y*z1.x);
    }

};

ostream& operator <<(ostream& o, const ComplexD& z){
    o << z.x << " + i* " << z.y << endl;
    return o;
}

ComplexD conj(ComplexD z){
    /* Return the conjugate of a complex number. */
    return ComplexD(z.x, -z.y);
}



#endif 