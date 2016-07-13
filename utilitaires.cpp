#include "utilitaires.h"
#include <boost/multiprecision/gmp.hpp>

namespace std
{
    long double sqrt(boost::multiprecision::mpz_int n)
    {
        return std::sqrt(n.convert_to<long double>());

        assert(false);
        return 1.0;
    }
    
    std::string to_string(const boost::multiprecision::mpz_int & n)
    {
        std::ostringstream oss;
        oss << n;
        return oss.str();
    }
}

template<>
boost::multiprecision::mpz_int racine_carre<boost::multiprecision::mpz_int>(boost::multiprecision::mpz_int n)
{
	boost::multiprecision::mpz_int resultat;
	mpz_sqrt(resultat.backend().data(), n.backend().data());
	return resultat;
}

long double operator+(const boost::multiprecision::mpz_int & n, const long double d)
{
    return n.convert_to<long double>() + d;
}

long double operator+(const long double d, const boost::multiprecision::mpz_int & n)
{
    return d + n.convert_to<long double>();
}

long double operator-(const boost::multiprecision::mpz_int & n, const long double d)
{
    return n.convert_to<long double>() - d;
}

long double operator-(const long double d, const boost::multiprecision::mpz_int & n)
{
    return d - n.convert_to<long double>();
}

long double operator/(const boost::multiprecision::mpz_int & n, const long double d)
{
    return n.convert_to<long double>() / d;
}

long double operator/(const long double d, const boost::multiprecision::mpz_int & n)
{
    return d / n.convert_to<long double>();
}

long double operator*(const boost::multiprecision::mpz_int & n, const long double d)
{
    return n.convert_to<long double>() * d;
}

long double operator*(const long double d, const boost::multiprecision::mpz_int & n)
{
    return d * n.convert_to<long double>();
}

