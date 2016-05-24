#include "arithmetiques.h"

namespace arithmetiques
{
    template<>
    boost::multiprecision::mpz_int PGCD<>(boost::multiprecision::mpz_int a, boost::multiprecision::mpz_int b)
    {
        boost::multiprecision::mpz_int resultat;
        mpz_gcd(resultat.backend().data(), a.backend().data(), b.backend().data());
        return resultat;
    }
    
    template<>
    boost::multiprecision::mpz_int PPCM<>(boost::multiprecision::mpz_int a, boost::multiprecision::mpz_int b)
    {
        boost::multiprecision::mpz_int resultat;
        mpz_lcm(resultat.backend().data(), a.backend().data(), b.backend().data());
        return resultat;
    }
    
    template<>
    void Bezout<>(boost::multiprecision::mpz_int a, 
                  boost::multiprecision::mpz_int b, 
                  boost::multiprecision::mpz_int& x, 
                  boost::multiprecision::mpz_int& y)
    {
        boost::multiprecision::mpz_int g = 1;    
        mpz_gcdext (g.backend().data(), x.backend().data(), y.backend().data(), a.backend().data(), b.backend().data());   
    }
    
    template<>
    boost::multiprecision::mpz_int inverse_modulaire<>(boost::multiprecision::mpz_int a, boost::multiprecision::mpz_int n)
    {
        boost::multiprecision::mpz_int resultat;
        mpz_invert(resultat.backend().data(), a.backend().data(), n.backend().data());
        return resultat;
    }
}
