#pragma once

#include <iostream>
#include <gmp.h>

#include <boost/optional.hpp>
#include <limits>
#include <deque>

class grand_nombre
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
    grand_nombre();
    grand_nombre(const mpz_t & op);
    grand_nombre(const grand_nombre & op);
    
    grand_nombre(unsigned int op);
    grand_nombre(signed int op);
    grand_nombre(unsigned long op);
    grand_nombre(signed long op);
    grand_nombre(double op);
    grand_nombre(const std::string & op, int base = 10);
    grand_nombre(unsigned long long op);
    grand_nombre(signed long long op);
    grand_nombre(long double op);
    virtual ~grand_nombre();
    
    void set(const mpz_t & op);
    void set(const grand_nombre & op);
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

    int compare(const grand_nombre & op) const;
    int compare(double op) const;
    int compare(signed long int op) const;
    int compare(unsigned long int op) const;

    template<typename T>
    int compare(const T & op) const
    {
        grand_nombre n(op);
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
    
    void swap(grand_nombre & op);
    const std::string to_string(int base = 10) const;
    
    grand_nombre & addition(const grand_nombre & op);
    grand_nombre & addition(unsigned long int op);

    template<typename T>
    grand_nombre & addition(const T & op)
    {
        grand_nombre tmp(op);
        return addition(tmp);
    }
    
    grand_nombre & soustraction(const grand_nombre & op);
    grand_nombre & soustraction(unsigned long int op);
    
    template<typename T>
    grand_nombre & soustraction(const T & op)
    {
        grand_nombre tmp(op);
        return soustraction(tmp);
    }
    
    grand_nombre & multiplication(const grand_nombre & op);
    grand_nombre & multiplication(unsigned long int op);
    grand_nombre & multiplication(signed long int op);

    template<typename T>
    grand_nombre & multiplication(const T & op)
    {
        grand_nombre tmp(op);
        return multiplication(tmp);
    }
    
    grand_nombre & division(const grand_nombre & op);
    grand_nombre & division(unsigned long int op);
    
    template<typename T>
    grand_nombre & division(const T & op)
    {
        grand_nombre tmp(op);
        return division(tmp);
    }
    
    grand_nombre & modulo(const grand_nombre & op);
    grand_nombre & modulo(unsigned long int op);

    template<typename T>
    grand_nombre & modulo(const T & op)
    {
        grand_nombre tmp(op);
        return modulo(tmp);
    }
    
    bool divisible(const grand_nombre & op) const;
    bool divisible(unsigned long int op) const;
    
    template<typename T>
    bool divisible(const T & op) const
    {
        grand_nombre tmp(op);
        return divisible(tmp);
    }
    
    static grand_nombre addition(const grand_nombre & op1, const grand_nombre & op2)
    {
        grand_nombre n;
        mpz_add(n.data, op1.data, op2.data);
        return n;
    }
    
    static grand_nombre addition(const grand_nombre & op1, unsigned long int op2)
    {
        grand_nombre n;
        mpz_add_ui(n.data, op1.data, op2);
        return n;
    }
    
    static grand_nombre addition(unsigned long int op1, const grand_nombre & op2)
    {
        grand_nombre n;
        mpz_add_ui(n.data, op2.data, op1);
        return n;
    }
    
    template<typename T>
    static grand_nombre addition(const grand_nombre & op1, const T & op2)
    {
        grand_nombre tmp(op2);
        return addition(op1, tmp);
    }
    
    template<typename T>
    static grand_nombre addition(const T & op1, const grand_nombre & op2)
    {
        grand_nombre tmp(op1);
        return addition(tmp, op2);
    }
    
    static grand_nombre soustraction(const grand_nombre & op1, const grand_nombre & op2)
    {
        grand_nombre n;
        mpz_sub(n.data, op1.data, op2.data);
        return n;
    }
    
    static grand_nombre soustraction(const grand_nombre & op1, unsigned long int op2)
    {
        grand_nombre n;
        mpz_sub_ui(n.data, op1.data, op2);
        return n;
    }
    
    static grand_nombre soustraction(unsigned long int op1, const grand_nombre & op2)
    {
        grand_nombre n;
        mpz_ui_sub(n.data, op1, op2.data);
        return n;
    }
    
    template<typename T>
    static grand_nombre soustraction(const grand_nombre & op1, const T & op2)
    {
        grand_nombre tmp(op2);
        return soustraction(op1, tmp);
    }
    
    template<typename T>
    static grand_nombre soustraction(const T & op1, const grand_nombre & op2)
    {
        grand_nombre tmp(op1);
        return soustraction(tmp, op2);
    }
    
    static grand_nombre multiplication(const grand_nombre & op1, const grand_nombre & op2)
    {
        grand_nombre n;
        mpz_mul(n.data, op1.data, op2.data);
        return n;
    }
    
    static grand_nombre multiplication(const grand_nombre & op1, unsigned long int op2)
    {
        grand_nombre n;
        mpz_mul_ui(n.data, op1.data, op2);
        return n;
    }
    
    static grand_nombre multiplication(unsigned long int op1, const grand_nombre & op2)
    {
        grand_nombre n;
        mpz_mul_ui(n.data, op2.data, op1);
        return n;
    }
    
    static grand_nombre multiplication(const grand_nombre & op1, signed long int op2)
    {
        grand_nombre n;
        mpz_mul_si(n.data, op1.data, op2);
        return n;
    }
    
    static grand_nombre multiplication(signed long int op1, const grand_nombre & op2)
    {
        grand_nombre n;
        mpz_mul_si(n.data, op2.data, op1);
        return n;
    }
    
    template<typename T>
    static grand_nombre multiplication(const grand_nombre & op1, const T & op2)
    {
        grand_nombre tmp(op2);
        return multiplication(op1, tmp);
    }
    
    template<typename T>
    static grand_nombre multiplication(const T & op1, const grand_nombre & op2)
    {
        grand_nombre tmp(op1);
        return multiplication(tmp, op2);
    }
    
    static grand_nombre division(const grand_nombre & op1, const grand_nombre & op2)
    {
        grand_nombre n;
        mpz_fdiv_q(n.data, op1.data, op2.data);
        return n;
    }
    
    static grand_nombre division(const grand_nombre & op1, unsigned long int op2)
    {
        grand_nombre n;
        mpz_fdiv_q_ui(n.data, op1.data, op2);
        return n;
    }
    
    template<typename T>
    static grand_nombre division(const grand_nombre & op1, const T & op2)
    {
        grand_nombre tmp(op2);
        return division(op1, tmp);
    }
    
    template<typename T>
    static grand_nombre division(const T & op1, const grand_nombre & op2)
    {
        grand_nombre tmp(op1);
        return division(tmp, op2);
    }
    
    static grand_nombre modulo(const grand_nombre & op1, const grand_nombre & op2)
    {
        grand_nombre n;
        mpz_mod(n.data, op1.data, op2.data);
        return n;
    }
    
    static grand_nombre modulo(const grand_nombre & op1, unsigned long int op2)
    {
        grand_nombre n;
        mpz_mod_ui(n.data, op1.data, op2);
        return n;
    }
    
    template<typename T>
    static grand_nombre modulo(const grand_nombre & op1, const T & op2)
    {
        grand_nombre tmp(op2);
        return modulo(op1, tmp);
    }
    
    template<typename T>
    static grand_nombre modulo(const T & op1, const grand_nombre & op2)
    {
        grand_nombre tmp(op1);
        return modulo(tmp, op2);
    }
    
    static bool divise(const grand_nombre & op1, const grand_nombre & op2)
    {
        return op1.divisible(op2);
    }
    
    static bool divise(const grand_nombre & op1, unsigned long int op2)
    {
        return op1.divisible(op2);
    }
    
    template<typename T>
    static bool divise(const T & op1, const grand_nombre & op2)
    {
        grand_nombre tmp(op1);
        return tmp.divisible(op2);
    }
    
    template<typename T>
    static bool divise(const grand_nombre & op1, const T & op2)
    {
        grand_nombre tmp(op2);
        return op1.divisible(tmp);
    }

    grand_nombre negation()
    {
        mpz_neg(data, data);
        return *this;
    }
    
    grand_nombre operator-() const
    {
        grand_nombre resultat;
        mpz_neg(resultat.data, data);
        return resultat;
    }
    
    void abs()
    {
        mpz_abs(data, data);
    }
    
    static grand_nombre abs(const grand_nombre & op)
    {
        grand_nombre resultat;
        mpz_abs(resultat.data, op.data);
        return resultat;
    }
    
    grand_nombre& operator=(const grand_nombre & op)
    {
        set(op);
        return *this;
    }

    template<typename T> grand_nombre& operator=(const T & op)
    {
        set(op);
        return *this;
    }
    
    grand_nombre& operator+=(const grand_nombre & op)
    {
        addition(op);
        return *this;
    }

    template<typename T> grand_nombre& operator+=(const T & op)
    {
        addition(op);
        return *this;
    }
    
    grand_nombre& operator-=(const grand_nombre & op)
    {
        soustraction(op);
        return *this;
    }

    template<typename T> grand_nombre& operator-=(const T & op)
    {
        soustraction(op);
        return *this;
    }
    
    grand_nombre& operator*=(const grand_nombre & op)
    {
        multiplication(op);
        return *this;
    }

    template<typename T> grand_nombre& operator*=(const T & op)
    {
        multiplication(op);
        return *this;
    }
    
    grand_nombre& operator/=(const grand_nombre & op)
    {
        division(op);
        return *this;
    }

    template<typename T> grand_nombre& operator/=(const T & op)
    {
        division(op);
        return *this;
    }
    
    grand_nombre& operator%=(const grand_nombre & op)
    {
        modulo(op);
        return *this;
    }

    template<typename T> grand_nombre& operator%=(const T & op)
    {
        modulo(op);
        return *this;
    }
    
    grand_nombre operator<<(const unsigned long & b) const
    {
        grand_nombre resultat;
        mpz_mul_2exp(resultat.data, data, b);
        return resultat;
    }
    
    grand_nombre operator>>(const unsigned long & b) const
    {
        grand_nombre resultat;
        mpz_fdiv_q_2exp(resultat.data, data, b);
        return resultat;
    }
    
    static grand_nombre puissance(const grand_nombre & base, unsigned long exposant)
    {
        grand_nombre resultat;
        mpz_pow_ui(resultat.data, base.data, exposant);
        return resultat;
    }
    
    static grand_nombre puissance(unsigned long base, unsigned long exposant)
    {
        grand_nombre resultat;
        mpz_ui_pow_ui(resultat.data, base, exposant);
        return resultat;
    }
    
    grand_nombre & puissance(unsigned long exposant)
    {
        mpz_pow_ui(data, data, exposant);
        return *this;
    }
    
    static grand_nombre puissance_modulaire(const grand_nombre & base, unsigned long exposant, const grand_nombre & modulo)
    {
        grand_nombre resultat;
        mpz_powm_ui(resultat.data, base.data, exposant, modulo.data);
        return resultat;
    }
    
    grand_nombre & puissance_modulaire(unsigned long exposant, const grand_nombre & modulo)
    {
        mpz_powm_ui(data, data, exposant, modulo.data);
        return *this;
    }
    
    grand_nombre & puissance_modulaire(const grand_nombre & exposant, const grand_nombre & modulo)
    {
        mpz_powm(data, data, exposant.data, modulo.data);
        return *this;
    }
    
    template<typename T>
    static grand_nombre puissance_modulaire(const grand_nombre & base, unsigned long exposant, const T & modulo)
    {
        grand_nombre tmp_modulo(modulo);
        return puissance_modulaire(base, exposant, tmp_modulo);
    }
    
    template<typename T>
    grand_nombre & puissance_modulaire(unsigned long exposant, const T & modulo)
    {
        grand_nombre tmp_modulo(modulo);
        return puissance_modulaire(exposant, tmp_modulo);
    }
    
    template<typename T>
    grand_nombre & puissance_modulaire(const grand_nombre & exposant, const T & modulo)
    {
        grand_nombre tmp_modulo(modulo);
        return puissance_modulaire(exposant, tmp_modulo);
    }
    
    static grand_nombre racine(const grand_nombre & op, unsigned long int n)
    {
        grand_nombre resultat;
        mpz_root(resultat.data, op.data, n);
        return resultat;
    }
    
    static grand_nombre racine_carre(const grand_nombre & op)
    {
        grand_nombre resultat;
        mpz_sqrt(resultat.data, op.data);
        return resultat;
    }
    
    static bool carre_parfait(const grand_nombre & op)
    {
        return mpz_perfect_square_p(op.data) != 0;
    }
    
    grand_nombre racine(unsigned long int n) const
    {
        grand_nombre resultat;
        mpz_root(resultat.data, data, n);
        return resultat;
    }
    
    grand_nombre racine_carre() const
    {
        grand_nombre resultat;
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
        grand_nombre tmp(n);
        return tmp.premier(probabilite);
    }
    
    grand_nombre premier_suivant() const
    {
        grand_nombre resultat;
        mpz_nextprime(resultat.data, data);
        return resultat;
    }
    
    static grand_nombre PGCD(const grand_nombre & op1, const grand_nombre & op2)
    {
        grand_nombre resultat;
        mpz_gcd(resultat.data, op1.data, op2.data);
        return resultat;
    }
    
    static grand_nombre PGCD(const grand_nombre & op1, unsigned long int op2)
    {
        grand_nombre resultat;
        mpz_gcd_ui(resultat.data, op1.data, op2);
        return resultat;
    }
    
    template<typename T>
    static grand_nombre PGCD(const grand_nombre & op1, const T & op2)
    {
        grand_nombre n2(op2);
        return PGCD(op1, n2);
    }
    
    template<typename T>
    static grand_nombre PGCD(const T & op1, const grand_nombre & op2)
    {
        return PGCD(op2, op1);
    }

    static grand_nombre PPCM(const grand_nombre & op1, const grand_nombre & op2)
    {
        grand_nombre resultat;
        mpz_lcm(resultat.data, op1.data, op2.data);
        return resultat;
    }
    
    static grand_nombre PPCM(const grand_nombre & op1, unsigned long int op2)
    {
        grand_nombre resultat;
        mpz_lcm_ui(resultat.data, op1.data, op2);
        return resultat;
    }
    
    template<typename T>
    static grand_nombre PPCM(const grand_nombre & op1, const T & op2)
    {
        grand_nombre n2(op2);
        return PPCM(op1, n2);
    }
    
    template<typename T>
    static grand_nombre PPCM(const T & op1, const grand_nombre & op2)
    {
        return PPCM(op2, op1);
    }

    boost::optional<grand_nombre> inverse_modulaire(const grand_nombre & modulo) const
    {
        grand_nombre resultat;
        if (mpz_invert(resultat.data, data, modulo.data) != 0)
            return resultat;
        
        return boost::none;
    }
    
    static boost::optional<grand_nombre> inverse_modulaire(const grand_nombre & op, const grand_nombre & modulo)
    {
        return op.inverse_modulaire(modulo);
    }
    
    grand_nombre & operator++()
    {
        return addition(1);
    }
    
    grand_nombre & operator--()
    {
        return soustraction(1);
    }
    
    grand_nombre operator++(int)
    {
        grand_nombre copie(data);
        addition(1);
        return copie;
    }
    
    grand_nombre operator--(int)
    {
        grand_nombre copie(data);
        soustraction(1);
        return copie;
    }
    
    grand_nombre operator~() const
    {
        grand_nombre r;
        mpz_com(r.data, data);
        return r;
    }
    
    grand_nombre & operator &=(const grand_nombre & n)
    {
        mpz_and(data, data, n.data);
        return *this;
    }
    
    template<typename T>
    grand_nombre & operator &=(const T & op)
    {
        grand_nombre n(op);
        mpz_and(data, data, n.data);
        return *this;
    }
    
    grand_nombre & operator |=(const grand_nombre & n)
    {
        mpz_ior(data, data, n.data);
        return *this;
    }
    
    template<typename T>
    grand_nombre & operator |=(const T & op)
    {
        grand_nombre n(op);
        mpz_ior(data, data, n.data);
        return *this;
    }
    
    grand_nombre & operator ^=(const grand_nombre & n)
    {
        mpz_xor(data, data, n.data);
        return *this;
    }
    
    template<typename T>
    grand_nombre & operator ^=(const T & op)
    {
        grand_nombre n(op);
        mpz_xor(data, data, n.data);
        return *this;
    }
    
    static grand_nombre coefficient_binomial(const grand_nombre & n, unsigned long int k);
    static grand_nombre coefficient_binomial(unsigned long int n, unsigned long int k);
    static grand_nombre factorielle(unsigned long int n);
    static grand_nombre catalan(unsigned long int n);

    void boucle_chiffre(std::function<void(unsigned long int)> op, unsigned long int base = 10) const;
    size_t nombre_chiffres(unsigned long int base = 10) const;
    grand_nombre somme_chiffres(unsigned long int base = 10) const;
    std::deque<unsigned long int> extraire_chiffres(unsigned long int base = 10) const;
    grand_nombre inverser_nombre(unsigned long int base = 10) const;
    bool palindrome(unsigned long int base = 10) const;
};

