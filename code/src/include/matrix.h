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

    friend std::ostream &operator<<(std::ostream &os,
                                    const Matrix<T,rows,cols> &m)
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

#endif
