#include <iostream>
#include "power.h"
#include "matrix.h"
#include "matrix_ops.h"
using namespace std;

typedef unsigned int uint;

int main(int argc, char *argv[])
{
    cout << "Multiplying matrices using power_monoid..." << endl;
    Matrix<int,2,2> m1;
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 2;
    m1(1,1) = 1;
    PlusTimes<int> plus_times;
    MatrixMultiplication<int, PlusTimes<int>, 2> matrix_mult(plus_times);
    Matrix<int,2,2> mpow = power_monoid(m1, 2, matrix_mult);
    cout << m1 << "^2 = " << mpow << endl;

    cout << "Computing transitive closure of some graph..." << endl;
    Matrix<int,3,3> graph;
    graph(0,0) = 1;
    graph(0,1) = 1;
    graph(0,2) = 0;
    graph(1,0) = 0;
    graph(1,1) = 1;
    graph(1,2) = 1;
    graph(2,0) = 1;
    graph(2,1) = 0;
    graph(2,2) = 1;
    OrAnd<int> or_and;
    MatrixMultiplication<int, OrAnd<int>, 3> matrix_mult2(or_and);
    Matrix<int,3,3> closure = power_monoid(graph, 2, matrix_mult2);
    cout << graph << "^2 = " << closure << endl;

    cout << "Computing shortest paths on some graph..." << endl;
    // Subgraph induced by {A,C,D,F} of graph on page 149.
    Matrix<uint,4,4> graph2;
    graph2(0,0) = 0;
    graph2(0,1) = MinPlus<uint>::infinity();
    graph2(0,2) = 3;
    graph2(0,3) = MinPlus<uint>::infinity();
    graph2(1,0) = 7;
    graph2(1,1) = 0;
    graph2(1,2) = MinPlus<uint>::infinity();
    graph2(1,3) = MinPlus<uint>::infinity();
    graph2(2,0) = MinPlus<uint>::infinity();
    graph2(2,1) = 5;
    graph2(2,2) = 0;
    graph2(2,3) = 4;
    graph2(3,0) = MinPlus<uint>::infinity();
    graph2(3,1) = 6;
    graph2(3,2) = MinPlus<uint>::infinity();
    graph2(3,3) = 0;
    MinPlus<uint> min_plus;
    MatrixMultiplication<uint, MinPlus<uint>, 4> matrix_mult3(min_plus);
    Matrix<uint,4,4> shortest_paths = power_monoid(graph2, 3, matrix_mult3);
    cout << graph2 << "^3 = " << shortest_paths << endl;

    return 0;
}
