#ifndef FFT_H
#define FFT_H

#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>

#include "ComplexD.hpp"

#define tolerance 1.0E-15

// // GCD 
// int gcd (int a, int b) {
//     int c;

//     while (a != 0) {
//         c = a; a = b%a;  b = c;
//     }
  
//     return b;
// }

// Primitive roots.
ComplexD get_prim_root(size_t size_vect) {

    double cosD = (abs(cos(2*M_PI/size_vect))<tolerance) ? 0 : cos(2*M_PI/size_vect);
    double sinD = (abs(sin(2*M_PI/size_vect))<tolerance) ? 0 : sin(2*M_PI/size_vect);
    return ComplexD(cosD, sinD);
}

vector<ComplexD> get_roots(ComplexD root, size_t n) {
    vector<ComplexD> roots(n);
    roots[0] = ComplexD(1, 0);
    std::cout << "roots [" << roots[0];
    for (int i = 1; i < n; ++i) {
        roots[i] = roots[i-1] * root;
        std::cout << ", " << roots[i];
    }
    std::cout << "]" << endl;
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


ComplexD eval(const vector<ComplexD> P, ComplexD root)
{
    ComplexD res = ComplexD();
    ComplexD omega = ComplexD(1, 0);
    for (int i = 0; i < P.size(); ++i) {
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
    // A REVOIR

    // Split P into Po and Pe.
    tuple< vector<ComplexD>, vector<ComplexD> > P_split = split(P);
    vector<ComplexD> Pe = std::get<0>(P_split);
    vector<ComplexD> Po = std::get<1>(P_split);
    vector<ComplexD> res(P.size());


    // FFT sur Pe et Po
    FFT_rec(Pe, roots, step*2);
    FFT_rec(Po, roots, step*2);

    // Evaluations.
    for (int i = 0; i < P.size()/2; ++i) {
        ComplexD root = roots[i*step]; // Omega^i
        res[i] = eval(Pe, root*root) + root * eval(Po, root*root);
        res[P.size()/2 + i] = eval(Pe, root*root) - root * eval(Po, root*root);
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


vector<ComplexD> FFT(const vector<ComplexD>& P) {
    /* FFT of P. */
    std::cout << "P = \n";
 
    // next_power_of_two
    vector<ComplexD> copyP(next_power_of_two(P.size()), ComplexD());
    for (std::size_t i = 0; i < P.size(); ++i) {
        copyP[i] = P[i];
        std::cout << copyP[i] << " \n";
    }
    for (std::size_t i = P.size(); i < copyP.size(); ++i) {
        std::cout << copyP[i] << " \n";
    }
    std::cout << endl;

    

    // Get the primitive root.
    ComplexD prim_root = get_prim_root(copyP.size());
    cout << "PRIM ROOT:" << prim_root << endl;

    // Get the list of primitive to the power from 0 to n-1.
    vector<ComplexD> roots = get_roots(prim_root, copyP.size());

    return FFT_rec(copyP, roots, 1);
}


// void FFT_rec(u64 n, const double complex * X, double complex *Y, u64 stride)
// {
//         if (n == 1) {
//                 Y[0] = X[0];
//                 return;
//         }
//         double complex omega_n = cexp(-2*I*M_PI / n);   /* n-th root of unity*/
//         double complex omega = 1;                          /* twiddle factor */
//         FFT_rec(n/2, X, Y, 2*stride);
//         FFT_rec(n/2, X + stride, Y + n/2, 2*stride);
//         for (u64 i = 0; i < n/2; i++) {
//                 double complex p = Y[i];
//                 double complex q = Y[i + n/2] * omega;
//                 Y[i] = p + q;
//                 Y[i + n/2] = p - q;
//                 omega *= omega_n;
//         }
// }

// void FFT(u64 n, const double complex * X, double complex *Y)
// {
//         /* sanity check */
//         if ((n & (n - 1)) != 0)
//                 errx(1, "size is not a power of two (this code does not handle other cases)");
//         FFT_rec(n, X, Y, 1);  
//         std::cout << "ICIIIIIIII\n";                      /* stride == 1 initially */
// }

// /* Computes the inverse Fourier transform, but destroys the input */
// void iFFT(u64 n, double complex * X, double complex *Y)
// {
//         for (u64 i = 0; i < n; i++)
//                 X[i] = conj(X[i]);
//         FFT(n, X, Y);
//         for (u64 i = 0; i < n; i++)
//                 Y[i] = conj(Y[i]) / n;
// }



vector<ComplexD> IFFT(const vector<ComplexD>& P) {
    /* IFFT of P. */

    // Get the primitive root.
    ComplexD prim_root = conj(get_prim_root(P.size()));
    cout << "PRIM ROOT:" << prim_root << endl;

    // Get the list of primitive to the power from 0 to n-1.
    vector<ComplexD> roots = get_roots(prim_root, P.size());
    vector<ComplexD> res = FFT_rec(P, roots, 1);
    
    return (1. / (double)P.size()) * res;
}



// // ComplexD *eval(ComplexD *coeffs, int n, Uint *tmp_coeffs, Uint *roots, Uint pas_rac) {
// ComplexD *eval(ComplexD *coeffs, int n, ComplexD *roots, int pas_rac) {
//     if (n == 1)
//         return &coeffs[0];

//     int k = n/2;
    
    
//     for (int i = 0; i < k; i++) {
//         tmp_coeffs[i] = coeffs[i] + coeffs[i+k];
//         ComplexD tmp(coeffs[i] - coeffs[i+k]);
//         tmp_coeffs[i+k] = tmp * roots[i*pas_rac];
//     }

//     Uint *r0 = eval(tmp_coeffs, k, coeffs, roots, pas_rac*2);
//     Uint *r1 = eval(&tmp_coeffs[k], k, &coeffs[k], roots, pas_rac*2);
    
//     for (int i = 0; i < k; i++) {
//         coeffs[2*i] = r0[i];
//         coeffs[2*i+1] = r1[i];
//     }
//     return coeffs;

//     // if (n == 1) return &coeffs[0];

//     // Uint k = n/2;
    
//     // Uint tmp;
//     // for (int i = 0; i < k; i++) {
//     //     tmp_coeffs[i] = mod_add(coeffs[i], coeffs[i+k]);
//     //     tmp = mod_sub(coeffs[i], coeffs[i+k]);
//     //     tmp_coeffs[i+k] = mod_mult(tmp, roots[i*pas_rac]);
//     // }
//     // Uint *r0 = eval(tmp_coeffs, k, coeffs, roots, pas_rac*2);
//     // Uint *r1 = eval(&tmp_coeffs[k], k, &coeffs[k], roots, pas_rac*2);
//     // for (int i = 0; i < k; i++) {
//     //     coeffs[2*i] = r0[i];
//     //     coeffs[2*i+1] = r1[i];
//     // }
//     // return coeffs;
// }





// IFFT.





#endif
