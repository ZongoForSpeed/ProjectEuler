#pragma once

#include <mpfr.h>
#include <algorithm>
#include <type_traits>
#include <sstream>
#include "mp_nombre.h"

class mp_decimal {
    mpfr_t _data{};

public:
    static void init() {
        mpfr_set_default_prec(512);
    }

    static void clear() {
        mpfr_free_cache();
    }

    static const mp_decimal PI;
    static const mp_decimal E;
    static const mp_decimal EULER;
    static const mp_decimal CATALAN;

    mp_decimal();

    mp_decimal(const mp_decimal &op);

    explicit mp_decimal(unsigned long int op);

    explicit mp_decimal(long int op);

    explicit mp_decimal(double op);

    explicit mp_decimal(long double op);

    explicit mp_decimal(const mp_nombre &op);

    explicit mp_decimal(const std::string &op, int base = 10);

    template<typename Nombre>
    explicit mp_decimal(const Nombre &op) : mp_decimal() {
        set(op);
    }

    virtual ~mp_decimal();

    void set(const mp_decimal &op);

    void set(unsigned long int op);

    void set(long int op);

    void set(float op);

    void set(double op);

    void set(long double op);

    void set(const mp_nombre &op);

    void set(const std::string &op, int base = 10);

    template<typename Nombre>
    void set(const Nombre &op) {
        set(op, std::is_integral<Nombre>());
    }

    long int get_long() const;

    unsigned long int get_unsigned_long() const;

    float get_float() const;

    double get_double() const;

    long double get_long_double() const;

    mp_nombre get_mp_nombre() const;

    template<typename Nombre>
    Nombre get() {
        return get<Nombre>(std::is_integral<Nombre>());
    }

    std::string to_string(size_t precision = 8) const;

    int compare(unsigned long op) const;

    int compare(long op) const;

    int compare(double op) const;

    int compare(long double op) const;

    int compare(const mp_nombre &op) const;

    template<typename Nombre>
    int compare(const Nombre &a) const {
        return compare(a, std::is_integral<Nombre>());
    }

    template<typename N>
    bool operator<(const N &op) const {
        return compare(op) < 0;
    }

    template<typename N>
    bool operator>(const N &op) const {
        return compare(op) > 0;
    }

    template<typename N>
    bool operator<=(const N &op) const {
        return compare(op) <= 0;
    }

    template<typename N>
    bool operator>=(const N &op) const {
        return compare(op) >= 0;
    }

    template<typename N>
    bool operator==(const N &op) const {
        return compare(op) == 0;
    }

    template<typename N>
    bool operator!=(const N &op) const {
        return compare(op) != 0;
    }

    bool operator>(const mp_decimal &op) const;

    bool operator>=(const mp_decimal &op) const;

    bool operator<(const mp_decimal &op) const;

    bool operator<=(const mp_decimal &op) const;

    bool operator==(const mp_decimal &op) const;

    bool operator!=(const mp_decimal &op) const;

    mp_decimal &operator=(const mp_decimal &op) {
        set(op);
        return *this;
    }

    static mp_decimal abs(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_abs(resultat._data, op._data, MPFR_RNDN);
        return resultat;
    }

    mp_decimal &negation();

    mp_decimal &inverse();

    mp_decimal operator-() const {
        mp_decimal resultat;
        mpfr_neg(resultat._data, _data, MPFR_RNDN);
        return resultat;
    }

    mpfr_ptr operator*() {
        return _data;
    }

    mpfr_srcptr operator*() const {
        return _data;
    }

    void swap(mp_decimal &op) {
        mpfr_swap(_data, op._data);
    }

    static mp_decimal racine_carre(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_sqrt(resultat._data, op._data, MPFR_RNDN);
        return resultat;
    }

    static mp_decimal racine_cubique(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_cbrt(resultat._data, op._data, MPFR_RNDN);
        return resultat;
    }

    static mp_decimal racine(const mp_decimal &op, unsigned long int n) {
        mp_decimal resultat;
        mpfr_root(resultat._data, op._data, n, MPFR_RNDN);
        return resultat;
    }

