#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <cmath>
#include <ctime>
#include "ComplexD.hpp"
using namespace std;

// #include "Matrix.hpp"
#include "FFT.hpp"
#include "polynome.hpp"



int main(){

    const int TEST1 = 0;
    const int TEST2 = 0;
    const int TEST3 = 0;
    const int TEST4 = 1;


    if (TEST1){
        ComplexD z(0, 1);
        ComplexD z2(z);
        ComplexD z3 = z2;

        // Testing +, *, +=, *=
        cout << "z = "    << z    << endl;
        cout << "z2 = "   << z2   << endl;
        cout << "z3 = "   << z3   << endl;
        cout << "z+z2 = " << z+z2 << endl;
        cout << "z-z2 = " << z-z2 << endl;
        cout << "z*z2 = " << z*z2 << endl;

    }

    if (TEST2){
        ComplexD z1(1, 0);
        ComplexD z2(1, 0);
        ComplexD z3(1, 0);
        ComplexD z4(1, 0);
        ComplexD z5(0, 0);
        vector<ComplexD> V = {z1, z2, z3, z4};
        // vector<ComplexD> V = {z1, z2, z3, z4, z5};

        // ComplexD z1(0.25, 0);
        // ComplexD z2(0.25, 0);
        // ComplexD z3(0.25, 0);
        // ComplexD z4(0.25, 0);
        // vector<ComplexD> V = {z1, z2, z3, z4};

        // ComplexD z0(3, 0);
        // ComplexD z1(4, 0);
        // ComplexD z2(6, 0);
        // ComplexD z3(2, 0);
        // ComplexD z4(1, 0);
        // ComplexD z5(10, 0);
        // vector<ComplexD> V = {z0, z1, z2, z3, z4, z5};

        // ComplexD z0(3, 0);
        // ComplexD z1(4, 0);
        // vector<ComplexD> V = {z0, z1};


        cout << "V:" << endl;
        for (int i = 0; i < V.size(); i++){
            cout << V[i] << endl;
        }
        cout << endl;

        ComplexD root(0, 1);  // root = i

        vector<ComplexD> res = FFT(V);

        cout << "FFT of V:" << endl;
        for (int i = 0; i < res.size(); i++){
            cout << res[i] << endl;
        }
        cout << endl;
    
    
    }

    if (TEST3){
        ComplexD z1(1, 0);
        ComplexD z2(1, 0);
        ComplexD z3(1, 0);
        ComplexD z4(1, 0);
        vector<ComplexD> V = {z1, z2, z3, z4};
        

        // ComplexD z1(0.25, 0);
        // ComplexD z2(0.25, 0);
        // ComplexD z3(0.25, 0);
        // ComplexD z4(0.25, 0);
        // vector<ComplexD> V = {z1, z2, z3, z4};

        // ComplexD z0(3, 0);
        // ComplexD z1(4, 0);
        // ComplexD z2(6, 0);
        // ComplexD z3(2, 0);
        // ComplexD z4(1, 0);
        // ComplexD z5(10, 0);
        // vector<ComplexD> V = {z0, z1, z2, z3, z4, z5};

        // ComplexD z0(3, 0);
        // ComplexD z1(4, 0);
        // vector<ComplexD> V = {z0, z1};


        cout << "V:" << endl;
        for (int i = 0; i < V.size(); i++) {
            cout << V[i] << "\t";
        }
        cout << endl;

        cout << "Step1" << endl;
        ComplexD root(0, -1);  // root = i
        cout << "Step2" << endl;

        vector<ComplexD> res = IFFT(V);
        cout << "Step3" << endl;
        

        cout << "IFFT of V:" << endl;
        for (int i = 0; i < res.size(); i++) {
            cout << res[i] << "\t";
        }
        cout << endl;
    }


    if (TEST4){
        ComplexD z1(0, 0);
        ComplexD z2(1, 0);
        ComplexD z3(1, 0);
        ComplexD z4(1, 0);
        ComplexD z5(0, 0);
        ComplexD z6(0, 0);
        ComplexD z7(0, 0);
        ComplexD z8(0, 0);
        vector<ComplexD> V1 = {z1, z2};

        ComplexD y0(0, 0);
        ComplexD y1(0, 0);
        ComplexD y2(1, 0);
        ComplexD y3(2, 0);
        ComplexD y4(1, 0);
        ComplexD y5(10, 0);
        vector<ComplexD> V2 = {y0, y1, y2, y3};

        cout << "Polynomial 1:" << endl;
        for (int i = 0; i < V1.size(); i++) {
            cout << V1[i] << "\t";
        }
        cout << endl;

        cout << "Polynomial 2:" << endl;
        for (int i = 0; i < V2.size(); i++) {
            cout << V2[i] << "\t";
        }
        cout << endl;


        vector<ComplexD> res = naive_mult(V1, V2);
        

        cout << "Naive mult of V1 and V2:" << endl;
        for (int i = 0; i < res.size(); ++i) {
            cout << res[i] << "\t";
        }
        cout << endl << endl;

        res = FFT_mult(V1, V2);
        

        cout << "FFT mult of V1 and V2:" << endl;
        for (int i = 0; i < res.size(); ++i) {
            cout << res[i] << "\t";
        }
        cout << endl;
    }
    
    return 0;
}
