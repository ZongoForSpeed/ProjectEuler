#pragma once

#include <mpfr.h>
#include <sstream>

#include "mpq_fraction.h"
#include "mpz_nombre.h"

class mpf_nombre {
    mpfr_ptr _data;

    static long DEFAULT_PRECISION;
    static mpfr_rnd_t DEFAULT_ROUNDING;
    static mpf_nombre PI;
    static mpf_nombre E;
    static mpf_nombre PHI;

    static mpf_nombre calcul_pi();

    static mpf_nombre calcul_e();

    static mpf_nombre calcul_phi();

    void init();

    void clear();

    template<typename Type>
    void init_set(Type op, std::true_type/*is_signed*/) {
        mpfr_init_set_si(_data, op, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void init_set(Type op, std::false_type/*is_signed*/) {
        mpfr_init_set_ui(_data, op, DEFAULT_ROUNDING);
    }

public:
    static void setPrecision(long precision);

    static void setRounding(mpfr_rnd_t rounding);

    mpf_nombre();

    mpf_nombre(const mpf_nombre &op);

    mpf_nombre(unsigned long op);

    mpf_nombre(long op);

    mpf_nombre(double op);

    mpf_nombre(long double op);

    mpf_nombre(const mpz_nombre &op);

    mpf_nombre(const mpq_fraction &op);

    mpf_nombre(const std::string &op, int base = 10);

    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    mpf_nombre(const Type x) {
        init();
        init_set(x, std::is_signed<Type>());
    }

    mpf_nombre(mpf_nombre &&op);

    ~mpf_nombre();

    mpf_nombre &operator=(const mpf_nombre &op);

    mpf_nombre &operator=(mpf_nombre &&op) noexcept;

    template<typename Type>
    mpf_nombre &operator=(const Type &op) {
        if (this != &op) {
            set(op);
        }
        return *this;
    }

    friend void swap(mpf_nombre &a, mpf_nombre &b) {
        std::swap(a._data, b._data);
    }

    void swap(mpf_nombre &op);

    // region setters
    void set(const mpf_nombre &op);

    void set(unsigned long op);

    void set(long op);

    void set(float op);

    void set(double op);

    void set(long double op);

    void set(const mpz_nombre &op);

    void set(const mpq_fraction &op);

    void set(const std::string &op, int base = 10);

    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    void set(Type x) {
        mpz_nombre tmp(x);
        set(tmp);
    }
    // endregion setters

    // region getters
    mpfr_ptr get_data();

    mpfr_srcptr get_data() const;

    float get_float() const;

    double get_double() const;

    long double get_long_double() const;

    long get_signed_long() const;

    unsigned long get_unsigned_long() const;

    mpz_nombre get_mpz_nombre();

    mpq_fraction get_mpq_fraction();
    // endregion getters

    std::string to_string(size_t precision = 15) const;

    static void negation(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_neg(rop._data, op._data, DEFAULT_ROUNDING);
    }

    mpf_nombre operator-() const;

    // region addition
    void static addition(mpf_nombre &rop, const mpf_nombre &op1, const mpf_nombre &op2);

    void static addition(mpf_nombre &rop, const mpf_nombre &op1, const mpz_nombre &op2);

    void static addition(mpf_nombre &rop, const mpf_nombre &op1, const mpq_fraction &op2);

    template<typename Type, typename = typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type>
    void static addition(mpf_nombre &rop, const mpf_nombre &op1, Type op2) {
        addition(rop, op1, op2, std::is_floating_point<Type>(), std::is_signed<Type>());
    }

    template<typename Type>
    void static addition(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::true_type /*is_floating_point*/,
                         std::true_type /*is_signed*/) {
        mpfr_add_d(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }


    template<typename Type>
    void static addition(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::false_type /*is_floating_point*/,
                         std::true_type /*is_signed*/) {
        mpfr_add_si(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static addition(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::false_type /*is_floating_point*/,
                         std::false_type /*is_signed*/) {
        mpfr_add_ui(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    template<typename Type>
    mpf_nombre &operator+=(Type op) {
        addition(*this, *this, op);
        return *this;
    }

    template<typename Type>
    mpf_nombre operator+(Type op) const {
        mpf_nombre rop;
        addition(rop, *this, op);
        return rop;
    }
    // endregion addition

    // region soustraction
    void static soustraction(mpf_nombre &rop, const mpf_nombre &op1, const mpf_nombre &op2);

    void static soustraction(mpf_nombre &rop, const mpf_nombre &op1, const mpz_nombre &op2);

    void static soustraction(mpf_nombre &rop, const mpf_nombre &op1, const mpq_fraction &op2);

    template<typename Type, typename = typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type>
    void static soustraction(mpf_nombre &rop, const mpf_nombre &op1, Type op2) {
        soustraction(rop, op1, op2, std::is_floating_point<Type>(), std::is_signed<Type>());
    }

    template<typename Type>
    void static soustraction(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::true_type /*is_floating_point*/,
                             std::true_type /*is_signed*/) {
        mpfr_sub_d(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static soustraction(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::false_type /*is_floating_point*/,
                             std::true_type /*is_signed*/) {
        mpfr_sub_si(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static soustraction(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::false_type /*is_floating_point*/,
                             std::false_type /*is_signed*/) {
        mpfr_sub_ui(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    void static soustraction(mpf_nombre &rop, const mpz_nombre &op1, const mpf_nombre &op2) {
        mpfr_sub_z(rop._data, op2._data, op1.get_data(), DEFAULT_ROUNDING);
        negation(rop, rop);
    }

    void static soustraction(mpf_nombre &rop, const mpq_fraction &op1, const mpf_nombre &op2) {
        mpfr_sub_q(rop._data, op2._data, op1.get_data(), DEFAULT_ROUNDING);
        negation(rop, rop);
    }

    template<typename Type, typename = typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type>
    void static soustraction(mpf_nombre &rop, Type op1, const mpf_nombre &op2) {
        soustraction(rop, op1, op2, std::is_floating_point<Type>(), std::is_signed<Type>());
    }

    template<typename Type>
    void static soustraction(mpf_nombre &rop, Type op1, const mpf_nombre &op2, std::true_type /*is_floating_point*/,
                             std::true_type /*is_signed*/) {
        mpfr_d_sub(rop._data, op1, op2._data, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static soustraction(mpf_nombre &rop, Type op1, const mpf_nombre &op2, std::false_type /*is_floating_point*/,
                             std::true_type /*is_signed*/) {
        mpfr_si_sub(rop._data, op1, op2._data, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static soustraction(mpf_nombre &rop, Type op1, const mpf_nombre &op2, std::false_type /*is_floating_point*/,
                             std::false_type /*is_signed*/) {
        mpfr_ui_sub(rop._data, op1, op2._data, DEFAULT_ROUNDING);
    }

    template<typename Type>
    mpf_nombre &operator-=(Type op) {
        soustraction(*this, *this, op);
        return *this;
    }

    template<typename Type>
    mpf_nombre operator-(Type op) const {
        mpf_nombre rop;
        soustraction(rop, *this, op);
        return rop;
    }
    // endregion soustraction

    // region multiplication
    void static multiplication(mpf_nombre &rop, const mpf_nombre &op1, const mpf_nombre &op2);

    void static multiplication(mpf_nombre &rop, const mpf_nombre &op1, const mpz_nombre &op2);

    void static multiplication(mpf_nombre &rop, const mpf_nombre &op1, const mpq_fraction &op2);

    template<typename Type, typename = typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type>
    void static multiplication(mpf_nombre &rop, const mpf_nombre &op1, Type op2) {
        multiplication(rop, op1, op2, std::is_floating_point<Type>(), std::is_signed<Type>());
    }

    template<typename Type>
    void static multiplication(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::true_type /*is_floating_point*/,
                               std::true_type /*is_signed*/) {
        mpfr_mul_d(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }


    template<typename Type>
    void static multiplication(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::false_type /*is_floating_point*/,
                               std::true_type /*is_signed*/) {
        mpfr_mul_si(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static multiplication(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::false_type /*is_floating_point*/,
                               std::false_type /*is_signed*/) {
        mpfr_mul_ui(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    template<typename Type>
    mpf_nombre &operator*=(Type op) {
        multiplication(*this, *this, op);
        return *this;
    }

    template<typename Type>
    mpf_nombre operator*(Type op) const {
        mpf_nombre rop;
        multiplication(rop, *this, op);
        return rop;
    }
    // endregion multiplication

    // region division
    void static division(mpf_nombre &rop, const mpf_nombre &op1, const mpf_nombre &op2);

    void static division(mpf_nombre &rop, const mpf_nombre &op1, const mpz_nombre &op2);

    void static division(mpf_nombre &rop, const mpf_nombre &op1, const mpq_fraction &op2);

    template<typename Type, typename = typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type>
    void static division(mpf_nombre &rop, const mpf_nombre &op1, Type op2) {
        division(rop, op1, op2, std::is_floating_point<Type>(), std::is_signed<Type>());
    }

    template<typename Type>
    void static division(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::true_type /*is_floating_point*/,
                         std::true_type /*is_signed*/) {
        mpfr_div_d(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static division(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::false_type /*is_floating_point*/,
                         std::true_type /*is_signed*/) {
        mpfr_div_si(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static division(mpf_nombre &rop, const mpf_nombre &op1, Type op2, std::false_type /*is_floating_point*/,
                         std::false_type /*is_signed*/) {
        mpfr_div_ui(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    void static division(mpf_nombre &rop, const mpz_nombre &op1, const mpf_nombre &op2) {
        mpfr_div_z(rop._data, op2._data, op1.get_data(), DEFAULT_ROUNDING);
        inverse(rop, rop);
    }

    void static division(mpf_nombre &rop, const mpq_fraction &op1, const mpf_nombre &op2) {
        mpfr_div_q(rop._data, op2._data, op1.get_data(), DEFAULT_ROUNDING);
        inverse(rop, rop);
    }

    template<typename Type, typename = typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type>
    void static division(mpf_nombre &rop, Type op1, const mpf_nombre &op2) {
        division(rop, op1, op2, std::is_floating_point<Type>(), std::is_signed<Type>());
    }

    template<typename Type>
    void static division(mpf_nombre &rop, Type op1, const mpf_nombre &op2, std::true_type /*is_floating_point*/,
                         std::true_type /*is_signed*/) {
        mpfr_d_div(rop._data, op1, op2._data, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static division(mpf_nombre &rop, Type op1, const mpf_nombre &op2, std::false_type /*is_floating_point*/,
                         std::true_type /*is_signed*/) {
        mpfr_si_div(rop._data, op1, op2._data, DEFAULT_ROUNDING);
    }

    template<typename Type>
    void static division(mpf_nombre &rop, Type op1, const mpf_nombre &op2, std::false_type /*is_floating_point*/,
                         std::false_type /*is_signed*/) {
        mpfr_ui_div(rop._data, op1, op2._data, DEFAULT_ROUNDING);
    }

    template<typename Type>
    mpf_nombre &operator/=(Type op) {
        division(*this, *this, op);
        return *this;
    }

    template<typename Type>
    mpf_nombre operator/(Type op) const {
        mpf_nombre rop;
        division(rop, *this, op);
        return rop;
    }
    // endregion division

    // region comparaison
    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    int compare(const Type &op) const {
        return compare(op, std::is_signed<Type>());
    }

    template<typename Type>
    int compare(Type op, std::false_type /*is_signed*/) const {
        return mpfr_cmp_ui(_data, op);
    }

    template<typename Type>
    int compare(Type op, std::true_type /*is_signed*/) const {
        return mpfr_cmp_si(_data, op);
    }

    int compare(const mpf_nombre &op) const;

    int compare(unsigned long op) const;

    int compare(signed long op) const;

    int compare(double op) const;

    int compare(long double op) const;

    int compare(const mpz_nombre &op) const;

    int compare(const mpq_fraction &op) const;

    template<typename Type>
    bool operator>(const Type &op) const {
        return compare(op) > 0;
    }

    template<typename Type>
    bool operator>=(const Type &op) const {
        return compare(op) >= 0;
    }

    template<typename Type>
    bool operator<(const Type &op) const {
        return compare(op) < 0;
    }

    template<typename Type>
    bool operator<=(const Type &op) const {
        return compare(op) <= 0;
    }

    template<typename Type>
    bool operator==(const Type &op) const {
        return compare(op) == 0;
    }

    template<typename Type>
    bool operator!=(const Type &op) const {
        return compare(op) != 0;
    }
    // endregion comparaison

    static void abs(mpf_nombre &rop, const mpf_nombre &op);

    static void racine_carre(mpf_nombre &rop, const mpf_nombre &op);

    static void racine_cubique(mpf_nombre &rop, const mpf_nombre &op);

    static void racine(mpf_nombre &rop, const mpf_nombre &op, unsigned long n);

    static void hypothenuse(mpf_nombre &rop, const mpf_nombre &x, const mpf_nombre &y);

    static void log(mpf_nombre &rop, const mpf_nombre &op);

    static void log2(mpf_nombre &rop, const mpf_nombre &op);

    static void log10(mpf_nombre &rop, const mpf_nombre &op);

    static void exp(mpf_nombre &rop, const mpf_nombre &op);

    static void exp2(mpf_nombre &rop, const mpf_nombre &op);

    static void exp10(mpf_nombre &rop, const mpf_nombre &op);

    static void expm1(mpf_nombre &rop, const mpf_nombre &op);

    static void puissance(mpf_nombre &rop, const mpf_nombre &op1, const mpf_nombre &op2);

    static void puissance(mpf_nombre &rop, const mpf_nombre &op1, unsigned long op2);

    static void puissance(mpf_nombre &rop, const mpf_nombre &op1, long op2);

    static void puissance(mpf_nombre &rop, const mpf_nombre &op1, const mpz_nombre &op2);

    static void puissance(mpf_nombre &rop, unsigned long op1, unsigned long op2);

    static void puissance(mpf_nombre &rop, unsigned long op1, const mpf_nombre &op2);

    static void sin(mpf_nombre &rop, const mpf_nombre &op);

    static void cos(mpf_nombre &rop, const mpf_nombre &op);

    static void tan(mpf_nombre &rop, const mpf_nombre &op);

    static void arcsin(mpf_nombre &rop, const mpf_nombre &op);

    static void arccos(mpf_nombre &rop, const mpf_nombre &op);

    static void arctan(mpf_nombre &rop, const mpf_nombre &op);

    static void arctan2(mpf_nombre &rop, const mpf_nombre &x, const mpf_nombre &y);

    static const mpf_nombre &pi();

    static const mpf_nombre &e();

    static const mpf_nombre &phi();

    static void zeta(mpf_nombre &rop, const mpf_nombre &op);

    static void zeta(mpf_nombre &rop, unsigned long op);

    static void factorielle(mpf_nombre &rop, unsigned long op);

    static void inverse(mpf_nombre &rop, const mpf_nombre &op);

    mpf_nombre floor() const;

    mpf_nombre ceil() const;
};

template<typename Type, typename = typename std::enable_if<!std::is_same<Type, mpf_nombre>::value, Type>::type>
inline mpf_nombre operator+(const Type &op1, const mpf_nombre &op2) {
    mpf_nombre rop;
    mpf_nombre::addition(rop, op2, op1);
    return rop;
}

template<typename Type, typename = typename std::enable_if<!std::is_same<Type, mpf_nombre>::value, Type>::type>
inline mpf_nombre operator-(const Type &op1, const mpf_nombre &op2) {
    mpf_nombre rop;
    mpf_nombre::soustraction(rop, op1, op2);
    return rop;
}

template<typename Type, typename = typename std::enable_if<!std::is_same<Type, mpf_nombre>::value, Type>::type>
inline mpf_nombre operator*(const Type &op1, const mpf_nombre &op2) {
    mpf_nombre rop;
    mpf_nombre::multiplication(rop, op2, op1);
    return rop;
}

template<typename Type, typename = typename std::enable_if<!std::is_same<Type, mpf_nombre>::value, Type>::type>
inline mpf_nombre operator/(const Type &op1, const mpf_nombre &op2) {
    mpf_nombre rop;
    mpf_nombre::division(rop, op1, op2);
    return rop;
}

template<typename Type>
inline bool operator==(const Type &a, const mpz_nombre &b) {
    return b.compare(a) == 0;
}

template<typename Type>
inline bool operator!=(const Type &a, const mpz_nombre &b) {
    return b.compare(a) != 0;
}

template<typename Type>
inline bool operator<(const Type &a, const mpz_nombre &b) {
    return b.compare(a) > 0;
}

template<typename Type>
inline bool operator>(const Type &a, const mpz_nombre &b) {
    return b.compare(a) < 0;
}

template<typename Type>
inline bool operator<=(const Type &a, const mpz_nombre &b) {
    return b.compare(a) >= 0;
}

template<typename Type>
inline bool operator>=(const Type &a, const mpz_nombre &b) {
    return b.compare(a) <= 0;
}

namespace std {
    void swap(mpf_nombre &op1, mpf_nombre &op2);

    mpf_nombre abs(const mpf_nombre &op);

    std::ostream &operator<<(std::ostream &os, const mpf_nombre &op);

    std::istream &operator>>(std::istream &is, mpf_nombre &op);

    mpf_nombre sqrt(const mpf_nombre &op);

    mpf_nombre cbrt(const mpf_nombre &op);

    mpf_nombre hypot(const mpf_nombre &x, const mpf_nombre &y);

    mpf_nombre log(const mpf_nombre &op);

    mpf_nombre log2(const mpf_nombre &op);

    mpf_nombre log10(const mpf_nombre &op);

    mpf_nombre exp(const mpf_nombre &op);

    mpf_nombre exp2(const mpf_nombre &op);

    mpf_nombre exp10(const mpf_nombre &op);

    mpf_nombre expm1(const mpf_nombre &op);

    mpf_nombre pow(const mpf_nombre &op1, const mpf_nombre &op2);

    mpf_nombre pow(const mpf_nombre &op1, unsigned long op2);

    mpf_nombre pow(const mpf_nombre &op1, signed long op2);

    mpf_nombre pow(const mpf_nombre &op1, const mpz_nombre &op2);

    mpf_nombre pow(unsigned long op1, const mpf_nombre &op2);

    mpf_nombre sin(const mpf_nombre &op);

    mpf_nombre cos(const mpf_nombre &op);

    mpf_nombre tan(const mpf_nombre &op);

    mpf_nombre asin(const mpf_nombre &op);

    mpf_nombre acos(const mpf_nombre &op);

    mpf_nombre atan(const mpf_nombre &op);

    mpf_nombre atan2(const mpf_nombre &x, const mpf_nombre &y);
}
