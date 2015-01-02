#ifndef __MISC__H
#define __MISC__H

#include <algorithm>

#define Regular typename
#define Integer typename
#define SemigroupOperation typename
#define MonoidOperation typename
#define Field typename
#define EuclideanDomain typename

#define divides(k,n) (n % k == 0)
#define coprime(n,k) (gcd(n,k) == 1)


template<Integer N>
bool odd(N n)
{
    return (n & 0x1) == 1;
} 

template<Integer N>
N half(N n)
{
    return n >> 1;
}

template<EuclideanDomain E>
E gcd(E a, E b)
{
    while(b != E(0))
    {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

#endif
