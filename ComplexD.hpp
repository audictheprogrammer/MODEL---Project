#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;

class ComplexD{

public:

    double x;
    double y;


    /* CONSTRUCTORS */
    ComplexD(const double& x0=0, const double& y0=0) :
    x(x0), y(y0) {}

    ComplexD(const ComplexD& z) :
    x(z.x), y(z.y) {}

    /* OPERATORS */
    ComplexD operator =(const ComplexD& z) {
        (*this).x = z.x;
        (*this).y = z.y;
    }

    ComplexD operator +(const ComplexD& z2) {
        ComplexD z1 = *this;
        return ComplexD(z1.x + z2.x, z1.y + z2.y);
    }
    
    ComplexD operator +=(const ComplexD& z2) {
        this->x += z2.x;
        this->y += z2.y;
        return *this;
    }

    ComplexD operator +(const double& d) {
        ComplexD z = *this;
        return ComplexD(z.x + d, z.y);
    }

    ComplexD operator +=(const double& d) {
        this->x += d;
        return *this;
    }

    ComplexD operator *(const ComplexD& z2) {
        ComplexD z1 = *this;
        return ComplexD(z1.x * z2.x - z1.y * z2.y, z1.y*z2.x + z2.y*z1.x);
    }

    ComplexD operator *=(const ComplexD& z2) {
        this->x = this->x * z2.x - this->y * z2.y;
        this->y = this->x * z2.y + this->y * z2.x;
        return *this;        
    }
    
    ComplexD operator *(const double& d) {
        return ComplexD(d*this->x, d*this->y);
    }
        
    ComplexD operator *=(const double& d) {
        this->x *= d;
        this->y *= d;
        return *this;
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