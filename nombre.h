#pragma once

#include <iostream>
#include <gmp.h>

#include <boost/optional.hpp>

class Nombre
{
    mpz_t data;
    
    template <typename T>
    void set(T op, std::false_type /*is_signed*/) 
    {
        mpz_import (data, 1, -1, sizeof op, 0, 0, &op);
    }
    
    template <typename T>
    void set(T op, std::true_type /*is_signed*/)
    {
        bool negatif = (op < 0);
        op = std::abs(op);
        mpz_import (data, 1, -1, sizeof op, 0, 0, &op);
        if (negatif) negation();
    }
    
    template <typename T>
    T get(std::false_type /*is_signed*/) const
    {
        T result = 0;
        mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
        return result;
    }
    
    template <typename T>
    T get(std::true_type /*is_signed*/) const
    {
        T result = 0;
        mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
        return signe() * result;
    }
    
public:
    Nombre();
    Nombre(const mpz_t & op);
    Nombre(const Nombre & op);
    
    explicit Nombre(unsigned int op);
    explicit Nombre(signed int op);
    explicit Nombre(unsigned long op);
    explicit Nombre(signed long op);
    explicit Nombre(double op);
    explicit Nombre(const std::string & op, int base = 10);
    explicit Nombre(unsigned long long op);
    explicit Nombre(signed long long op);
    explicit Nombre(long double op);
    virtual ~Nombre();
    
    void set(const mpz_t & op);
    void set(const Nombre & op);
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
    
    // void set(unsigned long long op)
    // {
    //     mpz_import (data, 1, -1, sizeof op, 0, 0, &op);
    // }
    
    // void set(signed long long op)
    // {
    //     bool negatif = (op < 0);
    //     op = std::abs(op);
    //     mpz_import (data, 1, -1, sizeof op, 0, 0, &op);
    //     if (negatif) negation();
    // }
    
    void set(long double op);
    
    unsigned long get_unsigned_long() const 
    {
        return mpz_get_ui(data);
    }
    
    signed long get_signed_long() const
    {
        return mpz_get_si(data);
    }
    
    double get_double() const
    {
        return mpz_get_d(data);
    }
    
    unsigned long long get_unsigned_long_long() const
    {
        unsigned long long result = 0;
        mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
        return result;
    }
    
    template <typename T>
    T get() const 
    {
        static_assert(std::is_integral<T>::value, "Integer required.");
        return get(std::is_signed<T>());
    }
    
    signed short signe() const
    {
        return mpz_sgn (data);
    }
    
    int compare(const Nombre & op) const
    {
        return mpz_cmp(data, op.data);
    }
    
    int compare(double op) const
    {
        return mpz_cmp_d(data, op);
    }
    
    int compare(signed long int op) const 
    {
        return mpz_cmp_si(data, op);
    }
    
    int compare(unsigned long int op) const
    {
        return mpz_cmp_ui(data, op);
    }
    
    template<typename T>
    int compare(const T & op) const
    {
        Nombre n(op);
        return compare(n);
    }
    
    template<typename T>
    static int compare(const Nombre & op1, const T & op2)
    {
        return op1.compare(op2);
    }
    
    template<typename T>
    static int compare(const T & op1, const Nombre & op2)
    {
        return -op2.compare(op1);
    }
    
    template<typename T>
    bool operator ==(const T & b) const
    {
        return compare(b) == 0;
    }
    
    template<typename T>
    bool operator !=(const T & b) const
    {
        return compare(b) != 0;
    }
    
    template<typename T>
    bool operator <(const T & b) const
    {
        return compare(b) < 0;
    }
    
    template<typename T>
    bool operator >(const T & b) const
    {
        return compare(b) > 0;
    }
    
    template<typename T>
    bool operator <=(const T & b) const
    {
        return compare(b) < 1;
    }
    
    template<typename T>
    bool operator >=(const T & b) const
    {
        return compare(b) > -1;
    }
    
    void swap(Nombre & op)
    {
        mpz_swap(data, op.data);
    }
    
