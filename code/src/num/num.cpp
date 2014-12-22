#include <gmpxx.h>
#include <iostream>
#include "misc.h"
#include "power.h"
#include "modpow.h"
using namespace std;

#define NUM_CARMICHAELS 7

#define modpow power_monoid<N,N,ModPow<N> >

// Takes exponential time in the number of bits of n :(
template<Integer N>
bool is_carmichael(const N &n)
{
    #define modexp_is_1(k,n) (modpow(k, n-1, ModPow<N>(n)) == N(1))
    #define is_prime(n) (k*k >= n && divisors == N(1))

    N divisors(1);
    for(N k(2); k < n; ++k)
    {
        if(divides(k,n))
            divisors++;
    
        // An integer k such that k is coprime to n and k^{n-1} != 1 mod n
        // is a proof that n is not a Carmichael number. In addition,
        // if k >= sqrt(n) and the number of divisors of n we found is just 1,
        // then n is a prime number. Needs to be composite in order to be
        // a Carmichael number.
        if((coprime(n,k) && !modexp_is_1(k,n)) || is_prime(n))
            return false;
    }
    return n > 2;
} 


int main(int argc, char *argv[])
{
    int carmichaels(0);
    for(mpz_class n(0);; n++)
    {
        if(is_carmichael(n))
        {
            cout << "Carmichael number #"
                 << carmichaels+1
                 << ": "
                 << n << endl;
            carmichaels++;
        }
        if(carmichaels == NUM_CARMICHAELS)
            break;
    }

    return 0;
}
