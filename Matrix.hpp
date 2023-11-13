#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "ComplexD.hpp"
#include <vector>


using namespace std;

class Matrix{
    public:
    int nr; // number of rows
    int nc; // number of columns
    vector<ComplexD> data; // Matrix row-wise
    
    Matrix(const int& nr, const int& nc){
        /* Constructor. */
        this->nr = nr;
        this->nc = nc;
        for (int i = 0; i < nr*nc; i++){
            this->data[i] = ComplexD(0, 0);
        }
    }

    // vector<ComplexD> operator *(vector<ComplexD> V){
    //     /* Product between a matrix and a vector. */
    // }


};



#endif