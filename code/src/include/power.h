#ifndef __POWER__H
#define __POWER__H

#include "misc.h"

template<Regular A, Integer N, SemigroupOperation Op>
A power_accumulate_semigroup(A r, A a, N n, Op op)
{
    if(n == 0) return r;

    while(true)
    {
        if(odd(n))
        {
            r = op(r, a);
            if(n == 1) return r;
        }

        n = half(n);
        a = op(a, a);
    }
}

template<Regular A, Integer N, SemigroupOperation Op>
A power_semigroup(A a, N n, Op op)
{
    while(!odd(n))
    {
        a = op(a, a);
        n = half(n);
    }
    
    if(n == 1) return a;
    return power_accumulate_semigroup(a, op(a,a), half(n-1), op);
}

template<Regular A, Integer N, MonoidOperation Op>
A power_monoid(A a, N n, Op op)
{
    if(n == 0) return op.identity();
    return power_semigroup(a, n, op);
}

#endif
