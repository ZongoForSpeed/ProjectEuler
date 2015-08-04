#pragma once

class Bezout {
public:
    Bezout(unsigned int a, unsigned int b);
    unsigned int pgcd() const { return _pgcd; }
    int u() const { return _u; }
    int v() const { return _v; }
private:
    int _u, _v;
    unsigned int _pgcd;
};

unsigned int inverse_mod(unsigned int a, unsigned int n);
int chinois(unsigned int a, unsigned int n, unsigned int b, unsigned int m);
