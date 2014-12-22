#ifndef __MISC__H
#define __MISC__H

#include <algorithm>

#define Regular typename
#define Integer typename
#define SemigroupOperation typename
#define MonoidOperation typename

#define divides(k,n) (n % k == N(0))
#define coprime(n,k) (gcd(n,k) == N(1))

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


template<Integer N>
N gcd(N a, N b)
{
    while(b != N(0))
    {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

#endif