    const std::string get_string(int base = 10) const
    {
        // std::string resultat (mpz_sizeinbase(data, base) + 2, 0);
        // mpz_get_str(&resultat[0], base, data);
        // resultat.shrink_to_fit();
        char * str = mpz_get_str(NULL, base, data);
        std::string resultat(str);
        free(str);
        return resultat;
    }
    
    Nombre & addition(const Nombre & op)
    {
        mpz_add(data, data, op.data);
        return *this;
    }
    
    Nombre & addition(unsigned long int op)
    {
        mpz_add_ui(data, data, op);
        return *this;
    }
    
    template<typename T>
    Nombre & addition(const T & op)
    {
        Nombre tmp(op);
        addition(tmp);
        return *this;
    }
    
    Nombre & soustraction(const Nombre & op)
    {
        mpz_sub(data, data, op.data);
        return *this;
    }
    
    Nombre & soustraction(unsigned long int op)
    {
        mpz_sub_ui(data, data, op);
        return *this;
    }
    
    template<typename T>
    Nombre & soustraction(const T & op)
    {
        Nombre tmp(op);
        soustraction(tmp);
        return *this;
    }
    
    Nombre & multiplication(const Nombre & op)
    {
        mpz_mul(data, data, op.data);
        return *this;
    }
    
    Nombre & multiplication(unsigned long int op)
    {
        mpz_mul_ui(data, data, op);
        return *this;
    }
    
    Nombre & multiplication(signed long int op)
    {
        mpz_mul_si(data, data, op);
        return *this;
    }
    
    template<typename T>
    Nombre & multiplication(const T & op)
    {
        Nombre tmp(op);
        multiplication(tmp);
        return *this;
    }
    
    Nombre & division(const Nombre & op)
    {
        mpz_fdiv_q (data, data, op.data);
        return *this;
    }
    
    Nombre & division(unsigned long int op)
    {
        mpz_fdiv_q_ui (data, data, op);
        return *this;
    }
    
    template<typename T>
    Nombre & division(const T & op)
    {
        Nombre tmp(op);
        division(tmp);
        return *this;
    }
    
    Nombre & modulo(const Nombre & op)
    {
        mpz_mod (data, data, op.data);
        return *this;
    }
    
    Nombre & modulo(unsigned long int op)
    {
        mpz_mod_ui (data, data, op);
        return *this;
    }
    
    template<typename T>
    Nombre & modulo(const T & op)
    {
        Nombre tmp(op);
        modulo(tmp);
        return *this;
    }
    
    bool divisible(const Nombre & op) const
    {
        return mpz_divisible_p(data, op.data) != 0;
    }
    
    bool divisible(unsigned long int op) const
    {
        return mpz_divisible_ui_p(data, op) != 0;
    }
    
    template<typename T>
    bool divisible(const Nombre & op) const
    {
        Nombre tmp(op);
        return divisible(tmp);
    }
    
    static Nombre addition(const Nombre & op1, const Nombre & op2)
    {
        Nombre n;
        mpz_add(n.data, op1.data, op2.data);
        return n;
    }
    
    static Nombre addition(const Nombre & op1, unsigned long int op2)
    {
        Nombre n;
        mpz_add_ui(n.data, op1.data, op2);
        return n;
    }
    
    static Nombre addition(unsigned long int op1, const Nombre & op2)
    {
        Nombre n;
        mpz_add_ui(n.data, op2.data, op1);
        return n;
    }
    
    template<typename T>
    static Nombre addition(const Nombre & op1, const T & op2)
    {
        Nombre tmp(op2);
        return addition(op1, tmp);
    }
    
    template<typename T>
    static Nombre addition(const T & op1, const Nombre & op2)
    {
        Nombre tmp(op1);
        return addition(tmp, op2);
    }
    
    static Nombre soustraction(const Nombre & op1, const Nombre & op2)
    {
        Nombre n;
        mpz_sub(n.data, op1.data, op2.data);
        return n;
    }
    
