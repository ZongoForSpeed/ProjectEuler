#include "Bezout.h"
#include <cstdlib>
#include <cassert>

Bezout::Bezout(unsigned int a, unsigned int b) 
{
    _u = 1;
    _v = 0;

    int next_u = 0;
    int next_v = 1;

    while (b != 0) {
        unsigned int temp = b;
        unsigned int q = a / b;
        b = a % temp;
        a = temp;

        temp = _u;
        _u = next_u;
        next_u = temp - q * next_u;
        temp = _v;
        _v = next_v;
        next_v = temp - q * next_v;
    }
    _pgcd = a;
}

unsigned int inverse_mod(unsigned int a, unsigned int n) 
{
    Bezout bezout(a, n);
    assert(bezout.pgcd() == 1);
    return  (bezout.u() < 0 ? bezout.u() + n : bezout.u()) % n;
}

int chinois(unsigned int a, unsigned int n, unsigned int b, unsigned int m) 
{
    Bezout bezout(n, m);
    assert(bezout.pgcd() == 1);
    return (b * bezout.u() * n + a * bezout.v() * m) % (m*n);
}
