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
    size_t size = 2 * std::max(P.size(), Q.size());
    std::vector<ComplexD> P2(size, ComplexD());
    std::vector<ComplexD> Q2(size, ComplexD());
    std::vector<ComplexD> res(size, ComplexD());

    for (std::size_t i = 0; i < size; ++i) {
        if (i < P.size()) {
            P2[i] = P[i];
        }
        
        if (i < Q.size()) {
            Q2[i] = Q[i];
        }
    }

    std::vector<ComplexD> FFT1 = FFT(P2);
    std::vector<ComplexD> FFT2 = FFT(Q2);

    
    for (int i = 0; i < size; i++) {
        res[i] = FFT1[i] * FFT2[i];
    }

    res = IFFT(res);

    res.resize(P.size() + Q.size() - 1);
    return res;
}



#endif