    static Nombre soustraction(const Nombre & op1, unsigned long int op2)
    {
        Nombre n;
        mpz_sub_ui(n.data, op1.data, op2);
        return n;
    }
    
    static Nombre soustraction(unsigned long int op1, const Nombre & op2)
    {
        Nombre n;
        mpz_ui_sub(n.data, op1, op2.data);
        return n;
    }
    
    template<typename T>
    static Nombre soustraction(const Nombre & op1, const T & op2)
    {
        Nombre tmp(op2);
        return soustraction(op1, tmp);
    }
    
    template<typename T>
    static Nombre soustraction(const T & op1, const Nombre & op2)
    {
        Nombre tmp(op1);
        return soustraction(tmp, op2);
    }
    
    static Nombre multiplication(const Nombre & op1, const Nombre & op2)
    {
        Nombre n;
        mpz_mul(n.data, op1.data, op2.data);
        return n;
    }
    
    static Nombre multiplication(const Nombre & op1, unsigned long int op2)
    {
        Nombre n;
        mpz_mul_ui(n.data, op1.data, op2);
        return n;
    }
    
    static Nombre multiplication(unsigned long int op1, const Nombre & op2)
    {
        Nombre n;
        mpz_mul_ui(n.data, op2.data, op1);
        return n;
    }
    
    static Nombre multiplication(const Nombre & op1, signed long int op2)
    {
        Nombre n;
        mpz_mul_si(n.data, op1.data, op2);
        return n;
    }
    
    static Nombre multiplication(signed long int op1, const Nombre & op2)
    {
        Nombre n;
        mpz_mul_si(n.data, op2.data, op1);
        return n;
    }
    
    template<typename T>
    static Nombre multiplication(const Nombre & op1, const T & op2)
    {
        Nombre tmp(op2);
        return multiplication(op1, tmp);
    }
    
    template<typename T>
    static Nombre multiplication(const T & op1, const Nombre & op2)
    {
        Nombre tmp(op1);
        return multiplication(tmp, op2);
    }
    
    static Nombre division(const Nombre & op1, const Nombre & op2)
    {
        Nombre n;
        mpz_fdiv_q(n.data, op1.data, op2.data);
        return n;
    }
    
    static Nombre division(const Nombre & op1, unsigned long int op2)
    {
        Nombre n;
        mpz_fdiv_q_ui(n.data, op1.data, op2);
        return n;
    }
    
    template<typename T>
    static Nombre division(const Nombre & op1, const T & op2)
    {
        Nombre tmp(op2);
        return division(op1, tmp);
    }
    
    template<typename T>
    static Nombre division(const T & op1, const Nombre & op2)
    {
        Nombre tmp(op1);
        return division(tmp, op2);
    }
    
    static Nombre modulo(const Nombre & op1, const Nombre & op2)
    {
        Nombre n;
        mpz_mod(n.data, op1.data, op2.data);
        return n;
    }
    
    static Nombre modulo(const Nombre & op1, unsigned long int op2)
    {
        Nombre n;
        mpz_mod_ui(n.data, op1.data, op2);
        return n;
    }
    
    template<typename T>
    static Nombre modulo(const Nombre & op1, const T & op2)
    {
        Nombre tmp(op2);
        return modulo(op1, tmp);
    }
    
    template<typename T>
    static Nombre modulo(const T & op1, const Nombre & op2)
    {
        Nombre tmp(op1);
        return modulo(tmp, op2);
    }
    
    static bool divise(const Nombre & op1, const Nombre & op2)
    {
        return op1.divisible(op2);
    }
    
    static bool divise(const Nombre & op1, unsigned long int op2)
    {
        return op1.divisible(op2);
    }
    
    template<typename T>
    static bool divise(const T & op1, const Nombre & op2)
    {
        Nombre tmp(op1);
        return tmp.divisible(op2);
    }
    
    template<typename T>
    static bool divise(const Nombre & op1, const T & op2)
    {
        Nombre tmp(op2);
        return op1.divisible(tmp);
    }
    
    void negation()
    {
        mpz_neg(data, data);
    }
    
