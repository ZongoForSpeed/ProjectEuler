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

    template<typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    mpf_nombre(const T x) {
        _data = new __mpfr_struct();
        mpz_nombre tmp(x);
        mpfr_init_set_z(_data, tmp.get_data(), DEFAULT_ROUNDING);
    }

    mpf_nombre(mpf_nombre &&op) : _data(std::exchange(op._data, nullptr)) {

    }

    ~mpf_nombre();

    mpf_nombre &operator=(const mpf_nombre &op);

    template<typename T>
    mpf_nombre &operator=(const T &op) {
        set(op);
        return *this;
    }

    void set(const mpf_nombre &op);

    void set(unsigned long op);

    void set(long op);

    void set(float op);

    void set(double op);

    void set(long double op);

    void set(const mpz_nombre &op);

    void set(const mpq_fraction &op);

    void set(const std::string &op, int base = 10);

    template<typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    void set(T x) {
        mpz_nombre tmp(x);
        set(tmp);
    }

    void swap(mpf_nombre &op);

    mpfr_ptr get_data();

    mpfr_srcptr get_data() const;

    float get_float() const;

    double get_double() const;

    long double get_long_double() const;

    long get_signed_long() const;

    unsigned long get_unsigned_long() const;

    mpz_nombre get_mpz_nombre();

    mpq_fraction get_mpq_fraction();

    std::string to_string(size_t precision = 15) const;

    mpf_nombre operator-() const;

    mpf_nombre &operator+=(const mpf_nombre &op);

    mpf_nombre operator+(const mpf_nombre &op) const;

    mpf_nombre &operator+=(unsigned long op);

    mpf_nombre operator+(unsigned long op) const;

    mpf_nombre &operator+=(signed long op);

    mpf_nombre operator+(signed long op) const;

    mpf_nombre &operator+=(double op);

    mpf_nombre operator+(double op) const;

    mpf_nombre &operator+=(const mpq_fraction &op);

    mpf_nombre operator+(const mpq_fraction &op) const;

    mpf_nombre &operator+=(const mpz_nombre &op);

    mpf_nombre operator+(const mpz_nombre &op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpf_nombre &operator+=(T op) {
        mpf_nombre tmp(op);
        return operator+=(tmp);
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpf_nombre operator+(T op) const {
        mpf_nombre tmp(op);
        return operator+(tmp);
    }

    mpf_nombre &operator-=(const mpf_nombre &op);

    mpf_nombre operator-(const mpf_nombre &op) const;

    mpf_nombre &operator-=(unsigned long op);

    mpf_nombre operator-(unsigned long op) const;

    mpf_nombre &operator-=(signed long op);

    mpf_nombre operator-(signed long op) const;

    mpf_nombre &operator-=(double op);

    mpf_nombre operator-(double op) const;

    mpf_nombre &operator-=(const mpq_fraction &op);

    mpf_nombre operator-(const mpq_fraction &op) const;

    mpf_nombre &operator-=(const mpz_nombre &op);

    mpf_nombre operator-(const mpz_nombre &op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpf_nombre &operator-=(T op) {
        mpf_nombre tmp(op);
        return operator-=(tmp);
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpf_nombre operator-(T op) const {
        mpf_nombre tmp(op);
        return operator-(tmp);
    }

    mpf_nombre &operator*=(const mpf_nombre &op);

    mpf_nombre operator*(const mpf_nombre &op) const;

    mpf_nombre &operator*=(unsigned long op);

    mpf_nombre operator*(unsigned long op) const;

    mpf_nombre &operator*=(signed long op);

    mpf_nombre operator*(signed long op) const;

    mpf_nombre &operator*=(double op);

    mpf_nombre operator*(double op) const;

    mpf_nombre &operator*=(const mpq_fraction &op);

    mpf_nombre operator*(const mpq_fraction &op) const;

    mpf_nombre &operator*=(const mpz_nombre &op);

    mpf_nombre operator*(const mpz_nombre &op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpf_nombre &operator*=(T op) {
        mpf_nombre tmp(op);
        return operator*=(tmp);
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpf_nombre operator*(T op) const {
        mpf_nombre tmp(op);
        return operator*(tmp);
    }

    mpf_nombre &operator/=(const mpf_nombre &op);

    mpf_nombre operator/(const mpf_nombre &op) const;

    mpf_nombre &operator/=(unsigned long op);

    mpf_nombre operator/(unsigned long op) const;

    mpf_nombre &operator/=(signed long op);

    mpf_nombre operator/(signed long op) const;

    mpf_nombre &operator/=(double op);

    mpf_nombre operator/(double op) const;

    mpf_nombre &operator/=(const mpq_fraction &op);

    mpf_nombre operator/(const mpq_fraction &op) const;

    mpf_nombre &operator/=(const mpz_nombre &op);

    mpf_nombre operator/(const mpz_nombre &op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpf_nombre &operator/=(T op) {
        mpf_nombre tmp(op);
        return operator/=(tmp);
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpf_nombre operator/(T op) const {
        mpf_nombre tmp(op);
        return operator/(tmp);
    }

    int compare(const mpf_nombre &op) const;

    int compare(unsigned long op) const;

    int compare(signed long op) const;

    int compare(double op) const;

    int compare(long double op) const;

    int compare(const mpz_nombre &op) const;

    int compare(const mpq_fraction &op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    int compare(const T &op) const {
        mpf_nombre tmp(op);
        return mpfr_cmp(_data, tmp.get_data());
    }

    bool operator>(const mpf_nombre &op) const;

    template<typename T>
    bool operator>(const T &op) const {
        return compare(op) > 0;
    }

    bool operator>=(const mpf_nombre &op) const;

    template<typename T>
    bool operator>=(const T &op) const {
        return compare(op) >= 0;
    }

    bool operator<(const mpf_nombre &op) const;

    template<typename T>
    bool operator<(const T &op) const {
        return compare(op) < 0;
    }

    bool operator<=(const mpf_nombre &op) const;

    template<typename T>
    bool operator<=(const T &op) const {
        return compare(op) <= 0;
    }

    bool operator==(const mpf_nombre &op) const;

    template<typename T>
    bool operator==(const T &op) const {
        return compare(op) == 0;
    }

    bool operator!=(const mpf_nombre &op) const;

    template<typename T>
    bool operator!=(const T &op) const {
        return compare(op) != 0;
    }

    static void abs( mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_abs(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void racine_carre(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_sqrt(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void racine_cubique(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_cbrt(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void racine(mpf_nombre &rop, const mpf_nombre &op, unsigned long n) {
        mpfr_rootn_ui(rop._data, op._data, n, DEFAULT_ROUNDING);
    }

    static void hypothenuse(mpf_nombre &rop, const mpf_nombre &x, const mpf_nombre &y) {
        mpfr_hypot(rop._data, x._data, y._data, DEFAULT_ROUNDING);
    }

    static void log(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_log(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void log2(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_log2(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void log10(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_log10(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void exp(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_exp(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void exp2(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_exp2(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void exp10(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_exp10(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void expm1(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_expm1(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static  void puissance(mpf_nombre &rop, const mpf_nombre &op1, const mpf_nombre &op2) {
        mpfr_pow(rop._data, op1._data, op2._data, DEFAULT_ROUNDING);
    }

    static void puissance(mpf_nombre &rop, const mpf_nombre &op1, unsigned long op2) {
        mpfr_pow_ui(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    static void puissance(mpf_nombre &rop, const mpf_nombre &op1, long op2) {
        mpfr_pow_si(rop._data, op1._data, op2, DEFAULT_ROUNDING);
    }

    static void puissance(mpf_nombre &rop, const mpf_nombre &op1, const mpz_nombre &op2) {
        mpfr_pow_z(rop._data, op1._data, op2.get_data(), DEFAULT_ROUNDING);
    }

    static void puissance(mpf_nombre &rop, unsigned long op1, unsigned long op2) {
        mpfr_ui_pow_ui(rop._data, op1, op2, DEFAULT_ROUNDING);
    }

    static void puissance(mpf_nombre &rop, unsigned long op1, const mpf_nombre &op2) {
        mpfr_ui_pow(rop._data, op1, op2._data, DEFAULT_ROUNDING);
    }

    static void sin(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_sin(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void cos(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_cos(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static  void tan(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_tan(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void arcsin(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_asin(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void arccos(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_acos(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void arctan(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_atan(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void arctan2(mpf_nombre &rop, const mpf_nombre &x, const mpf_nombre &y) {
        mpfr_atan2(rop._data, x._data, y._data, DEFAULT_ROUNDING);
    }
    
    static const mpf_nombre &pi();

    static const mpf_nombre &e();

    static const mpf_nombre & phi();

    static void zeta(mpf_nombre& rop, const mpf_nombre& op) {
        mpfr_zeta(rop._data, op._data, DEFAULT_ROUNDING);
    }

    static void zeta(mpf_nombre& rop, unsigned long op) {
        mpfr_zeta_ui(rop._data, op, DEFAULT_ROUNDING);
    }

    static void factorielle(mpf_nombre& rop, unsigned long op) {
        mpfr_fac_ui(rop._data, op, DEFAULT_ROUNDING);
    }

    static void inverse(mpf_nombre &rop, const mpf_nombre &op) {
        mpfr_ui_div(rop._data, 1, op._data, DEFAULT_ROUNDING);
    }

};

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpf_nombre operator+(const T &op1, const mpf_nombre &op2) {
    return op2.operator+(op1);
}

inline mpf_nombre operator+(const mpz_nombre &op1, const mpf_nombre &op2) {
    return op2.operator+(op1);
}

inline mpf_nombre operator+(const mpq_fraction &op1, const mpf_nombre &op2) {
    return op2.operator+(op1);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpf_nombre operator-(const T &op1, const mpf_nombre &op2) {
    mpf_nombre n(op1);
    return n.operator-=(op2);
}

inline mpf_nombre operator-(const mpz_nombre &op1, const mpf_nombre &op2) {
    mpf_nombre n(op1);
    return n.operator-=(op2);
}

inline mpf_nombre operator-(const mpq_fraction &op1, const mpf_nombre &op2) {
    mpf_nombre n(op1);
    return n.operator-=(op2);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpf_nombre operator*(const T &op1, const mpf_nombre &op2) {
    return op2.operator*(op1);
}

inline mpf_nombre operator*(const mpz_nombre &op1, const mpf_nombre &op2) {
    return op2.operator*(op1);
}

inline mpf_nombre operator*(const mpq_fraction &op1, const mpf_nombre &op2) {
    return op2.operator*(op1);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpf_nombre operator/(const T &op1, const mpf_nombre &op2) {
    mpf_nombre n(op1);
    return n /= (op2);
}

inline mpf_nombre operator/(const mpz_nombre &op1, const mpf_nombre &op2) {
    mpf_nombre n(op1);
    return n /= (op2);
}

inline mpf_nombre operator/(const mpq_fraction &op1, const mpf_nombre &op2) {
    mpf_nombre n(op1);
    return n /= (op2);
}

template<typename T>
inline bool operator==(const T &a, const mpz_nombre &b) {
    return b.compare(a) == 0;
}

template<typename T>
inline bool operator!=(const T &a, const mpz_nombre &b) {
    return b.compare(a) != 0;
}

template<typename T>
inline bool operator<(const T &a, const mpz_nombre &b) {
    return b.compare(a) > 0;
}

template<typename T>
inline bool operator>(const T &a, const mpz_nombre &b) {
    return b.compare(a) < 0;
}

template<typename T>
inline bool operator<=(const T &a, const mpz_nombre &b) {
    return b.compare(a) >= 0;
}

template<typename T>
inline bool operator>=(const T &a, const mpz_nombre &b) {
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
