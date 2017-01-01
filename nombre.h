#pragma once

#include <iostream>
#include <gmp.h>

#include <boost/optional.hpp>
#include <limits>

class nombre
{
    mpz_t data;
    
    template <typename Type>
    void set(Type op, std::false_type /*is_signed*/)
    {
        mpz_import (data, 1, -1, sizeof op, 0, 0, &op);
    }
    
    template <typename Type>
    void set(Type op, std::true_type /*is_signed*/)
    {
        bool negatif = (op < 0);
        op = std::abs(op);
        mpz_import (data, 1, -1, sizeof op, 0, 0, &op);
        if (negatif) negation();
    }
    
    template <typename Type>
    Type get(std::false_type /*is_signed*/) const
    {
        Type result = 0;
        mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
        return result;
    }
    
    template <typename Type>
    Type get(std::true_type /*is_signed*/) const
    {
        Type result = 0;
        mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
        return signe() * result;
    }
    
public:
    nombre();
    nombre(const mpz_t & op);
    nombre(const nombre & op);
    
    nombre(unsigned int op);
    nombre(signed int op);
    nombre(unsigned long op);
    nombre(signed long op);
    nombre(double op);
    nombre(const std::string & op, int base = 10);
    nombre(unsigned long long op);
    nombre(signed long long op);
    nombre(long double op);
    virtual ~nombre();
    
    void set(const mpz_t & op);
    void set(const nombre & op);
    void set(unsigned long op);
    void set(signed long op);
    void set(unsigned int op);
    void set(signed int op);
    void set(double op);
    void set(const std::string & op, int base = 10);
    
    template <typename T>
    void set(T x) 
    {
        static_assert(std::is_integral<T>::value, "Integer required.");
        set(x, std::is_signed<T>());
    }
    
    void set(long double op);
    
    unsigned long get_unsigned_long() const;
    signed long get_signed_long() const;
    double get_double() const;
    unsigned long long get_unsigned_long_long() const;
    
    template <typename T>
    T get() const 
    {
        static_assert(std::is_integral<T>::value, "Integer required.");
        return get(std::is_signed<T>());
    }
    
    signed short signe() const;

    int compare(const nombre & op) const;
    int compare(double op) const;
    int compare(signed long int op) const;
    int compare(unsigned long int op) const;

    template<typename T>
    int compare(const T & op) const
    {
        nombre n(op);
        return compare(n);
    }
    
    template<typename T>
    bool operator ==(const T & b) const { return compare(b) == 0; }
    
    template<typename T>
    bool operator !=(const T & b) const { return compare(b) != 0; }
    
    template<typename T>
    bool operator <(const T & b) const { return compare(b) < 0; }
    
    template<typename T>
    bool operator >(const T & b) const { return compare(b) > 0; }
    
    template<typename T>
    bool operator <=(const T & b) const { return compare(b) < 1; }
    
    template<typename T>
    bool operator >=(const T & b) const { return compare(b) > -1; }
    
    void swap(nombre & op);
    const std::string to_string(int base = 10) const;
    
    nombre & addition(const nombre & op);
    nombre & addition(unsigned long int op);

    template<typename T>
    nombre & addition(const T & op)
    {
        nombre tmp(op);
        addition(tmp);
        return *this;
    }
    
    nombre & soustraction(const nombre & op);
    nombre & soustraction(unsigned long int op);
    
    template<typename T>
    nombre & soustraction(const T & op)
    {
        nombre tmp(op);
        soustraction(tmp);
        return *this;
    }
    
    nombre & multiplication(const nombre & op);
    nombre & multiplication(unsigned long int op);
    nombre & multiplication(signed long int op);

    template<typename T>
    nombre & multiplication(const T & op)
    {
        nombre tmp(op);
        multiplication(tmp);
        return *this;
    }
    
    nombre & division(const nombre & op);
    nombre & division(unsigned long int op);
    
    template<typename T>
    nombre & division(const T & op)
    {
        nombre tmp(op);
        division(tmp);
        return *this;
    }
    
