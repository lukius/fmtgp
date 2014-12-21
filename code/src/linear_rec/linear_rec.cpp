#include <iostream>
#include <vector>
#include "power.h"
#include "matrix.h"
#include "matrix_ops.h"
using namespace std;


template<size_t k>
Matrix<int,k,k> coef_matrix_from(const vector<int> &coefficients)
{
    Matrix<int,k,k> m;

    for(size_t j = 0; j < k; ++j)
        m(0,j) = coefficients[j];
    
    for(size_t i = 1; i < k; ++i)
        for(size_t j = 0; j < k; ++j) 
            m(i,j) = (i == j+1) ? 1 : 0;

    return m;
}

// Solve arbitrary k-order linear recurrences by supplying their k coefficients
// and k initial values. Since matrices conform a monoid with the usual
// multiplication operation, power_monoid can be used to compute fast matrix
// powers.
template<size_t k>
int linear_recurrence_seq(size_t n, const vector<int> &coefficients,
                          const vector<int> &initial_values)
{
    Matrix<int,k,k> coef_matrix = coef_matrix_from<k>(coefficients);
    PlusTimes<int> plus_times;
    MatrixMultiplication<int,PlusTimes<int>,k> k_k_mult(plus_times);
    MatrixMultiplication<int,PlusTimes<int>,k,k,1> k_1_mult(plus_times);

    Matrix<int,k,1> iv_matrix;
    for(size_t i = 0; i < k; ++i)
        iv_matrix(i,0) = initial_values[k-i-1];

    Matrix<int,k,k> coef_pow = power_monoid(coef_matrix, n-k+1,
                                            k_k_mult);
    Matrix<int,k,1> result = k_1_mult(coef_pow, iv_matrix);

    return result(0,0);
}

int fibonacci(size_t n)
{
    vector<int> coefficients = {1, 1};
    vector<int> initial_values = {0, 1};

    return linear_recurrence_seq<2>(n, coefficients, initial_values);
}

int custom_recurrence(size_t n)
{
    // C(0) = 2; C(1) = -1; C(2) = 5
    // C(n) = 4C(n-1) + C(n-2) - 7C(n-3)  (n >= 3)

    vector<int> coefficients = {4, 1, -7};
    vector<int> initial_values = {2, -1, 5};

    return linear_recurrence_seq<3>(n, coefficients, initial_values);
}

int main(int argc, char *argv[])
{
    cout << "Fib(45) = " << fibonacci(45) << endl; 
    cout << "Now test a custom recurrence C defined as follows:" << endl;
    cout << "C(0) = 2; C(1) = -1; C(2) = 5" << endl;
    cout << "C(n) = 4C(n-1) + C(n-2) - 7C(n-3)  (n >= 3)" << endl;
    cout << "C(10) = " << custom_recurrence(10) << endl; 

    return 0;
}
