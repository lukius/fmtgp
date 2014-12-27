#include <gmpxx.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include "misc.h"
using namespace std;

template<typename N>
using pair_N = pair<N, N>;

template<typename N>
using three_uple = pair<N, pair_N<N>>;


template<Integer N>
pair_N<N> solve_system(pair_N<N> eq_1, pair_N<N> eq_2)
{
    #define a eq_1.first
    #define b eq_1.second
    #define c eq_2.first
    #define d eq_2.second

    // Find k such that
    //  |a  b|-1  |  k | 
    //  |c  d|    |-k+1|
    // has integer coefficients. In other words, 
    // ad - bc | k(d + b) - b
    // ad - bc | a - k(a + c)

    N det(a*d - b*c);
    N num1, num2;
    for(N k(0);; ++k)
    {
        num1 = k*(d + b) - b;
        num2 = a - k*(a + c);
        if (divides(det, num1) && divides(det, num2)) break;

        num1 = d - k*(d + b);
        num2 = k*(a + c) - c;
        if (divides(det, num1) && divides(det, num2)) break;
    }

    return {num1/det, num2/det};
}


template<Integer N>
three_uple<N> stein_egcd(N m, N n)
{
    // Compute (d, x, y) such that
    // mx + ny = d = gcd(m, n)
    
    // Every transformation of m and n in Stein's algorithm is adapted
    // in order to transform x and y as well. This generates a 2x2 linear
    // system, which solves to (k -k+1) for some k. At the very end of 
    // the algorithm, we have that m' == n', and taking x' = k and
    // y' = 1-k (or viceversa) solves m'x' + n'y' = d = m'. Thus, the idea
    // is to find a k that solves this linear system in such a way that the
    // solution has integer coefficients.
    // 
    // Since k is brute-forced, the algorithm is not efficient at all. In fact,
    // I've just found a proper extended binary GCD algorithm after googling it.
    // I'm not sure if k can be found algebraically... :(

    #define two_count(m, n, d)  while(!odd(m) && !odd(n)) { n >>= 1; m >>= 1;\
                                                            d++; }
    #define to_odd(a, eq)       while(!odd(a)) { a >>= 1; multiply_by_2(eq) }
    #define add_eq(eq1, eq2)    eq1.first += eq2.first;\
                                eq1.second += eq2.second;
    #define multiply_by_2(eq)   eq.first <<= 1; eq.second <<= 1;

    pair_N<N> eq_x({N(1), N(0)}),
              eq_y({N(0), N(1)});

    if(m < N(0)) m = -m;
    if(n < N(0)) n = -n;
    if(m == N(0)) return {n, {N(0), N(1)}};
    if(n == N(0)) return {m, {N(1), N(0)}};

    int t(0);
    two_count(m, n, t);
    to_odd(m, eq_x);
    to_odd(n, eq_y);
    
    while(m != n)
    {
        if(n > m)
        {
            swap(n, m);
            swap(eq_x, eq_y);
        }
        m -= n;
        add_eq(eq_y, eq_x);
        do
        {
            m >>= 1;
            multiply_by_2(eq_x);
        } while(!odd(m));
    }
    
    pair_N<N> x_y(solve_system(eq_x, eq_y));

    return {m << t, x_y};
} 


int main(int argc, char *argv[])
{
    mpz_class m(2*2*2*3*3*5*7*11*13), n(2*2*5*17*23*31);
    three_uple<mpz_class> values(stein_egcd(m, n));

    cout << "gcd(" << m << ", " << n << ") = " << values.first << endl;
    cout << values.second.first  << "*" << m << " + "
         << values.second.second << "*" << n << " = "
         << values.second.first*m + values.second.second*n << endl;

    return 0;
}
