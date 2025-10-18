#pragma once

namespace combinatoire {
    unsigned int coefficient_binomial_u(unsigned int n, unsigned int p);

    unsigned long coefficient_binomial_ul(unsigned long n, unsigned long p);

    unsigned long long coefficient_binomial_ull(unsigned long long n, unsigned long long p);

    unsigned int coefficient_binomial_u(unsigned int n, unsigned int p, unsigned int modulo);

    unsigned long coefficient_binomial_ul(unsigned long n, unsigned long p, unsigned long modulo);

    unsigned long long coefficient_binomial_ull(unsigned long long n, unsigned long long p,
                                                      unsigned long long modulo);

    unsigned int arrangement_u(unsigned int n, unsigned int p);

    unsigned long arrangement_ul(unsigned long n, unsigned long p);

    unsigned long long arrangement_ull(unsigned long long n, unsigned long long p);

    unsigned int catalan_u(unsigned int n);

    unsigned long catalan_ul(unsigned long n);

    unsigned long long catalan_ull(unsigned long long n);

    unsigned int factorielle_u(unsigned int n);

    unsigned long factorielle_ul(unsigned long n);

    unsigned long long factorielle_ull(unsigned long long n);

}
