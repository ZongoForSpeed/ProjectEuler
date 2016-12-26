#include "problemes.h"

#include <iostream>
#include <cstdlib>

typedef unsigned long long nombre;

namespace
{
    template<nombre p>
    class Number
    {
    public:
        Number(nombre n) : _value(n >= 0 ? n % p : p + n % p) {}
        nombre value() const { return _value; }
    
        Number<p> &operator+=(const Number<p> &b) { _value += b._value; if (_value >= p) _value -= p; return *this; }
        Number<p> &operator-=(const Number<p> &b) { _value = _value < b._value ? p + _value - b._value : _value - b._value; return *this; }
        Number<p> &operator*=(const Number<p> &b) { unsigned long long int c = _value; c *= b._value; _value = c % p; return *this; }
        Number<p> &operator/=(const Number<p> &b) { return operator*=(power(b, p - 2)); }
    private:
        nombre _value;
    };
    
    template<nombre p>
    std::ostream &operator<<(std::ostream& os, const Number<p> &a)
    {
        os << a.value();
        return os;
    }
    
    template<nombre p>
    Number<p> power(Number<p> a, unsigned n)
    {
        Number<p> result(1);
        while (n>0)
        {
            if (n % 2)
                result *= a;
            a *= a;
            n /= 2;
        }
        return result;
    }
    
    template<nombre p>
    Number<p> operator-(const Number<p>& a)
    {
        return Number<p>(p - a.value());
    }
    
    template<nombre p>
    Number<p> operator+(const Number<p>& a, const Number<p>&b)
    {
        Number<p> c(a);
        c += b;
        return c;
    }
    
    template<nombre p>
    Number<p> operator-(const Number<p>& a, const Number<p>&b)
    {
        Number<p> c(a);
        c -= b;
        return c;
    }
    
    template<nombre p>
    Number<p> operator*(const Number<p>& a, const Number<p>&b)
    {
        Number<p> c(a);
        c *= b;
        return c;
    }
    
    template<nombre p>
    Number<p> operator/(const Number<p>& a, const Number<p>&b)
    {
        Number<p> c(a);
        c /= b;
        return c;
    }
    
    template<nombre p>
    std::pair<unsigned long long int, Number<p> > internalFact(unsigned long long int n)
    {
        Number<p> resultat = 1;
        unsigned long long int pow = 0;
        bool sgn = false;
        while (n > 0)
        {
            for (unsigned int i = n % p; i > 1; --i)
                resultat *= i;
            n /= p;
            sgn ^= (n % 2 == 1);
            pow += n;
        }
        return std::make_pair(pow, sgn ? -resultat : resultat);
    }
    
    template<unsigned int p>
    Number<p> fact(unsigned long long int n)
    {
        return internalFact<p>(n).second;
    }
    
    template<unsigned int p>
    Number<p> A(unsigned long long int n, unsigned long long int k)
    {
        return fact<p>(n) / fact<p>(n-k);
    }
    
    template<unsigned int p>
    Number<p> binomial(unsigned long long int n, unsigned long long int k)
    {
        auto fn = internalFact<p>(n);
        auto fk = internalFact<p>(k);
        auto fnk = internalFact<p>(n-k);
        if (fn.first - fk.first - fnk.first > 0)
            return Number<p>(0);
        return fn.second / (fk.second * fnk.second);
    }
    
    
    template<nombre p>
    class Probleme498
    {
        unsigned long long n;
        unsigned long long m;
        unsigned long long d;
    
    public:
        Probleme498(const unsigned long long & _n, const unsigned long long & _m, const unsigned long long & _d) : n(_n), m(_m), d(_d) {}
    
        nombre algorithme()
        {
            nombre i = d;
            Number<p> resultat(0);
            while (i < m)
            {
                nombre j = i;
                Number<p> u = 0;
                Number<p> s = 0;
                bool first = true;
                while (j < m)
                {
                    if (first)
                    {
                        u = binomial<p>(n, j) * binomial<p>(j, d);
                        // std::cout << "u_" << j << " = " << u << std::endl;
                        if (j%2 == 0)
                            u = - u;
                        first = false;
                    }
                    else if ((n - j + 1)%p == 0)
                        break;
                    else
                    {
                        u *= n - j + 1;
                        u /= j - d;
                        u = -u;
                    }
                    ++j;
                    s += u;
                }
                // std::cout << "s_" << j << " = " << s << std::endl;
                resultat += s;
                i += p;
            }
            
            return resultat.value();
        }
    };
}

ENREGISTRER_PROBLEME(498, "Remainder of polynomial division")
{
    // For positive integers n and m, we define two polynomials F_n(x) = x^n and G_m(x) = (x-1)^m.
    // We also define a polynomial Rn,m(x) as the remainder of the division of F_n(x) by G_m(x).
    // For example, R_6,3(x) = 15x² - 24x + 10.
    //
    // Let C(n, m, d) be the absolute value of the coefficient of the d-th degree term of R_n,m(x).
    // We can verify that C(6, 3, 1) = 24 and C(100, 10, 4) = 227197811615775.
    //
    // Find C(10^13, 10^12, 10^4) mod 999999937.
    Probleme498<999999937> p(10000000000000LL, 1000000000000LL, 10000);
    return std::to_string(p.algorithme());
}
