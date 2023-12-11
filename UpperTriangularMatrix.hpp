#ifndef UPPER_TRIANGULAR_MATRIX_HPP
#define UPPER_TRIANGULAR_MATRIX_HPP


class UpperTriangularMatrix{

public:
    int nr;
    int nc;
    std::vector<double> v;
	vector<double> data;

    UpperTriangularMatrix(const int& nr, const int& nc){
		/* Constructor. */
		this->nr = nr;
		this->nc = nc;
        vector<double> this->data(nr*nc);
	}

    UpperTriangularMatrix(const UpperTriangularMatrix& M){
        this->nr = nr;
        this->nc = nc;
        this->data = M.data;
    }

    /*
    • a constructor UpperTriangularMatrix(const int&, const int&) intializing nr,nc
    with the input parameters and sizing data accordingly, setting the coefficients to 0.
    • a copy constructor
    • a copy assignment operator =
    • member function void push_back(const int& j, const int& k, const double&
    v) that adds the value v in row-column position (j,k). This routine shall check that
    the position (j,k) is located in the upper triangular part and returns an error if
    not.
    • operator ( , ) that takes a pair of integers (j, k) and returns the (r-valued) coefficient
    located at the j-th row and k-th column.
    • output stream operator <<
    • member-function std::vector<double> Solve(const std::vector<double>& b)
    that solves the corresponding upper triangular linear system with b as right-hand
    side, and returning the solution.
    • friend function int NbRow(const DenseMatrix&) that returns the number of rows
    • friend function int NbCol(const DenseMatrix&) that returns the number of columns

    */


};



#endif