    Nombre operator-() const
    {
        Nombre resultat;
        mpz_neg(resultat.data, data);
        return resultat;
    }
    
    void abs()
    {
        mpz_abs(data, data);
    }
    
    static Nombre abs(const Nombre & op)
    {
        Nombre resultat;
        mpz_abs(resultat.data, op.data);
        return resultat;
    }
    
    Nombre& operator=(const Nombre & op)
    {
        set(op);
        return *this;
    }

    template<typename T> Nombre& operator=(const T & op)
    {
        set(op);
        return *this;
    }
    
    Nombre& operator+=(const Nombre & op)
    {
        addition(op);
        return *this;
    }

    template<typename T> Nombre& operator+=(const T & op)
    {
        addition(op);
        return *this;
    }
    
    Nombre& operator-=(const Nombre & op)
    {
        soustraction(op);
        return *this;
    }

    template<typename T> Nombre& operator-=(const T & op)
    {
        soustraction(op);
        return *this;
    }
    
    Nombre& operator*=(const Nombre & op)
    {
        multiplication(op);
        return *this;
    }

    template<typename T> Nombre& operator*=(const T & op)
    {
        multiplication(op);
        return *this;
    }
    
    Nombre& operator/=(const Nombre & op)
    {
        division(op);
        return *this;
    }

    template<typename T> Nombre& operator/=(const T & op)
    {
        division(op);
        return *this;
    }
    
    Nombre& operator%=(const Nombre & op)
    {
        modulo(op);
        return *this;
    }

    template<typename T> Nombre& operator%=(const T & op)
    {
        modulo(op);
        return *this;
    }
    
    Nombre operator<<(const unsigned long & b) const
    {
        Nombre resultat;
        mpz_mul_2exp(resultat.data, data, b);
        return resultat;
    }
    
    Nombre operator>>(const unsigned long & b) const
    {
        Nombre resultat;
        mpz_fdiv_q_2exp(resultat.data, data, b);
        return resultat;
    }
    
    static Nombre puissance(const Nombre & base, unsigned long exposant)
    {
        Nombre resultat;
        mpz_pow_ui(resultat.data, base.data, exposant);
        return resultat;
    }
    
    static Nombre puissance(unsigned long base, unsigned long exposant)
    {
        Nombre resultat;
        mpz_ui_pow_ui(resultat.data, base, exposant);
        return resultat;
    }
    
    Nombre & puissance(unsigned long exposant)
    {
        mpz_pow_ui(data, data, exposant);
        return *this;
    }
    
    static Nombre puissance_modulaire(const Nombre & base, unsigned long exposant, const Nombre & modulo)
    {
        Nombre resultat;
        mpz_powm_ui(resultat.data, base.data, exposant, modulo.data);
        return resultat;
    }
    
    Nombre & puissance_modulaire(unsigned long exposant, const Nombre & modulo)
    {
        mpz_powm_ui(data, data, exposant, modulo.data);
        return *this;
    }
    
    Nombre & puissance_modulaire(const Nombre & exposant, const Nombre & modulo)
    {
        mpz_powm(data, data, exposant.data, modulo.data);
        return *this;
    }
    
    template<typename T>
    static Nombre puissance_modulaire(const Nombre & base, unsigned long exposant, const T & modulo)
    {
        Nombre tmp_modulo(modulo);
        return puissance_modulaire(base, exposant, tmp_modulo);
    }
    
    template<typename T>
    Nombre & puissance_modulaire(unsigned long exposant, const T & modulo)
    {
        Nombre tmp_modulo(modulo);
        return puissance_modulaire(exposant, tmp_modulo);
    }
    
    template<typename T>
    Nombre & puissance_modulaire(const Nombre & exposant, const T & modulo)
    {
        Nombre tmp_modulo(modulo);
        return puissance_modulaire(exposant, tmp_modulo);
    }
    
    static Nombre racine(const Nombre & op, unsigned long int n)
    {
        Nombre resultat;
        mpz_root(resultat.data, op.data, n);
        return resultat;
    }
    