    nombre & modulo(const nombre & op);
    nombre & modulo(unsigned long int op);

    template<typename T>
    nombre & modulo(const T & op)
    {
        nombre tmp(op);
        modulo(tmp);
        return *this;
    }
    
    bool divisible(const nombre & op) const;
    bool divisible(unsigned long int op) const;
    
    template<typename T>
    bool divisible(const T & op) const
    {
        nombre tmp(op);
        return divisible(tmp);
    }
    
    static nombre addition(const nombre & op1, const nombre & op2)
    {
        nombre n;
        mpz_add(n.data, op1.data, op2.data);
        return n;
    }
    
    static nombre addition(const nombre & op1, unsigned long int op2)
    {
        nombre n;
        mpz_add_ui(n.data, op1.data, op2);
        return n;
    }
    
    static nombre addition(unsigned long int op1, const nombre & op2)
    {
        nombre n;
        mpz_add_ui(n.data, op2.data, op1);
        return n;
    }
    
    template<typename T>
    static nombre addition(const nombre & op1, const T & op2)
    {
        nombre tmp(op2);
        return addition(op1, tmp);
    }
    
    template<typename T>
    static nombre addition(const T & op1, const nombre & op2)
    {
        nombre tmp(op1);
        return addition(tmp, op2);
    }
    
    static nombre soustraction(const nombre & op1, const nombre & op2)
    {
        nombre n;
        mpz_sub(n.data, op1.data, op2.data);
        return n;
    }
    
    static nombre soustraction(const nombre & op1, unsigned long int op2)
    {
        nombre n;
        mpz_sub_ui(n.data, op1.data, op2);
        return n;
    }
    
    static nombre soustraction(unsigned long int op1, const nombre & op2)
    {
        nombre n;
        mpz_ui_sub(n.data, op1, op2.data);
        return n;
    }
    
    template<typename T>
    static nombre soustraction(const nombre & op1, const T & op2)
    {
        nombre tmp(op2);
        return soustraction(op1, tmp);
    }
    
    template<typename T>
    static nombre soustraction(const T & op1, const nombre & op2)
    {
        nombre tmp(op1);
        return soustraction(tmp, op2);
    }
    
    static nombre multiplication(const nombre & op1, const nombre & op2)
    {
        nombre n;
        mpz_mul(n.data, op1.data, op2.data);
        return n;
    }
    
    static nombre multiplication(const nombre & op1, unsigned long int op2)
    {
        nombre n;
        mpz_mul_ui(n.data, op1.data, op2);
        return n;
    }
    
    static nombre multiplication(unsigned long int op1, const nombre & op2)
    {
        nombre n;
        mpz_mul_ui(n.data, op2.data, op1);
        return n;
    }
    
    static nombre multiplication(const nombre & op1, signed long int op2)
    {
        nombre n;
        mpz_mul_si(n.data, op1.data, op2);
        return n;
    }
    
    static nombre multiplication(signed long int op1, const nombre & op2)
    {
        nombre n;
        mpz_mul_si(n.data, op2.data, op1);
        return n;
    }
    
    template<typename T>
    static nombre multiplication(const nombre & op1, const T & op2)
    {
        nombre tmp(op2);
        return multiplication(op1, tmp);
    }
    
    template<typename T>
    static nombre multiplication(const T & op1, const nombre & op2)
    {
        nombre tmp(op1);
        return multiplication(tmp, op2);
    }
    
    static nombre division(const nombre & op1, const nombre & op2)
    {
        nombre n;
        mpz_fdiv_q(n.data, op1.data, op2.data);
        return n;
    }
    
    static nombre division(const nombre & op1, unsigned long int op2)
    {
        nombre n;
        mpz_fdiv_q_ui(n.data, op1.data, op2);
        return n;
    }
    
    template<typename T>
    static nombre division(const nombre & op1, const T & op2)
    {
        nombre tmp(op2);
        return division(op1, tmp);
    }
    
