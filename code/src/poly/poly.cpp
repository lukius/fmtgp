#include <iostream>
#include <gmpxx.h>
#include "misc.h"
#include "poly.h"
using namespace std;


int main(int argc, char *argv[])
{
    Polynomial<mpq_class> p({1,0,-1}), q({1,-2,1}),
                          r({3,-3,-117,-93,210}),
                          s({4,-60,220,300,-1664,-1680});

    cout << "p(X) = " << p << endl;
    cout << "q(X) = " << q  << endl;
    cout << "GCD(p, q) = " << gcd(p, q) << endl;

    cout << endl;

    cout << "r(X) = " << r << endl;
    cout << "s(X) = " << s  << endl;
    cout << "GCD(r, s) = " << gcd(r, s) << endl;

    return 0;
}
