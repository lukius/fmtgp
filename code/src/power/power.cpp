#include <iostream>
#include "power.h"
using namespace std;


struct IntegerMultiplication
{
    int operator()(int a, int n){ return a*n; };

    int identity() { return 1; };
};


int main(int argc, char *argv[])
{
    cout << "Multiplying integers using power_monoid..." << endl;
    IntegerMultiplication mult;
    int pow;

    pow = power_monoid(3, 5, mult);
    cout << "3^5 = " << pow << endl;
    pow = power_monoid(2, 10, mult);
    cout << "2^10 = " << pow << endl;

    return 0;
}