    template<typename T>
    static nombre division(const T & op1, const nombre & op2)
    {
        nombre tmp(op1);
        return division(tmp, op2);
    }
    
    static nombre modulo(const nombre & op1, const nombre & op2)
    {
        nombre n;
        mpz_mod(n.data, op1.data, op2.data);
        return n;
    }
    
    static nombre modulo(const nombre & op1, unsigned long int op2)
    {
        nombre n;
        mpz_mod_ui(n.data, op1.data, op2);
        return n;
    }
    
    template<typename T>
    static nombre modulo(const nombre & op1, const T & op2)
    {
        nombre tmp(op2);
        return modulo(op1, tmp);
    }
    
    template<typename T>
    static nombre modulo(const T & op1, const nombre & op2)
    {
        nombre tmp(op1);
        return modulo(tmp, op2);
    }
    
    static bool divise(const nombre & op1, const nombre & op2)
    {
        return op1.divisible(op2);
    }
    
    static bool divise(const nombre & op1, unsigned long int op2)
    {
        return op1.divisible(op2);
    }
    
    template<typename T>
    static bool divise(const T & op1, const nombre & op2)
    {
        nombre tmp(op1);
        return tmp.divisible(op2);
    }
    
    template<typename T>
    static bool divise(const nombre & op1, const T & op2)
    {
        nombre tmp(op2);
        return op1.divisible(tmp);
    }
    
    void negation()
    {
        mpz_neg(data, data);
    }
    
    nombre operator-() const
    {
        nombre resultat;
        mpz_neg(resultat.data, data);
        return resultat;
    }
    
    void abs()
    {
        mpz_abs(data, data);
    }
    
    static nombre abs(const nombre & op)
    {
        nombre resultat;
        mpz_abs(resultat.data, op.data);
        return resultat;
    }
    
    nombre& operator=(const nombre & op)
    {
        set(op);
        return *this;
    }

    template<typename T> nombre& operator=(const T & op)
    {
        set(op);
        return *this;
    }
    
    nombre& operator+=(const nombre & op)
    {
        addition(op);
        return *this;
    }

    template<typename T> nombre& operator+=(const T & op)
    {
        addition(op);
        return *this;
    }
    
    nombre& operator-=(const nombre & op)
    {
        soustraction(op);
        return *this;
    }

    template<typename T> nombre& operator-=(const T & op)
    {
        soustraction(op);
        return *this;
    }
    
    nombre& operator*=(const nombre & op)
    {
        multiplication(op);
        return *this;
    }

    template<typename T> nombre& operator*=(const T & op)
    {
        multiplication(op);
        return *this;
    }
    
    nombre& operator/=(const nombre & op)
    {
        division(op);
        return *this;
    }

    template<typename T> nombre& operator/=(const T & op)
    {
        division(op);
        return *this;
    }
    
    nombre& operator%=(const nombre & op)
    {
        modulo(op);
        return *this;
    }

    template<typename T> nombre& operator%=(const T & op)
    {
        modulo(op);
        return *this;
    }
    
    nombre operator<<(const unsigned long & b) const
    {
        nombre resultat;
        mpz_mul_2exp(resultat.data, data, b);
        return resultat;
    }
    
    nombre operator>>(const unsigned long & b) const
    {
        nombre resultat;
        mpz_fdiv_q_2exp(resultat.data, data, b);
        return resultat;
    }
    
    static nombre puissance(const nombre & base, unsigned long exposant)
    {
        nombre resultat;
        mpz_pow_ui(resultat.data, base.data, exposant);
        return resultat;
    }
    
    static nombre puissance(unsigned long base, unsigned long exposant)
    {
        nombre resultat;
        mpz_ui_pow_ui(resultat.data, base, exposant);
        return resultat;
    }
    
    nombre & puissance(unsigned long exposant)
    {
        mpz_pow_ui(data, data, exposant);
        return *this;
    }
    
