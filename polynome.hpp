#ifndef POLYNOME_HPP
#define POLYNOME_HPP

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <tuple>
#include "ComplexD.hpp"
#include "FFT.hpp"

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

    std::vector<ComplexD> P2(P.size() + Q.size() - 1, 0.);
    std::vector<ComplexD> Q2(P.size() + Q.size() - 1, 0.);

    std::size_t size = (P.size() < Q.size()) ? Q.size() : P.size();
    
    for (std::size_t i = 0; i < size; ++i) {
        if (i <= P.size()) {
            P2[i] = P[i];
        }
        
        if (i <= Q.size()) {
            Q2[i] = Q[i];
        }
    }

    std::vector<ComplexD> FFT1 = FFT(P2);
    std::vector<ComplexD> FFT2 = FFT(Q2);

    for (int i = 0; i < P.size() + Q.size() - 1; i++) {
        res[i] = FFT1[i] * FFT2[i];
    }

    res = IFFT(res);

    return res;
}



#endif