    static Nombre racine_carre(const Nombre & op)
    {
        Nombre resultat;
        mpz_sqrt(resultat.data, op.data);
        return resultat;
    }
    
    static bool carre_parfait(const Nombre & op)
    {
        return mpz_perfect_square_p(op.data) != 0;
    }
    
    Nombre racine(unsigned long int n) const
    {
        Nombre resultat;
        mpz_root(resultat.data, data, n);
        return resultat;
    }
    
    Nombre racine_carre() const
    {
        Nombre resultat;
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
    
    Nombre premier_suivant() const
    {
        Nombre resultat;
        mpz_nextprime(resultat.data, data);
        return resultat;
    }
    
    static Nombre PGCD(const Nombre & op1, const Nombre & op2)
    {
        Nombre resultat;
        mpz_gcd(resultat.data, op1.data, op2.data);
        return resultat;
    }
    
    static Nombre PGCD(const Nombre & op1, unsigned long int op2)
    {
        Nombre resultat;
        mpz_gcd_ui(resultat.data, op1.data, op2);
        return resultat;
    }
    
    template<typename T>
    static Nombre PGCD(const Nombre & op1, const T & op2)
    {
        Nombre n2(op2);
        return PGCD(op1, n2);
    }
    
    template<typename T>
    static Nombre PGCD(const T & op1, const Nombre & op2)
    {
        return PGCD(op2, op1);
    }
    
    template<typename T>
    Nombre PGCD(const T & op) const
    {
        return PGCD(*this, op);
    }
    
    static Nombre PPCM(const Nombre & op1, const Nombre & op2)
    {
        Nombre resultat;
        mpz_lcm(resultat.data, op1.data, op2.data);
        return resultat;
    }
    
    static Nombre PPCM(const Nombre & op1, unsigned long int op2)
    {
        Nombre resultat;
        mpz_lcm_ui(resultat.data, op1.data, op2);
        return resultat;
    }
    
    template<typename T>
    static Nombre PPCM(const Nombre & op1, const T & op2)
    {
        Nombre n2(op2);
        return PPCM(op1, n2);
    }
    
    template<typename T>
    static Nombre PPCM(const T & op1, const Nombre & op2)
    {
        return PPCM(op2, op1);
    }
    
    template<typename T>
    Nombre PPCM(const T & op) const
    {
        return PPCM(*this, op);
    }
    
    boost::optional<Nombre> inverse_modulaire(const Nombre & modulo) const
    {
        Nombre resultat;
        if (mpz_invert(resultat.data, data, modulo.data) != 0)
            return resultat;
        
        return boost::none;
    }
    
    static boost::optional<Nombre> inverse_modulaire(const Nombre & op, const Nombre & modulo)
    {
        return op.inverse_modulaire(modulo);
    }
    
    Nombre & operator++()
    {
        return addition(1);
    }
    
    Nombre & operator--()
    {
        return soustraction(1);
    }
    
    Nombre operator++(int)
    {
        Nombre copie(data);
        addition(1);
        return copie;
    }
    
    Nombre operator--(int)
    {
        Nombre copie(data);
        soustraction(1);
        return copie;
    }
    
    Nombre operator~() const
    {
        Nombre r;
        mpz_com(r.data, data);
        return r;
    }
    
    Nombre & operator &=(const Nombre & n)
    {
        mpz_and(data, data, n.data);
        return *this;
    }
    
    template<typename T>
    Nombre & operator &=(const T & op)
    {
        Nombre n(op);
        mpz_and(data, data, n.data);
        return *this;
    }
    
    Nombre & operator |=(const Nombre & n)
    {
        mpz_ior(data, data, n.data);
        return *this;
    }
    
    template<typename T>
    Nombre & operator |=(const T & op)
    {
        Nombre n(op);
        mpz_ior(data, data, n.data);
        return *this;
    }
    
    Nombre & operator ^=(const Nombre & n)
    {
        mpz_xor(data, data, n.data);
        return *this;
    }
    
    template<typename T>
    Nombre & operator ^=(const T & op)
    {
        Nombre n(op);
        mpz_xor(data, data, n.data);
        return *this;
    }
};

inline Nombre operator+(const Nombre & op1, const Nombre & op2)
{
    return Nombre::addition(op1, op2);
}

template<typename T>
inline Nombre operator+(const Nombre & op1, const T & op2)
{
    return Nombre::addition(op1, op2);
}

template<typename T>
inline Nombre operator+(const T & op1, const Nombre & op2)
{
    return Nombre::addition(op1, op2);
}

inline Nombre operator-(const Nombre & op1, const Nombre & op2)
{
    return Nombre::soustraction(op1, op2);
}

template<typename T>
inline Nombre operator-(const Nombre & op1, const T & op2)
{
    return Nombre::soustraction(op1, op2);
}

template<typename T>
inline Nombre operator-(const T & op1, const Nombre & op2)
{
    return Nombre::soustraction(op1, op2);
}

inline Nombre operator*(const Nombre & op1, const Nombre & op2)
{
    return Nombre::multiplication(op1, op2);
}

template<typename T>
inline Nombre operator*(const Nombre & op1, const T & op2)
{
    return Nombre::multiplication(op1, op2);
}

template<typename T>
inline Nombre operator*(const T & op1, const Nombre & op2)
{
    return Nombre::multiplication(op1, op2);
}

inline Nombre operator/(const Nombre & op1, const Nombre & op2)
{
    return Nombre::division(op1, op2);
}

template<typename T>
inline Nombre operator/(const Nombre & op1, const T & op2)
{
    return Nombre::division(op1, op2);
}

template<typename T>
inline Nombre operator/(const T & op1, const Nombre & op2)
{
    return Nombre::division(op1, op2);
}

inline Nombre operator%(const Nombre & op1, const Nombre & op2)
{
    return Nombre::modulo(op1, op2);
}

template<typename T>
inline Nombre operator%(const Nombre & op1, const T & op2)
{
    return Nombre::modulo(op1, op2);
}

template<typename T>
inline Nombre operator%(const T & op1, const Nombre & op2)
{
    return Nombre::modulo(op1, op2);
}

inline Nombre operator&(const Nombre & a, const Nombre & b)
{
    Nombre resultat(a);
    resultat &= b;
    return resultat;
}

template<typename T>
inline Nombre operator&(const Nombre & a, const T & b)
{
    Nombre resultat(b);
    resultat &= a;
    return resultat;
}

template<typename T>
inline Nombre operator&(const T & a, const Nombre & b)
{
    Nombre resultat(a);
    resultat &= b;
    return resultat;
}

inline Nombre operator|(const Nombre & a, const Nombre & b)
{
    Nombre resultat(a);
    resultat |= b;
    return resultat;
}

template<typename T>
inline Nombre operator|(const Nombre & a, const T & b)
{
    Nombre resultat(b);
    resultat |= a;
    return resultat;
}

template<typename T>
inline Nombre operator|(const T & a, const Nombre & b)
{
    Nombre resultat(a);
    resultat |= b;
    return resultat;
}

inline Nombre operator^(const Nombre & a, const Nombre & b)
{
    Nombre resultat(a);
    resultat ^= b;
    return resultat;
}

template<typename T>
inline Nombre operator^(const Nombre & a, const T & b)
{
    Nombre resultat(b);
    resultat ^= a;
    return resultat;
}

template<typename T>
inline Nombre operator^(const T & a, const Nombre & b)
{
    Nombre resultat(a);
    resultat ^= b;
    return resultat;
}

namespace std
{
    Nombre abs(const Nombre & op);
    
    void swap(Nombre & op1, Nombre & op2);
    
    Nombre sqrt(const Nombre & op);
    
    Nombre cbrt(const Nombre & op);
    
    std::ostream& operator<<(std::ostream& os, const Nombre & op);
    
    std::istream& operator>>(std::istream& is, Nombre & op);;
    
    std::string to_string( const Nombre & n );
}
