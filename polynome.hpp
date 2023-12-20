#ifndef POLYNOME_HPP
#define POLYNOME_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <cmath>

#include "ComplexD.hpp"
#include "FFT.hpp"


void init_poly(std::vector<ComplexD>& P, size_t max_rand) {
    /* Fill randomly the coefficients between 0 and max_rand-1. */
    for (std::size_t i = 0; i < P.size(); i++){
        P[i] = std::rand() % max_rand;
    }
}


std::size_t verif_poly(std::vector<ComplexD>& naif, std::vector<ComplexD>& FFT) {
    assert (naif.size() == FFT.size());
    for (std::size_t i = 0; i < naif.size(); ++i) {
        if (naif[i] != FFT[i]) {
            cout << "naif  : " << naif[i] << " normal : "  << FFT[i] << "\n";
            return 0;
        }
    }
    return 1;
}


std::vector<ComplexD> naive_mult(const std::vector<ComplexD>& P, const std::vector<ComplexD>& Q) {
    std::vector<ComplexD> res(P.size() + Q.size() - 1, 0.);

    for (std::size_t i = 0; i < P.size(); ++i) {
        
        for (std::size_t j = 0; j < Q.size(); ++j) {
            res[i+j] += P[i] * Q[j];
        }
    }

    return res;
}



std::vector<ComplexD> FFT_mult_init(const std::vector<ComplexD>& P, const std::vector<ComplexD>& Q) {
    std::size_t size = 2 * std::max(P.size(), Q.size());
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


    for (std::size_t i = 0; i < size; i++) {
        res[i] = FFT1[i] * FFT2[i];
    }

    res = IFFT(res);

    res.resize(P.size() + Q.size() - 1);
    return res;
}

std::vector<ComplexD> FFT_mult(const std::vector<ComplexD>& P, const std::vector<ComplexD>& Q) {
    std::size_t sizeP = next_power_of_two(P.size());
    std::size_t sizeQ = next_power_of_two(Q.size());
    std::size_t size = 2 * std::max(sizeP, sizeQ);

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


    for (std::size_t i = 0; i < size; i++) {
        res[i] = FFT1[i] * FFT2[i];
    }

    res = IFFT(res);

    res.resize(P.size() + Q.size() - 1);
    return res;
}



#endif