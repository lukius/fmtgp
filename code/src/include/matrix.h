#ifndef __MATRIX__H
#define __MATRIX__H

template<typename T, size_t rows, size_t cols>
using _Matrix = T[rows][cols];

// A very rudimentary matrix implementation.
template<typename T, size_t rows, size_t cols>
struct Matrix
{
    _Matrix<T,rows,cols> _M;

    Matrix() {};
    Matrix(_Matrix<T,rows,cols> m) { _M = m; };

    T &operator()(size_t i, size_t j) { return _M[i][j]; };

    template<typename S>
    friend std::ostream &operator<<(std::ostream &os,
                                    const Matrix<S,rows,cols> &m)
    {
        std::string comma;
        os << "[";
        for(size_t i = 0; i < rows; ++i)
        {
            os << "[";
            for(size_t j = 0; j < cols; ++j)
            {
                comma = (j == cols-1) ? "" : ", ";
                os << m._M[i][j] << comma;
            }
            comma = (i == rows-1) ? "" : ", ";
            os << "]" << comma;
        }
        os << "]";
        return os;
    };
};

template<size_t n, size_t m=n, size_t l=n>
struct MatrixMultiplication
{
    // Traditional matrix multiplication running in cubic time.
    // Might implement Strassen later.
    Matrix<int,n,l> operator()(Matrix<int,n,m> m1, Matrix<int,m,l> m2)
    {
        Matrix<int,n,l> prod;

        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < l; ++j)
                for(size_t k = 0; k < m; ++k)
                {
                    if(k == 0) prod(i,j) = 0;
                    prod(i,j) += m1(i,k) * m2(k,j);
                }

        return prod;
    };

    Matrix<int,n,n> identity()
    {
        Matrix<int,n,n> id;

        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < n; ++j)
                id(i,j) = (i == j) ? 1 : 0;

        return id;
    };
};

#endif