template<typename T>
inline grand_nombre operator+(const T & op1, const grand_nombre & op2)
{
    return grand_nombre::addition(op1, op2);
}

template<typename T>
inline grand_nombre operator-(const T & op1, const grand_nombre & op2)
{
    return grand_nombre::soustraction(op1, op2);
}

template<typename T>
inline grand_nombre operator*(const T & op1, const grand_nombre & op2)
{
    return grand_nombre::multiplication(op1, op2);
}

template<typename T>
inline grand_nombre operator/(const T & op1, const grand_nombre & op2)
{
    return grand_nombre::division(op1, op2);
}

template<typename T>
inline grand_nombre operator%(const T & op1, const grand_nombre & op2)
{
    return grand_nombre::modulo(op1, op2);
}

template<typename T>
inline grand_nombre operator&(const T & a, const grand_nombre & b)
{
    grand_nombre resultat(a);
    resultat &= b;
    return resultat;
}

template<typename T>
inline grand_nombre operator|(const T & a, const grand_nombre & b)
{
    grand_nombre resultat(a);
    resultat |= b;
    return resultat;
}

template<typename T>
inline grand_nombre operator^(const T & a, const grand_nombre & b)
{
    grand_nombre resultat(a);
    resultat ^= b;
    return resultat;
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator ==(const T & a, const grand_nombre & b) {
    return b.compare(a) == 0; 
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator !=(const T & a, const grand_nombre & b) { 
    return b.compare(a) != 0; 
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator <(const T & a, const grand_nombre & b) { 
    return b.compare(a) > 0; 
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator >(const T & a, const grand_nombre & b) { 
    return b.compare(a) < 0; 
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator <=(const T & a, const grand_nombre & b) { 
    return b.compare(a) > -1; 
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator >=(const T & a, const grand_nombre & b) { 
    return b.compare(a) < 1; 
}

namespace std
{
    grand_nombre abs(const grand_nombre & op);
    
    void swap(grand_nombre & op1, grand_nombre & op2);
    
    grand_nombre sqrt(const grand_nombre & op);
    
    grand_nombre cbrt(const grand_nombre & op);
    
    std::ostream& operator<<(std::ostream& os, const grand_nombre & op);
    
    std::istream& operator>>(std::istream& is, grand_nombre & op);

    template<>
    class numeric_limits<grand_nombre> : public numeric_limits<long long>
    {
    public:
        static constexpr int digits = INT_MAX;
        static constexpr int digits10 = INT_MAX;

        static grand_nombre min()
        {
            return -max();
        }

        static grand_nombre max()
        {
            return grand_nombre::puissance(2, digits);
        }

        static grand_nombre lowest()
        {
            return min();
        }
    };
}
