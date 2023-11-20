#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <tuple>

#include "ComplexD.hpp"

#define tolerance 0

// GCD 
int gcd (int a, int b)
{
    int c;

    while (a != 0) {
        c = a; a = b%a;  b = c;
    }
  
    return b;
}

// Primitive roots.
ComplexD get_prim_root(size_t size_vect) 
{

    double cosD = (abs(cos(2*M_PI/size_vect))<tolerance) ? 0 : cos(2*M_PI/size_vect);
    double sinD = (abs(sin(2*M_PI/size_vect))<tolerance) ? 0 : sin(2*M_PI/size_vect);
    return ComplexD(cosD, sinD);
}

vector<ComplexD> get_roots(ComplexD root, size_t n) {
    vector<ComplexD> roots(n);
    roots[0] = ComplexD(1, 0);

    for (int i = 1; i < n; i++) {
        roots[i] = roots[i-1] * root;
    }

    return roots;
}


tuple<vector<ComplexD>, vector<ComplexD>> split(const vector<ComplexD>& P) {
    vector<ComplexD> Po(P.size()/2);
    vector<ComplexD> Pe((P.size()+1)/2);
    
    for (size_t i = 0; i < P.size()/2; ++i) {
        Pe[i] = P[i*2];
        Po[i] = P[i*2 + 1];
    }

    if (P.size()%2 != 0) {
        Pe[P.size()/2] = P[P.size()-1];   
    }

    return tuple<vector<ComplexD>, vector<ComplexD>> (Pe, Po);
}


// FFT.

vector<ComplexD> FFT_rec(const vector<ComplexD>& P, const vector<ComplexD>& roots) {

    // Split P into Po and Pe.
    tuple<vector<ComplexD>, vector<ComplexD>> P_split = split(P);
    vector<ComplexD> Pe = std::get<0>(P_split);
    vector<ComplexD> Po = std::get<1>(P_split);


    // Evaluations.
    vector<ComplexD> res (P.size());

    // utile ?
    ComplexD O(); // Omega^i
    ComplexD T(); // Omega^{2i}

    for (int i = 0; i < P.size(); i+=2) {
        O = roots[i];
        T = roots[2*i];
        res[i] = eval(Pe, T) + O * eval(Po, T);

        O = roots[i+1];
        T = roots[2*(i+1)];
        res[i+1] = eval(Pe, T) + O * eval(Po, T);
    }

    vector<ComplexD> new_roots = 
}

vector<ComplexD> FFT(const vector<ComplexD>& P) {
    /* FFT of P. */

    // Get the primitive root.
    ComplexD prim_root = get_prim_root(P.size());

    // Get the list of primitive to the power from 0 to n-1.
    vector<ComplexD> roots = get_roots(prim_root, P.size());

    return FFT_rec(P, roots);
}





// IFFT.
