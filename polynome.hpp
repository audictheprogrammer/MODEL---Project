#ifndef POLYNOME_HPP
#define POLYNOME_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include "ComplexD.hpp"
#include "FFT.hpp"
#include <cmath>

std::vector<ComplexD> naive_mult(const std::vector<ComplexD>& P, const std::vector<ComplexD>& Q) {
    std::vector<ComplexD> res(P.size() + Q.size() - 1, 0.);

    for (std::size_t i = 0; i < P.size(); ++i) {
        
        for (std::size_t j = 0; j < Q.size(); ++j) {
            res[i+j] += P[i] * Q[j];
        }
    }

    return res;
}



std::vector<ComplexD> FFT_mult(const std::vector<ComplexD>& P, const std::vector<ComplexD>& Q) {
    std::vector<ComplexD> res(P.size() + Q.size() - 1, 0.);

    // std::vector<ComplexD> P2(P.size() + Q.size() - 1, 0.);
    // std::vector<ComplexD> Q2(P.size() + Q.size() - 1, 0.);
    std::vector<ComplexD> P2(P.size() + Q.size() - 1, ComplexD());
    std::vector<ComplexD> Q2(P.size() + Q.size() - 1, ComplexD());

    std::size_t size = (P.size() < Q.size()) ? Q.size() : P.size();
    
    for (std::size_t i = 0; i < P.size() + Q.size() - 1; ++i) {
    // for (std::size_t i = 0; i < size; ++i) {
        if (i < P.size()) {
            P2[i] = P[i];
        }
        
        if (i < Q.size()) {
            Q2[i] = Q[i];
        }
    }

    std::cout << "P2 = " << endl;
    for (int i = 0; i < P2.size(); ++i) {
        cout << P2[i] << "\t";
    }
    std::cout << std::endl;

    std::cout << "Q2 = " << endl;
    for (int i = 0; i < Q2.size(); ++i) {
        cout << Q2[i] << "\t";
    }
    std::cout << std::endl;

    std::vector<ComplexD> FFT1 = FFT(P2);
    std::vector<ComplexD> FFT2 = FFT(Q2);

    // std::vector<ComplexD> FFT1 = {ComplexD(3, 0), 
    //                               ComplexD(0, 1.72)};
    // std::vector<ComplexD> FFT2 = {ComplexD(7, 0), 
    //                               ComplexD(1, 3.44)};




    std::cout << "FFT1 = " << std::endl;
    for (int i = 0; i < FFT1.size(); ++i) {
        cout << FFT1[i] << "\t";
    }
    std::cout << std::endl;

    std::cout << "FFT2 =" << std::endl;
    for (int i = 0; i < FFT2.size(); ++i) {
        cout <<FFT2[i] << "\t";
    }
    std::cout << std::endl;

    
    for (int i = 0; i < P.size() + Q.size() - 1; i++) {
        res[i] = FFT1[i] * FFT2[i];
    }

    std::cout << endl << "PQ =" << std::endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << "\t";
    }
    std::cout << std::endl;

    res = IFFT(res);

    std::cout << "IFFT(res) =" << std::endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << "\t";
    }
    std::cout << std::endl;
    return res;
}



#endif