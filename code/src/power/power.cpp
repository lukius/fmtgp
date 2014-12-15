#include <iostream>
#include "power.h"
#include "matrix.h"
using namespace std;

typedef Matrix<int,2,2> TMatrix;

struct IntegerMultiplication
{
    int operator()(int a, int n){ return a*n; };

    int identity() { return 1; };
};


int main(int argc, char *argv[])
{
    cout << "Multiplying integers using power_monoid..." << endl;
    IntegerMultiplication mult;
    int pow;

    pow = power_monoid(3, 5, mult);
    cout << "3^5 = " << pow << endl;
    pow = power_monoid(2, 10, mult);
    cout << "2^10 = " << pow << endl;

    cout << "Multiplying matrices using power_monoid..." << endl;
    TMatrix m1;
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 2;
    m1(1,1) = 1;
    MatrixMultiplication<2> matrix_mult;
    TMatrix mpow = power_monoid(m1, 2, matrix_mult);
    cout << m1 << "^2 = " << mpow << endl;

    return 0;
}
