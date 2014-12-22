#ifndef __MODPOW__H
#define __MODPOW__H

#include "misc.h"

template<Integer N>
struct ModPow
{
    N _modulus;

    ModPow(const N &n) : _modulus(n) {};

    N operator()(const N &n, const N &m) const
    {
        return (n*m) % _modulus; 
    };

    N identity() const
    {
        return N(1);
    }
};

#endif