    template<typename Nombre>
    mp_decimal &operator+=(const Nombre &op) {
        mp_decimal::addition(*this, *this, op);
        return *this;
    }

    template<typename Nombre>
    mp_decimal operator+(const Nombre &op) const {
        mp_decimal resultat;
        mp_decimal::addition(resultat, *this, op);
        return resultat;
    }

    template<typename Nombre>
    mp_decimal &operator-=(const Nombre &op) {
        mp_decimal::soustraction(*this, *this, op);
        return *this;
    }

    template<typename Nombre>
    mp_decimal operator-(const Nombre &op) const {
        mp_decimal resultat;
        mp_decimal::soustraction(resultat, *this, op);
        return resultat;
    }

    template<typename Nombre>
    mp_decimal &operator*=(const Nombre &op) {
        mp_decimal::multiplication(*this, *this, op);
        return *this;
    }

    template<typename Nombre>
    mp_decimal operator*(const Nombre &op) const {
        mp_decimal resultat;
        mp_decimal::multiplication(resultat, *this, op);
        return resultat;
    }

    template<typename Nombre>
    mp_decimal &operator/=(const Nombre &op) {
        mp_decimal::division(*this, *this, op);
        return *this;
    }

    template<typename Nombre>
    mp_decimal operator/(const Nombre &op) const {
        mp_decimal resultat;
        mp_decimal::division(resultat, *this, op);
        return resultat;
    }

    static void negation(mp_decimal &rop, const mp_decimal &op);

    static void inverse(mp_decimal &rop, const mp_decimal &op);

    static void addition(mp_decimal &rop, const mp_decimal &op1, const mp_decimal &op2);

    static void addition(mp_decimal &rop, const mp_decimal &op1, unsigned long op2);

    static void addition(mp_decimal &rop, const mp_decimal &op1, long op2);

    static void addition(mp_decimal &rop, const mp_decimal &op1, double op2);

    static void addition(mp_decimal &rop, const mp_decimal &op1, const mp_nombre &op2);

    template<typename Nombre>
    static void addition(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2) {
        addition(rop, op1, op2, std::is_integral<Nombre>());
    }

    static void soustraction(mp_decimal &rop, const mp_decimal &op1, const mp_decimal &op2);

    static void soustraction(mp_decimal &rop, unsigned long int op1, const mp_decimal &op2);

    static void soustraction(mp_decimal &rop, const mp_decimal &op1, unsigned long int op2);

    static void soustraction(mp_decimal &rop, long int op1, const mp_decimal &op2);

    static void soustraction(mp_decimal &rop, const mp_decimal &op1, long int op2);

    static void soustraction(mp_decimal &rop, double op1, const mp_decimal &op2);

    static void soustraction(mp_decimal &rop, const mp_decimal &op1, double op2);

    static void soustraction(mp_decimal &rop, const mp_nombre &op1, const mp_decimal &op2);

    static void soustraction(mp_decimal &rop, const mp_decimal &op1, const mp_nombre &op2);

    template<typename Nombre>
    static void soustraction(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2) {
        soustraction(rop, op1, op2, std::is_integral<Nombre>());
    }

    template<typename Nombre>
    static void soustraction(mp_decimal &rop, const Nombre &op1, const mp_decimal &op2) {
        soustraction(rop, op2, op1);
        negation(rop, rop);
    }

    static void multiplication(mp_decimal &rop, const mp_decimal &op1, const mp_decimal &op2);

    static void multiplication(mp_decimal &rop, const mp_decimal &op1, unsigned long op2);

    static void multiplication(mp_decimal &rop, const mp_decimal &op1, long op2);

    static void multiplication(mp_decimal &rop, const mp_decimal &op1, double op2);

    static void multiplication(mp_decimal &rop, const mp_decimal &op1, const mp_nombre &op2);

    template<typename Nombre>
    static void multiplication(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2) {
        multiplication(rop, op1, op2, std::is_integral<Nombre>());
    }

    template<typename Nombre>
    static void multiplication(mp_decimal &rop, const Nombre &op1, const mp_decimal &op2) {
        multiplication(rop, op2, op1);
    }

