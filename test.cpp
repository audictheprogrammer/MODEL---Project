#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <cmath>

#include "ComplexD.hpp"
using namespace std;



int main(){

    ComplexD z(0, 1);
    ComplexD z2(z);
    ComplexD z3 = z2;

    cout << "z = "      << z        << endl;
    cout << "z2 = "     << z2       << endl;
    cout << "z3 = "     << z3       << endl;

    cout << "z+z2 = "   << z+z2     << endl;
    cout << "z+=z2 = "  << (z+=z2)  << endl;
    cout << "z+4 = "    << z+4      << endl;
    cout << "z+=4 = "   << (z+=4)   << endl;

    cout << "z-z2 = "   << z-z2     << endl;
    cout << "z-=z2 = "  << (z-=z2)  << endl;
    cout << "z-4 = "    << z-4      << endl;
    cout << "z-=4 = "   << (z-=4)   << endl;

    cout << "z*z2 = "   << z*z2     << endl;
    cout << "z*=z2 = "  << (z*=z2)  << endl;
    cout << "z*4 = "    << z*4      << endl;
    cout << "z*=4 = "   << (z*=4)   << endl;
    
    cout << "z/4 = "    << z/4      << endl;
    cout << "z/=4 = "   << (z/=4)   << endl;

    cout << "z^2 = "    << (z^2)    << endl;

    cout << "conj(z)= " << conj(z)  << endl;
    

    return 0;
}