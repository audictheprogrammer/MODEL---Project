#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

using namespace std;

#define tolerance 1.0E-5

class ComplexD {

public:

    double x;
    double y;


    /* CONSTRUCTORS */
    ComplexD(const double& x0=0, const double& y0=0) :
    x(x0), y(y0) {}

    ComplexD(const ComplexD& z) :
    x(z.x), y(z.y) {}

    /* OPERATORS */
    ComplexD operator = (const ComplexD& z) {
        (*this).x = z.x;
        (*this).y = z.y;
        return *this;
    }

    bool operator != (const ComplexD& z) {
        bool b = ( (abs(x-z.x) > tolerance) || (abs(y-z.y) > tolerance ) ) ? 1 : 0;
        return b;
    }

    bool operator == (const ComplexD& z) {
        bool b = ( (abs(x-z.x) < tolerance) && (abs(y-z.y) < tolerance ) ) ? 1 : 0;
        return b;
    }

    friend ComplexD conj(ComplexD z) {
        /* Returns the conjugate of a complex number. */
        return ComplexD(z.x, -z.y);
    }

    ComplexD operator + (const ComplexD& z2) {
        ComplexD z = ComplexD();
        z.x = (abs(x + z2.x) < tolerance) ? 0 : x + z2.x;
        z.y = (abs(y + z2.y) < tolerance) ? 0 : y + z2.y;
        return z;
    }
    

    ComplexD operator - (const ComplexD& z2) {
        ComplexD z = ComplexD();
        z.x = (abs(x - z2.x) < tolerance) ? 0 : x - z2.x;
        z.y = (abs(y - z2.y) < tolerance) ? 0 : y - z2.y;
        return z;
    }

    ComplexD operator += (const ComplexD& z2) {
        this->x = (abs(x + z2.x) < tolerance) ? 0 : x + z2.x;
        this->y = (abs(y + z2.y) < tolerance) ? 0 : y + z2.y;
        return *this;
    }

    ComplexD operator -= (const ComplexD& z2) {
        this->x = (abs(x - z2.x) < tolerance) ? 0 : x - z2.x;
        this->y = (abs(y - z2.y) < tolerance) ? 0 : y - z2.y;
        return *this;
    }

    ComplexD operator + (const double& d) {
        ComplexD z = ComplexD();
        z.x = (abs(x + d) < tolerance) ? 0 : x + d;
        z.y = y;
        return z;
    }

    ComplexD operator - (const double& d) {
        ComplexD z = ComplexD();
        z.x = (abs(x - d) < tolerance) ? 0 : x - d;
        z.y = y;
        return z;
    }

    ComplexD operator += (const double& d) {
        this->x = (abs(x + d) < tolerance) ? 0 : x + d;
        return *this;
    }

    ComplexD operator -= (const double& d) {
        this->x = (abs(x - d) < tolerance) ? 0 : x - d;
        return *this;
    }

    ComplexD operator *(const ComplexD& z2) {
        ComplexD z1 = *this;
        double v1 = z1.x * z2.x - z1.y * z2.y;
        double v2 = z1.y * z2.x + z2.y * z1.x;
        return ComplexD((abs(v1) < tolerance) ? 0 : v1, 
                        (abs(v2) < tolerance) ? 0 : v2);
    }

    ComplexD operator *(const ComplexD& z2) const {
        ComplexD z1 = *this;
        double v1 = z1.x * z2.x - z1.y * z2.y;
        double v2 = z1.y * z2.x + z2.y * z1.x;
        return ComplexD((abs(v1) < tolerance) ? 0 : v1, 
                        (abs(v2) < tolerance) ? 0 : v2);
    }


    ComplexD operator *=(const ComplexD& z2) {
        double tmp = this->x;
        double v1 = this->x * z2.x - this->y * z2.y;
        double v2 = tmp * z2.y + this->y * z2.x;
        this->x = (abs(v1) < tolerance) ? 0 : v1;
        this->y = (abs(v2) < tolerance) ? 0 : v2;
        return *this;
    }
    
    ComplexD operator *(const double& d) {
        double v1 = d*this->x;
        double v2 = d*this->y;
        return ComplexD((abs(v1) < tolerance) ? 0 : v1, 
                        (abs(v2) < tolerance) ? 0 : v2);
        }
        
    ComplexD operator *=(const double& d) {
        double v1 = this->x*d;
        double v2 = this->y*d;
        this->x = (abs(v1) < tolerance) ? 0 : v1;
        this->y = (abs(v2) < tolerance) ? 0 : v2;
        return *this;
    }

    ComplexD operator /(const ComplexD& z2) {
        ComplexD res = ComplexD();
        ComplexD z2barre = conj(z2);
        double d = (z2*z2barre).x;
        double v1 = (this->x*z2barre.x - this->y*z2barre.y)/d;
        double v2 = (this->x*z2barre.y + this->y*z2barre.x)/d;
        res.x = (abs(v1) < tolerance) ? 0 : v1;
        res.y = (abs(v2) < tolerance) ? 0 : v2;
        return res;
    }

    ComplexD operator /=(const ComplexD& z2) {
        ComplexD z2barre = conj(z2);
        double d = (z2*z2barre).x;
        double v1 = (this->x*z2barre.x - this->y*z2barre.y)/d;
        double v2 = (this->x*z2barre.y + this->y*z2barre.x)/d;
        this->x = (abs(v1) < tolerance) ? 0 : v1;
        this->y = (abs(v2) < tolerance) ? 0 : v2;
        return *this;
    }

    ComplexD operator /(const double& d) {
        double v1 = this->x/d;
        double v2 = this->y/d;
        return ComplexD((abs(v1) < tolerance) ? 0 : v1, 
                        (abs(v2) < tolerance) ? 0 : v2);
    }
        
    ComplexD operator /=(const double& d) {
        double v1 = this->x/d;
        double v2 = this->y/d;
        this->x = (abs(v1) < tolerance) ? 0 : v1;
        this->y = (abs(v2) < tolerance) ? 0 : v2;
        return *this;
    }

    ComplexD operator ^(const double& d) {
        ComplexD res = ComplexD(1,0);
        for (int i = 0; i < d; ++i) {
            res *= (*this);
        }
        *this = res;
        return *this;
    }
};

ostream& operator <<(ostream& o, const ComplexD& z) {
    o << z.x << " + i* " << z.y;
    return o;
}

std::vector<ComplexD> operator * (double d, std::vector<ComplexD>& V) {    
    for (std::size_t i = 0; i < V.size(); ++i) {
        V[i] = V[i] * d;
    }
    
    return V;
}

#endif 