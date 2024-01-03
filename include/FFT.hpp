#ifndef FFT_H
#define FFT_H

#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>

#include "ComplexD.hpp"

#define tolerance 1.0E-5

// Primitive roots.
ComplexD get_prim_root(size_t size_vect) {

    double cosD = (abs(cos(2*M_PI/size_vect))<tolerance) ? 0 : cos(2*M_PI/size_vect);
    double sinD = (abs(sin(2*M_PI/size_vect))<tolerance) ? 0 : sin(2*M_PI/size_vect);
    return ComplexD(cosD, sinD);
}

vector<ComplexD> get_roots(ComplexD root, size_t n) {
    vector<ComplexD> roots(n);
    roots[0] = ComplexD(1, 0);
    for (std::size_t i = 1; i < n; ++i) {
        roots[i] = roots[i-1] * root;
    }
    return roots;
}


tuple<vector<ComplexD>, vector<ComplexD>> split(const vector<ComplexD>& P) {
    vector<ComplexD> Po(P.size()/2);
    vector<ComplexD> Pe((P.size()+1)/2);
    
    for (std::size_t i = 0; i < P.size()/2; ++i) {
        Pe[i] = P[i*2];
        Po[i] = P[i*2 + 1];
    }

    if (P.size()%2 != 0) {
        Pe[P.size()/2] = P[P.size()-1];   
    }

    return tuple<vector<ComplexD>, vector<ComplexD>> (Pe, Po);
}


ComplexD eval(const vector<ComplexD> P, ComplexD root)
{
    ComplexD res = ComplexD();
    ComplexD omega = ComplexD(1, 0);
    for (std::size_t i = 0; i < P.size(); ++i) {
        res += P[i]*omega;
        omega *= root;
    }

    return res;
}


// FFT.
vector<ComplexD> FFT_rec(const vector<ComplexD>& P, const vector<ComplexD>& roots, int step) {
    if (P.size() == 1) {
        vector<ComplexD> res = {P[0]};
        return res;
    }

    // Split P into Po and Pe.
    tuple< vector<ComplexD>, vector<ComplexD> > P_split = split(P);
    vector<ComplexD> Pe = std::get<0>(P_split);
    vector<ComplexD> Po = std::get<1>(P_split);
    vector<ComplexD> res(P.size());

    // FFT sur Pe et Po
    vector<ComplexD> FFT_Pe = FFT_rec(Pe, roots, step*2);
    vector<ComplexD> FFT_Po = FFT_rec(Po, roots, step*2);

    // Evaluations
    for (std::size_t i = 0; i < P.size()/2; ++i) {
        ComplexD root = roots[i*step]; // Omega^i
        res[i] = FFT_Pe[i] + root * FFT_Po[i];
        res[P.size()/2 + i] = FFT_Pe[i] - root * FFT_Po[i];
    }
    
    return res;
}

size_t next_power_of_two(size_t n) {
    if ((n & (n - 1)) == 0) {
        return n;
    }

    size_t power = 1;
    while (power < n) {
        power <<= 1;
    }

    return power;
}



vector<ComplexD> FFT(vector<ComplexD>& P) {
    /* Computes the FFT of P
    Converts P into a polynomial of size power of two.
    */
    size_t size = next_power_of_two(P.size());
    P.resize(size);
    // Get the primitive root.
    ComplexD prim_root = get_prim_root(P.size());

    // Get the list of primitive to the power from 0 to n-1.
    vector<ComplexD> roots = get_roots(prim_root, P.size());
    vector<ComplexD> res = FFT_rec(P, roots, 1);
    return res;
}

vector<ComplexD> IFFT(const vector<ComplexD>& P) {
    /* IFFT of P. */

    // Get the primitive root.
    ComplexD prim_root = conj(get_prim_root(P.size()));

    // Get the list of primitive to the power from 0 to n-1.
    vector<ComplexD> roots = get_roots(prim_root, P.size());
    vector<ComplexD> res = FFT_rec(P, roots, 1);
    
    return (1. / (double)P.size()) * res;
}


#endif