    static nombre puissance_modulaire(const nombre & base, unsigned long exposant, const nombre & modulo)
    {
        nombre resultat;
        mpz_powm_ui(resultat.data, base.data, exposant, modulo.data);
        return resultat;
    }
    
    nombre & puissance_modulaire(unsigned long exposant, const nombre & modulo)
    {
        mpz_powm_ui(data, data, exposant, modulo.data);
        return *this;
    }
    
    nombre & puissance_modulaire(const nombre & exposant, const nombre & modulo)
    {
        mpz_powm(data, data, exposant.data, modulo.data);
        return *this;
    }
    
    template<typename T>
    static nombre puissance_modulaire(const nombre & base, unsigned long exposant, const T & modulo)
    {
        nombre tmp_modulo(modulo);
        return puissance_modulaire(base, exposant, tmp_modulo);
    }
    
    template<typename T>
    nombre & puissance_modulaire(unsigned long exposant, const T & modulo)
    {
        nombre tmp_modulo(modulo);
        return puissance_modulaire(exposant, tmp_modulo);
    }
    
    template<typename T>
    nombre & puissance_modulaire(const nombre & exposant, const T & modulo)
    {
        nombre tmp_modulo(modulo);
        return puissance_modulaire(exposant, tmp_modulo);
    }
    
    static nombre racine(const nombre & op, unsigned long int n)
    {
        nombre resultat;
        mpz_root(resultat.data, op.data, n);
        return resultat;
    }
    
    static nombre racine_carre(const nombre & op)
    {
        nombre resultat;
        mpz_sqrt(resultat.data, op.data);
        return resultat;
    }
    
    static bool carre_parfait(const nombre & op)
    {
        return mpz_perfect_square_p(op.data) != 0;
    }
    
    nombre racine(unsigned long int n) const
    {
        nombre resultat;
        mpz_root(resultat.data, data, n);
        return resultat;
    }
    
    nombre racine_carre() const
    {
        nombre resultat;
        mpz_sqrt(resultat.data, data);
        return resultat;
    }
    
    bool carre_parfait() const
    {
        return mpz_perfect_square_p(data) != 0;
    }
    
    bool premier(int probabilite = 25) const
    {
        return mpz_probab_prime_p(data, probabilite) != 0;
    }

    template <typename T>
    static bool premier(const T & n, int probabilite = 25)
    {
        nombre tmp(n);
        return tmp.premier(probabilite);
    }
    
    nombre premier_suivant() const
    {
        nombre resultat;
        mpz_nextprime(resultat.data, data);
        return resultat;
    }
    
    static nombre PGCD(const nombre & op1, const nombre & op2)
    {
        nombre resultat;
        mpz_gcd(resultat.data, op1.data, op2.data);
        return resultat;
    }
    
    static nombre PGCD(const nombre & op1, unsigned long int op2)
    {
        nombre resultat;
        mpz_gcd_ui(resultat.data, op1.data, op2);
        return resultat;
    }
    
    template<typename T>
    static nombre PGCD(const nombre & op1, const T & op2)
    {
        nombre n2(op2);
        return PGCD(op1, n2);
    }
    
    template<typename T>
    static nombre PGCD(const T & op1, const nombre & op2)
    {
        return PGCD(op2, op1);
    }

    static nombre PPCM(const nombre & op1, const nombre & op2)
    {
        nombre resultat;
        mpz_lcm(resultat.data, op1.data, op2.data);
        return resultat;
    }
    
    static nombre PPCM(const nombre & op1, unsigned long int op2)
    {
        nombre resultat;
        mpz_lcm_ui(resultat.data, op1.data, op2);
        return resultat;
    }
    
    template<typename T>
    static nombre PPCM(const nombre & op1, const T & op2)
    {
        nombre n2(op2);
        return PPCM(op1, n2);
    }
    
    template<typename T>
    static nombre PPCM(const T & op1, const nombre & op2)
    {
        return PPCM(op2, op1);
    }

    boost::optional<nombre> inverse_modulaire(const nombre & modulo) const
    {
        nombre resultat;
        if (mpz_invert(resultat.data, data, modulo.data) != 0)
            return resultat;
        
        return boost::none;
    }
    
