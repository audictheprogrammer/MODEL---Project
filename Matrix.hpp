#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "ComplexD.hpp"
#include <vector>
#include <cassert>

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

    vector<ComplexD> operator *(vector<ComplexD> V){
        /* Product between a matrix and a vector. */
        assert(V.size() == this->nc);
        vector<ComplexD> res(this->nr);
        for (int i = 0; i < this->nr; i++){
            for (int j = 0; j < this->nr; j++){
                res[i] += this->data[i*this->nc + j] * V[j];
            }
        }

        return res;
    }

    vector<ComplexD> operator *(ComplexD z){
        /* Product between a matrix and a complex. */
        for (int i = 0; i < this->nr; i++){
            for (int j = 0; j < this->nr; j++){
                this->data[i*this->nc + j] *= z;
            }
        }
    
    
    }



};



#endif