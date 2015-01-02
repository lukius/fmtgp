#ifndef _POLY_H_
#define _POLY_H_

#include "misc.h"
#include <string>
#include <utility>
#include <vector>

#define deg_coef std::pair<int, K>


// K[X] polynomials. The vector _coef holding the coefficients is such that
// {(n_0, a_{n_0}),(n_1, a_{n_1}),...,(n_k, a_{n_k})} = a_{n_0} x^{n_0} + 
// a_{n_1} x^{n_1} + ... + a_{n_k} x^{n_k}
// where n_0 > n_1 > ... > n_k.
// That is, each element in _coef is a tuple (degree, coefficient). In
// particular, the first element holds the information regarding the degree of
// the polynomial and its associated coefficient.
template<Field K>
class Polynomial
{
private:
    std::vector<deg_coef> _coef;

    Polynomial multiply(const K &coef, int deg) const
    {
        Polynomial<K> result(*this);
        for(size_t i = 0; i < _coef.size(); ++i)
        {
            result._coef[i].first += deg;
            result._coef[i].second *= coef;
        }
        return result;
    }

public:
    Polynomial() : Polynomial(int(0)) {};
    
    Polynomial(int coef)
    {
        _coef.push_back({int(0), coef});
    };
    
    Polynomial(const std::vector<K> &coef)
    {
        // Generate a polynomial from a list of coefficients {a_n,...,a_0}.
        size_t n(coef.size());
        for(size_t i = 0; i < n; ++i)
            if(coef[i] != K(0))
                _coef.push_back({n-i-1, coef[i]});
        if(_coef.size() == int(0))
            _coef.push_back({int(0), K(0)});
    };

    Polynomial(const std::vector<deg_coef> &coef) : _coef(coef) {};

    int degree() const
    {
        return _coef[0].first;
    };

    Polynomial operator+(const Polynomial &other) const
    {
        std::vector<deg_coef> res_coef;
        size_t i(0), j(0);

        while(i < _coef.size() && j < other._coef.size())
        {
            if(_coef[i].first == other._coef[j].first)
            {
                K value = _coef[i].second + other._coef[j].second;
                if(value != K(0))
                    res_coef.push_back({_coef[i].first, value});
                i++; j++;
            }
            else if(_coef[i].first > other._coef[j].first)
            {
                res_coef.push_back(_coef[i]);
                i++;
            }
            else
            {
                res_coef.push_back(other._coef[j]);
                j++;
            }
        }

        for(; i < _coef.size(); ++i)
            res_coef.push_back(_coef[i]);

        for(; j < other._coef.size(); ++j)
            res_coef.push_back(other._coef[j]);
        
        if(res_coef.size() == 0)
            res_coef.push_back({int(0), K(0)});

        return Polynomial<K>(res_coef);
    }

    Polynomial operator%(const Polynomial &divisor) const
    {
        Polynomial<K> remainder(*this);
        K div_coef(divisor._coef[0].second);
        int div_degree(divisor.degree());

        while(remainder != Polynomial<K>(0) &&
              remainder.degree() >= div_degree)
        {
            K coef = remainder._coef[0].second;
            remainder = remainder + divisor.multiply(-coef/div_coef,
                                                     remainder.degree()-div_degree);
        }

        // Normalize coefficients by dividing by the highest degree coefficient.
        if(remainder._coef[0].second != K(0))
            remainder = remainder.multiply(1/remainder._coef[0].second, int(0));

        return remainder;
    };

    bool operator!=(const Polynomial &other) const
    {
        return _coef != other._coef;        
    };

    friend std::ostream &operator<<(std::ostream &os, const Polynomial<K> &p)
    {
        std::string plus;

        for(size_t i = 0; i < p._coef.size(); ++i)
        {
            int n = p._coef[i].first;
            K coef = p._coef[i].second;
            plus = (i+1 < p._coef.size())
                        ? ((p._coef[i+1].second < K(0)) ? " - " : " + ")
                        : "";

            if(i == int(0) && coef != K(1))            
                os << coef;
            else if(coef != K(1) || n == 0)
                os << abs(coef);
            if(n == int(1))
                os << "X";
            else if(n > int(0))
                os << "X^" << n;
            os << plus;
        }

        return os; 
    };
};

#endif