    static void division(mp_decimal &rop, const mp_decimal &op1, const mp_decimal &op2);

    static void division(mp_decimal &rop, unsigned long int op1, const mp_decimal &op2);

    static void division(mp_decimal &rop, const mp_decimal &op1, unsigned long int op2);

    static void division(mp_decimal &rop, long int op1, const mp_decimal &op2);

    static void division(mp_decimal &rop, const mp_decimal &op1, long int op2);

    static void division(mp_decimal &rop, double op1, const mp_decimal &op2);

    static void division(mp_decimal &rop, const mp_decimal &op1, double op2);

    static void division(mp_decimal &rop, const mp_decimal &op1, const mp_nombre &op2);

    template<typename Nombre>
    static void division(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2) {
        division(rop, op1, op2, std::is_integral<Nombre>());
    }

    template<typename Nombre>
    static void division(mp_decimal &rop, const Nombre &op1, const mp_decimal &op2) {
        division(rop, op2, op1);
        inverse(rop, rop);
    }

    static void puissance(mp_decimal &rop, const mp_decimal &op1, const mp_decimal &op2) {
        mpfr_pow(rop._data, op1._data, op2._data, MPFR_RNDN);
    }

    static void puissance(mp_decimal &rop, const mp_decimal &op1, unsigned long int op2) {
        mpfr_pow_ui(rop._data, op1._data, op2, MPFR_RNDN);
    }

    static void puissance(mp_decimal &rop, const mp_decimal &op1, long int op2) {
        mpfr_pow_si(rop._data, op1._data, op2, MPFR_RNDN);
    }

    static void puissance(mp_decimal &rop, const mp_decimal &op1, const mp_nombre &op2) {
        mpfr_pow_z(rop._data, op1._data, op2.get_data(), MPFR_RNDN);
    }

    static void puissance(mp_decimal &rop, unsigned long int op1, unsigned long int op2) {
        mpfr_ui_pow_ui(rop._data, op1, op2, MPFR_RNDN);
    }

    static void puissance(mp_decimal &rop, unsigned long int op1, const mp_decimal &op2) {
        mpfr_ui_pow(rop._data, op1, op2._data, MPFR_RNDN);
    }

    static mp_decimal puissance(const mp_decimal & op1, unsigned long int op2) {
        mp_decimal resultat;
        puissance(resultat, op1, op2);
        return resultat;
    }

private:
    template<typename Nombre>
    int compare(const Nombre &op, std::false_type /*is_integral*/) const {
        static_assert("Not implemented");
        mp_decimal n(op);
        return compare(n);
    }

    template<typename Nombre>
    int compare(const Nombre &op, std::true_type /*is_integral*/) const {
        mp_nombre n(op);
        return compare(n);
    }

    template<typename Nombre>
    void set(const Nombre &op, std::false_type /*is_integral*/) {
        static_assert("Not implemented");
        mp_nombre n(op);
        return set(n);
    }

    template<typename Nombre>
    void set(const Nombre &op, std::true_type /*is_integral*/) {
        mp_nombre n(op);
        set(n);
    }

    template<typename Nombre>
    Nombre get(std::false_type /*is_integral*/) const {
        static_assert("Not implemented");
        return get_mp_nombre().get<Nombre>();
    }

    template<typename Nombre>
    Nombre get(std::true_type /*is_integral*/) const {
        return get_mp_nombre().get<Nombre>();
    }

    template<typename Nombre>
    static void addition(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2, std::false_type /*is_integral*/) {
        static_assert("Not implemented");
        mp_decimal n(op2);
        addition(rop, op1, n);
    }


    template<typename Nombre>
    static void addition(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2, std::true_type /*is_integral*/) {
        mp_nombre n(op2);
        addition(rop, op1, n);
    }

    template<typename Nombre>
    static void
    soustraction(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2, std::false_type /*is_integral*/) {
        static_assert("Not implemented");
        mp_decimal n(op2);
        soustraction(rop, op1, n);
    }

