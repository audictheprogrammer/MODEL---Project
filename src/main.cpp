#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <cmath>
#include <ctime>
#include <fstream>

#include "../include/ComplexD.hpp"
#include "../include/FFT.hpp"
#include "../include/polynome.hpp"

#define MAX_R 4294967296

#define VALID "\x1B[32m[VALID]\033[0m"
#define INVALID "\x1B[31m[INVALID]\033[0m"

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



int main(int argc, char* argv[]){

    int TEST1 = 1;  // arithmetic operations
    int TEST2 = 1;  // FFT
    int TEST3 = 1;  // IFFT
    int TEST4 = 1;  // polynom multiplication with FFT
    int TEST5 = 0;  // Compare the execution time between FFT and naive multiplication
    int TEST6 = 0;  // Check validity of both Poly mult.

    std::cout << "Do you want to use your own polynomials to test the FFT multiplication method ?\n"
                "Otherwise our prepared set of tests will be launched.\n [y/n] ";
    char answer[1];
    std::cin >> answer;
    if (answer[0] == 'y') { 
        TEST1 = 0;
        TEST2 = 0;
        TEST3 = 0;
        TEST4 = 0;
        TEST5 = 0;
        TEST6 = 0;
        
        int size;
        double real;
        double imag;

        std::cout << "Please select the size of your first polynomial.\n";
        std::cin >> size;
        vector<ComplexD> P(size);
        std::cout << "Enter the real part, then the imaginary part.\n";
        
        for (int i = 0; i < size; ++i) {
            std::cout << "P[" << i << "] = ";
            std::cin >> real;
            std::cin >> imag;
            std::cout << std::endl;
            P[i] = ComplexD(real, imag);
        }
    
        std::cout << "Please select the size of your second polynomial.\n";
        std::cin >> size;
        vector<ComplexD> Q(size);
        std::cout << "Enter the real part, then the imaginary part.\n";

        for (int i = 0; i < size; ++i) {
            std::cout << "Q[" << i << "] = ";
            std::cin >> real;
            std::cin >> imag;
            std::cout << std::endl;
            Q[i] = ComplexD(real, imag);
        }
        
        cout << "Polynomial 1:" << endl;
        for (std::size_t i = 0; i < P.size(); i++) {
            cout << P[i] << "\t";
        }
        cout << endl;

        cout << "Polynomial 2:" << endl;
        for (std::size_t i = 0; i < Q.size(); i++) {
            cout << Q[i] << "\t";
        }
        cout << endl << endl;

        vector<ComplexD> res_naif = naive_mult(P, Q);
        vector<ComplexD> res_FFT = FFT_mult(P, Q);
        
        
        cout << "Naive mult of V1 and V2:" << endl;
        for (std::size_t i = 0; i < res_naif.size(); ++i) {
            cout << res_naif[i] << "\t";
        }
        cout << endl;
        
        cout << "FFT mult of V1 and V2:" << endl;
        for (std::size_t i = 0; i < res_FFT.size(); ++i) {
            cout << res_FFT[i] << "\t";
        }
        cout << endl;

        char *color = (char *)INVALID;
        if (verif_poly(res_naif, res_FFT))
            color = (char *)VALID;
        cout << "Polynom multiplication : " <<  color << endl;        

    }
    
    if (TEST1) {
        cout << "### Test opérations arithmétiques ###\n";
        ComplexD z0 = ComplexD();
        ComplexD z1(1, 1);
        ComplexD z2(1, 0);
        ComplexD z3(0, 4);
        ComplexD z4(z1);
        ComplexD z5 = z2;

        // Testing +, *, +=, *=
        cout << "Constructeur :\t" << ((z1.x == 1 && z1.y == 1) ? VALID : INVALID) << endl;
        cout << "Constr. vide :\t" << ((z0.x == 0 && z0.y == 0) ? VALID : INVALID) << endl;
        cout << "Copie    :\t" << ((z4.x == z1.x && z4.y == z1.y) ? VALID : INVALID) << endl;
        cout << " =       :\t" << ((z5.x == z2.x && z5.y == z2.y) ? VALID : INVALID) << endl;
        cout << " +(int)  :\t" << (((z5+4).x == 5 && (z5+4).y == 0) ? VALID : INVALID) << endl;
        cout << " +       :\t" << (((z1+z2).x == 2 && (z1+z2).y == 1) ? VALID : INVALID) << endl;
        z5 += 4;
        cout << " +=(int) :\t" << ((z5.x == 5 && z5.y == 0) ? VALID : INVALID) << endl;
        z1 += z2;
        cout << " +=      :\t" << ((z1.x == 2 && z1.y == 1) ? VALID : INVALID) << endl;
        cout << " -(int)  :\t" << (((z5-4).x == 1 && (z5-4).y == 0) ? VALID : INVALID) << endl;
        cout << " -       :\t" << (((z1-z3).x == 2 && (z1-z3).y == -3) ? VALID : INVALID) << endl;
        z5 -= 4;
        cout << " -=(int) :\t" << ((z5.x == 1 && z5.y == 0) ? VALID : INVALID) << endl;
        z1 -= z3;
        cout << " -=      :\t" << ((z1.x == 2 && z1.y == -3) ? VALID : INVALID) << endl;
        cout << " *(int)  :\t" << (((z3*2).x == 0 && (z3*2).y == 8) ? VALID : INVALID) << endl;
        cout << " *       :\t" << (((z1*z3).x == 12 && (z1*z3).y == 8) ? VALID : INVALID) << endl;
        z2 *= 3;
        cout << " *=(int) :\t" << ((z2.x == 3 && z2.y == 0) ? VALID : INVALID) << endl;
        z1 *= z3;
        cout << " *=      :\t" << ((z1.x == 12 && z1.y == 8) ? VALID : INVALID) << endl;
        cout << " /(int)  :\t" << (((z2/2).x == 1.5 && (z2/2).y == 0) ? VALID : INVALID) << endl;
        cout << " /       :\t" << (((z3/z1).x == (double)32/208 && (z3/z1).y == (double)48/208) ? VALID : INVALID) << endl;
        z2 /= 2;
        cout << " /=(int) :\t" << ((z2.x == 1.5 && z2.y == 0) ? VALID : INVALID) << endl;
        z3 /= z1;
        cout << " /=      :\t" << ((z3.x == (double)32/208 && z3.y == (double)48/208) ? VALID : INVALID) << endl;
        cout << endl;
    }

    if (TEST2){
        ComplexD z1(1, 0);
        ComplexD z2(1, 0);
        ComplexD z3(1, 0);
        ComplexD z4(1, 0);
        ComplexD z5(1, 0);
        vector<ComplexD> V = {z1, z2, z3, z4};

        cout << "### Test FFT ###\n";

        ComplexD root(0, 1);  // root = i

        vector<ComplexD> res = FFT(V);


        cout << "V:" << endl;
        for (size_t i = 0; i < V.size(); i++){
            cout << V[i] << "\t";
        }
        cout << endl;

        cout << "FFT of V:" << endl;
        for (std::size_t i = 0; i < res.size(); i++){
            cout << res[i] << "\t";
        }
        cout << endl;
        cout << ((res[0] == 4 && res[1] == 0 && res[2] == 0 && res[3] == 0) ? VALID : INVALID) << endl << endl;
    
    }

    if (TEST3){
        ComplexD z1(1, 0);
        ComplexD z2(1, 0);
        ComplexD z3(1, 0);
        ComplexD z4(1, 0);
        vector<ComplexD> V = {z1, z2, z3, z4};

        cout << "### Test Inverse FFT ###\n";
        cout << "V:" << endl;
        for (std::size_t i = 0; i < V.size(); i++) {
            cout << V[i] << "\t";
        }
        cout << endl;

        ComplexD root(0, -1);  // root = i
        vector<ComplexD> res = IFFT(V);
        

        cout << "IFFT of V:" << endl;
        for (size_t i = 0; i < res.size(); i++) {
            cout << res[i] << "\t";
        }
        cout << endl << ((res[0] == 1 && res[1] == 0 && res[2] == 0 && res[3] == 0) ? VALID : INVALID) << endl << endl;

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

        cout << "### Test produit polynomes ###\n";

        cout << "Polynomial 1:" << endl;
        for (std::size_t i = 0; i < V1.size(); i++) {
            cout << V1[i] << "\t";
        }
        cout << endl;

        cout << "Polynomial 2:" << endl;
        for (std::size_t i = 0; i < V2.size(); i++) {
            cout << V2[i] << "\t";
        }
        cout << endl << endl;


        vector<ComplexD> res_naif = naive_mult(V1, V2);
        vector<ComplexD> res_FFT = FFT_mult(V1, V2);
        
        
        cout << "Naive mult of V1 and V2:" << endl;
        for (std::size_t i = 0; i < res_naif.size(); ++i) {
            cout << res_naif[i] << "\t";
        }
        cout << endl;

        cout << "FFT mult of V1 and V2:" << endl;
        for (std::size_t i = 0; i < res_FFT.size(); ++i) {
            cout << res_FFT[i] << "\t";
        }
        cout << endl << endl;

        char *color = (char *)INVALID;
        if (verif_poly(res_naif, res_FFT))
            color = (char *)VALID;
        cout << "Produit de polynomes avec FFT : " << color << endl << endl;
        
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


        // vector<size_t> Plot = {1, 2, 4, 8, 16, 32, 64 ,128, 256, 1024, 2048, 8192, 16384};
        vector<size_t> Plot = {32, 64 , 128, 256, 1024, 2048, 8192, 16384, 32768, 65536};
        cout << "Plot size = " << Plot.size() << endl;

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
        cout << "TEST 6 : " <<  color << endl;
    }

    return 0;
}