    static boost::optional<nombre> inverse_modulaire(const nombre & op, const nombre & modulo)
    {
        return op.inverse_modulaire(modulo);
    }
    
    nombre & operator++()
    {
        return addition(1);
    }
    
    nombre & operator--()
    {
        return soustraction(1);
    }
    
    nombre operator++(int)
    {
        nombre copie(data);
        addition(1);
        return copie;
    }
    
    nombre operator--(int)
    {
        nombre copie(data);
        soustraction(1);
        return copie;
    }
    
    nombre operator~() const
    {
        nombre r;
        mpz_com(r.data, data);
        return r;
    }
    
    nombre & operator &=(const nombre & n)
    {
        mpz_and(data, data, n.data);
        return *this;
    }
    
    template<typename T>
    nombre & operator &=(const T & op)
    {
        nombre n(op);
        mpz_and(data, data, n.data);
        return *this;
    }
    
    nombre & operator |=(const nombre & n)
    {
        mpz_ior(data, data, n.data);
        return *this;
    }
    
    template<typename T>
    nombre & operator |=(const T & op)
    {
        nombre n(op);
        mpz_ior(data, data, n.data);
        return *this;
    }
    
    nombre & operator ^=(const nombre & n)
    {
        mpz_xor(data, data, n.data);
        return *this;
    }
    
    template<typename T>
    nombre & operator ^=(const T & op)
    {
        nombre n(op);
        mpz_xor(data, data, n.data);
        return *this;
    }
    
    static nombre coefficient_binomial(const nombre & n, unsigned long int k)
    {
        nombre resultat;
        mpz_bin_ui (resultat.data, n.data, k);
        return resultat;
    }
    
    static nombre coefficient_binomial(unsigned long int n, unsigned long int k)
    {
        nombre resultat;
        mpz_bin_uiui (resultat.data, n, k);
        return resultat;
    }

    static nombre factorielle(unsigned long int n)
    {
        nombre resultat;
        mpz_fac_ui (resultat.data, n);
        return resultat;
    }
};

template<typename T>
inline nombre operator+(const T & op1, const nombre & op2)
{
    return nombre::addition(op1, op2);
}

template<typename T>
inline nombre operator-(const T & op1, const nombre & op2)
{
    return nombre::soustraction(op1, op2);
}

template<typename T>
inline nombre operator*(const T & op1, const nombre & op2)
{
    return nombre::multiplication(op1, op2);
}

template<typename T>
inline nombre operator/(const T & op1, const nombre & op2)
{
    return nombre::division(op1, op2);
}

template<typename T>
inline nombre operator%(const T & op1, const nombre & op2)
{
    return nombre::modulo(op1, op2);
}

template<typename T>
inline nombre operator&(const T & a, const nombre & b)
{
    nombre resultat(a);
    resultat &= b;
    return resultat;
}

template<typename T>
inline nombre operator|(const T & a, const nombre & b)
{
    nombre resultat(a);
    resultat |= b;
    return resultat;
}

template<typename T>
inline nombre operator^(const T & a, const nombre & b)
{
    nombre resultat(a);
    resultat ^= b;
    return resultat;
}

namespace std
{
    nombre abs(const nombre & op);
    
    void swap(nombre & op1, nombre & op2);
    
    nombre sqrt(const nombre & op);
    
    nombre cbrt(const nombre & op);
    
    std::ostream& operator<<(std::ostream& os, const nombre & op);
    
    std::istream& operator>>(std::istream& is, nombre & op);

    template<>
    class numeric_limits<nombre> : public numeric_limits<long long>
    {
    public:
        static constexpr int digits = INT_MAX;
        static constexpr int digits10 = INT_MAX;

        static nombre min()
        {
            return -max();
        }

        static nombre max()
        {
            return nombre::puissance(2, digits);
        }

        static nombre lowest()
        {
            return min();
        }
    };
}