    template<typename Nombre>
    static void
    soustraction(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2, std::true_type /*is_integral*/) {
        mp_nombre n(op2);
        soustraction(rop, op1, n);
    }

    template<typename Nombre>
    static void
    multiplication(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2, std::false_type /*is_integral*/) {
        static_assert("Not implemented");
        mp_decimal n(op2);
        multiplication(rop, op1, n);
    }

    template<typename Nombre>
    static void
    multiplication(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2, std::true_type /*is_integral*/) {
        mp_nombre n(op2);
        multiplication(rop, op1, n);
    }

    template<typename Nombre>
    static void division(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2, std::false_type /*is_integral*/) {
        static_assert("Not implemented");
        mp_decimal n(op2);
        division(rop, op1, n);
    }

    template<typename Nombre>
    static void division(mp_decimal &rop, const mp_decimal &op1, const Nombre &op2, std::true_type /*is_integral*/) {
        mp_nombre n(op2);
        division(rop, op1, n);
    }

    static mp_decimal calcul_pi();

    static mp_decimal calcul_catalan();

    static mp_decimal calcul_e();

    static mp_decimal calcul_euler();
};

template<typename Nombre, typename = typename std::enable_if<std::is_arithmetic<Nombre>::value, Nombre>::type>
inline mp_decimal operator+(const Nombre &op1, const mp_decimal &op2) {
    mp_decimal resultat;
    mp_decimal::addition(resultat, op2, op1);
    return resultat;
}

template<typename Nombre, typename = typename std::enable_if<std::is_arithmetic<Nombre>::value, Nombre>::type>
inline mp_decimal operator-(const Nombre &op1, const mp_decimal &op2) {
    mp_decimal resultat;
    mp_decimal::soustraction(resultat, op1, op2);
    return resultat;
}

template<typename Nombre, typename = typename std::enable_if<std::is_arithmetic<Nombre>::value, Nombre>::type>
inline mp_decimal operator*(const Nombre &op1, const mp_decimal &op2) {
    mp_decimal resultat;
    mp_decimal::multiplication(resultat, op2, op1);
    return resultat;
}

template<typename Nombre, typename = typename std::enable_if<std::is_arithmetic<Nombre>::value, Nombre>::type>
inline mp_decimal operator/(const Nombre &op1, const mp_decimal &op2) {
    mp_decimal resultat;
    mp_decimal::division(resultat, op2, op1);
    return resultat;
}

namespace std {
    mp_decimal abs(const mp_decimal &op);

    void swap(mp_decimal &op1, mp_decimal &op2);

    mp_decimal sqrt(const mp_decimal &op);

    mp_decimal cbrt(const mp_decimal &op);

    mp_decimal exp(const mp_decimal &op);

    mp_decimal exp2(const mp_decimal &op);

    mp_decimal expm1(const mp_decimal &op);

    mp_decimal log(const mp_decimal &op);

    mp_decimal log2(const mp_decimal &op);

    mp_decimal log10(const mp_decimal &op);

    mp_decimal log1p(const mp_decimal &op);

    mp_decimal sin(const mp_decimal &op);

    mp_decimal cos(const mp_decimal &op);

    mp_decimal tan(const mp_decimal &op);

    mp_decimal asin(const mp_decimal &op);

    mp_decimal acos(const mp_decimal &op);

    mp_decimal atan(const mp_decimal &op);

    mp_decimal atan2(const mp_decimal &op1, const mp_decimal &op2);

    std::ostream &operator<<(std::ostream &os, const mp_decimal &op);

    std::istream &operator>>(std::istream &is, mp_decimal &op);

    template<>
    class numeric_limits<mp_decimal> : public numeric_limits<long double> {
    public:
        static constexpr int digits = INT_MAX;
        static constexpr int digits10 = INT_MAX;

        static mp_nombre max() {
            return mp_nombre::puissance(2, digits);
        }

        static mp_nombre min() {
            return max().negation();
        }

        static mp_nombre lowest() {
            return min();
        }
    };

    inline string to_string(const mp_decimal &op) {
        return op.to_string();
    }
}
