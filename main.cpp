#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <cmath>
#include <ctime>
#include <fstream>

#include "ComplexD.hpp"
#include "FFT.hpp"
#include "polynome.hpp"

#define MAX_R 4294967296

#define VALID "\x1B[32mVALID\033[0m"
#define INVALID "\x1B[31mINVALID\033[0m"

using namespace std;

tuple<double, double> benchmark_poly_mult(size_t size) {
    vector<ComplexD> P1(size);
    vector<ComplexD> P2(size);

    init_poly(P1, MAX_R);
    init_poly(P2, MAX_R);

    std::clock_t start = std::clock();
    vector<ComplexD> P3 = naive_mult(P1, P2);
    std::clock_t end = std::clock();

    double t_naif = static_cast<double> (end - start) / CLOCKS_PER_SEC;
    
    start = std::clock();
    P3 = FFT_mult(P1, P2);
    end = std::clock();
    
    double t_FFT = static_cast<double> (end - start) / CLOCKS_PER_SEC;

    std::tuple<double, double> res(t_naif, t_FFT);
    
    return res;

}



int main(){

    const int TEST1 = 1;
    const int TEST2 = 0;
    const int TEST3 = 0;
    const int TEST4 = 0;
    const int TEST5 = 1;
    const int TEST6 = 0;


    if (TEST1){
        cout << "### Test opérations arithmétiques ###\n";
        ComplexD z(0, 1);
        ComplexD z2(z);
        ComplexD z3 = z2;

        // Testing +, *, +=, *=
        cout << "z\t=  "    << z    << " :\t";
        cout << ((z.x == 0 && z.y == 1) ? VALID : INVALID) << endl;
        cout << "z2\t=  "   << z2   << " :\t";
        cout << ((z2.x == 0 && z2.y == 1) ? VALID : INVALID) << endl;
        cout << "z3\t=  "   << z3   << " :\t";
        cout << ((z3.x == 0 && z3.y == 1) ? VALID : INVALID) << endl;
        cout << "z + z2\t=  " << z+z2 << " :\t";
        cout << (((z+z2).x == 0 && (z+z2).y == 2) ? VALID : INVALID) << endl;
        cout << "z += z2\t=  " << (z+=z2) << " :\t";
        cout << ((z.x == 0 && z.y == 2) ? VALID : INVALID) << endl;
        cout << "z - z2\t=  " << z-z2 << " :\t";
        cout << (((z-z2).x == 0 && (z-z2).y == 1) ? VALID : INVALID) << endl;
        cout << "z -= z2\t=  " << (z-=z2) << " :\t";
        cout << ((z.x == 0 && z.y == 1) ? VALID : INVALID) << endl;
        cout << "z * z2\t= " << z*z2 << " :\t";
        cout << (((z*z2).x == -1 && (z*z2).y == 0) ? VALID : INVALID) << endl;
        cout << "z *= z2\t= " << (z*=z2) << " :\t";
        cout << ((z.x == -1 && z.y == 0) ? VALID : INVALID) << endl;
        cout << "z2 / z\t= " << z2/z << " :\t";
        cout << (((z2/z).x == -1 && (z2/z).y == 0) ? VALID : INVALID) << endl;

    }

    if (TEST2){
        ComplexD z1(1, 0);
        ComplexD z2(1, 0);
        ComplexD z3(1, 0);
        ComplexD z4(1, 0);
        ComplexD z5(1, 0);
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
        for (size_t i = 0; i < V.size(); i++){
            cout << V[i] << endl;
        }
        cout << endl;

        ComplexD root(0, 1);  // root = i

        vector<ComplexD> res = FFT(V);

        cout << "FFT of V:" << endl;
        for (std::size_t i = 0; i < res.size(); i++){
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
        for (std::size_t i = 0; i < V.size(); i++) {
            cout << V[i] << "\t";
        }
        cout << endl;

        // cout << "Step1" << endl;
        ComplexD root(0, -1);  // root = i
        // cout << "Step2" << endl;

        vector<ComplexD> res = IFFT(V);
        // cout << "Step3" << endl;
        

        cout << "IFFT of V:" << endl;
        for (size_t i = 0; i < res.size(); i++) {
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
        for (std::size_t i = 0; i < V1.size(); i++) {
            cout << V1[i] << "\t";
        }
        cout << endl;

        cout << "Polynomial 2:" << endl;
        for (std::size_t i = 0; i < V2.size(); i++) {
            cout << V2[i] << "\t";
        }
        cout << endl;


        vector<ComplexD> res_naif = naive_mult(V1, V2);
        vector<ComplexD> res_FFT = FFT_mult(V1, V2);
        
        char *color = (char *)INVALID;
        if (verif_poly(res_naif, res_FFT))
            color = (char *)VALID;
        printf("TEST 4 : %s\n", color);
        

        cout << "Naive mult of V1 and V2:" << endl;
        for (std::size_t i = 0; i < res_naif.size(); ++i) {
            cout << res_naif[i] << "\t";
        }
        cout << endl << endl;

        

        cout << "FFT mult of V1 and V2:" << endl;
        for (std::size_t i = 0; i < res_FFT.size(); ++i) {
            cout << res_FFT[i] << "\t";
        }
        cout << endl;
    }

    if (TEST5){

        ofstream f1;
        ofstream f2;
        f1.open("Benchmark1.txt");
        f2.open("Benchmark2.txt");

        if (!f1.is_open()){
            cout << "Error f1.open: NOT OPEN !" << endl;
        }
        if (!f2.is_open()){
            cout << "Error f2.open: NOT OPEN !" << endl;
        }


        vector<size_t> Plot = {1, 2, 4, 8, 16, 32, 64 ,128,\
                               256, 1024, 2048, 8192, 16384};
        for (size_t i = 0; i < Plot.size(); i++){
            size_t size = Plot[i];
            tuple<double, double> time = benchmark_poly_mult(size);
            f1 << size << " " << get<0>(time) << endl;
            f2 << size << " " << get<1>(time) << endl;
            
            cout << "NaiveMult: "<< size << " " << get<0>(time) << endl;
            cout << "FFTMult: "<< size << " " << get<1>(time) << endl;
            cout << endl;
        }

        f1.close();
        f2.close();

    }

    if (TEST6) {

        std::cout << "Polynome size wished ?\n";
        
        std::size_t size;
        //std::scanf("%ld", &size);
        std::cin >> size;

        std::vector<ComplexD> P6(size);

        init_poly(P6, 10);
        std::vector<ComplexD> Q6 = P6;

        std::vector<ComplexD> res_naif = naive_mult(P6,Q6);
        std::vector<ComplexD> res_FFT  = FFT_mult(P6,Q6);

        char *color = (char *)INVALID;
        if (verif_poly(res_naif, res_FFT))
            color = (char *)VALID;
        printf("TEST 6 : %s\n", color);
    }

    return 0;
}
