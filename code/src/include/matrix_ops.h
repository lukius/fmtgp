#ifndef __MATRIX_OPS__H
#define __MATRIX_OPS__H

#include <algorithm>
#include <limits>
#include "misc.h"


template<Integer N>
struct PlusTimes
{
    N additive_identity() { return 0; };

    N multiply(N a, N b) { return a*b; };

    N add(N a, N b) { return a+b; };
};


template<Integer N>
struct OrAnd
{
    N additive_identity() { return 0; };

    N multiply(N a, N b) { return a && b; };

    N add(N a, N b) { return a || b; };
};


template<Integer N>
struct MinPlus
{
    static N infinity() { return std::numeric_limits<N>::max(); };

    N additive_identity() { return infinity(); };

    N multiply(N a, N b)
    { 
        if(a == infinity() || b == infinity())
            return infinity();
        else        
            return a+b;
    };

    N add(N a, N b) { return std::min(a,b); };
};


template<Integer N, typename Operation, size_t n, size_t m=n, size_t l=n>
struct MatrixMultiplication
{
    Operation _operation;

    MatrixMultiplication(Operation op) : _operation(op) {};

    // Traditional matrix multiplication running in cubic time.
    // Might implement Strassen later (but... won't work for
    // min-plus matrix multiplication)
    Matrix<N,n,l> operator()(Matrix<N,n,m> m1, Matrix<N,m,l> m2)
    {
        Matrix<N,n,l> prod;
        N product;

        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < l; ++j)
                for(size_t k = 0; k < m; ++k)
                {
                    if(k == 0)
                        prod(i,j) = _operation.additive_identity();
                    product = _operation.multiply(m1(i,k), m2(k,j));
                    prod(i,j) = _operation.add(prod(i,j), product);                    
                }

        return prod;
    };

    Matrix<N,n,n> identity()
    {
        Matrix<N,n,n> id;

        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < n; ++j)
                id(i,j) = (i == j) ? 1 : 0;

        return id;
    };
};

#endif
