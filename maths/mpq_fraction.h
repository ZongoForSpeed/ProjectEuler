#pragma once

#include <gmp.h>
#include "mpz_nombre.h"

class mpq_fraction {
    mpq_ptr _data;

    void init();

    void clear();

public:
    mpq_fraction();

    ~mpq_fraction();

    mpq_fraction(const mpq_fraction &op);

    mpq_fraction(mpq_fraction &&op);

    mpq_fraction(const mpz_nombre &op);

    mpq_fraction(unsigned long int op1, unsigned long int op2);

    mpq_fraction(signed long int op1, unsigned long int op2);

    mpq_fraction(const std::string &op, int base = 10);

    mpq_fraction(double op);

    mpq_fraction &operator=(const mpq_fraction &op);

    mpq_fraction &operator=(mpq_fraction &&op) noexcept;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpq_fraction &operator=(const T &op) {
        set(op);
        return *this;
    }

    // region Setters
    void set(const mpq_t &op) {
        mpq_set(_data, op);
    }

    void set(const mpq_fraction &op) {
        mpq_set(_data, op._data);
    }

    void set(const mpz_t &op) {
        mpq_set_z(_data, op);
    }

    void set(const mpz_nombre &op) {
        mpq_set_z(_data, op.get_data());
    }

    void set(unsigned long int op) {
        mpq_set_ui(_data, op, 1ul);
    }

    void set(unsigned long int op1, unsigned long int op2) {
        mpq_set_ui(_data, op1, op2);
    }

    void set(signed long int op) {
        mpq_set_si(_data, op, 1ul);
    }

    void set(signed long int op1, unsigned long int op2) {
        mpq_set_si(_data, op1, op2);
    }

    void set(double op) {
        mpq_set_d(_data, op);
    }

    void set(const std::string &op, int base = 10) {
        mpq_set_str(_data, op.c_str(), base);
    }
    // endregion Setters

    void swap(mpq_fraction &op);

    friend void swap(mpq_fraction &a, mpq_fraction &b) {
        std::swap(a._data, b._data);
    }

    double get_double() const;

    std::string to_string(int base = 10) const;

    mpq_fraction &negation() {
        mpq_neg(_data, _data);
        return *this;
    }

    mpq_fraction operator-() const {
        mpq_fraction resultat;
        mpq_neg(resultat._data, _data);
        return resultat;
    }

    static mpq_fraction abs(const mpq_fraction &op) {
        mpq_fraction resultat;
        mpq_abs(resultat._data, op._data);
        return resultat;
    }

    mpq_fraction &inverse() {
        mpq_inv(_data, _data);
        return *this;
    }

    signed short signe() const {
        return mpq_sgn(_data);
    }

    mpq_fraction &operator+=(mpq_fraction &op);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpq_fraction &operator+=(const T &op) {
        mpq_fraction n(op);
        return this->operator+=(n);
    }

    mpq_fraction operator+(const mpq_fraction &op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpq_fraction operator+(const T &op) const {
        mpq_fraction resultat;
        mpq_fraction n(op);
        mpq_add(resultat._data, _data, n._data);
        mpq_canonicalize(resultat._data);
        return resultat;
    }

    mpq_fraction &operator-=(mpq_fraction &op);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpq_fraction &operator-=(const T &op) {
        mpq_fraction n(op);
        return this->operator-=(n);
    }

    mpq_fraction operator-(const mpq_fraction &op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpq_fraction operator-(const T &op) const {
        mpq_fraction resultat;
        mpq_fraction n(op);
        mpq_sub(resultat._data, _data, n._data);
        mpq_canonicalize(resultat._data);
        return resultat;
    }

    mpq_fraction &operator*=(mpq_fraction &op);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpq_fraction &operator*=(const T &op) {
        mpq_fraction n(op);
        return this->operator*=(n);
    }

    mpq_fraction operator*(const mpq_fraction &op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpq_fraction operator*(const T &op) const {
        mpq_fraction resultat;
        mpq_fraction n(op);
        mpq_mul(resultat._data, _data, n._data);
        mpq_canonicalize(resultat._data);
        return resultat;
    }

    mpq_fraction &operator/=(mpq_fraction &op);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpq_fraction &operator/=(const T &op) {
        mpq_fraction n(op);
        return this->operator/=(n);
    }

    mpq_fraction operator/(const mpq_fraction &op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpq_fraction operator/(const T &op) const {
        mpq_fraction resultat;
        mpq_fraction n(op);
        mpq_div(resultat._data, _data, n._data);
        mpq_canonicalize(resultat._data);
        return resultat;
    }

    int compare(const mpq_fraction &op) const;

    int compare(const mpz_nombre &op) const;

    int compare(unsigned long int n, unsigned long int d) const;

    int compare(signed long int n, unsigned long int d) const;

    int compare(signed long int op) const;

    int compare(unsigned long int op) const;

    template<typename T>
    [[nodiscard]] int compare(const T &op) const {
        mpz_nombre n(op);
        return compare(n);
    }

    bool egale(const mpq_fraction &op) const;

    bool operator==(const mpq_fraction &op) const;

    bool operator==(const mpz_nombre &op) const;

    bool operator<(const mpq_fraction &op) const;

    bool operator<(const mpz_nombre &op) const;

    bool operator<=(const mpq_fraction &op) const;

    bool operator<=(const mpz_nombre &op) const;

    bool operator>(const mpq_fraction &op) const;

    bool operator>(const mpz_nombre &op) const;

    bool operator>=(const mpq_fraction &op) const;

    bool operator>=(const mpz_nombre &op) const;

    mpq_ptr get_data();

    mpq_srcptr get_data() const;

    mpz_nombre numerateur() const {
        mpz_nombre resultat;
        mpq_get_num(resultat.get_data(), _data);
        return resultat;
    }

    mpz_nombre denominateur() const {
        mpz_nombre resultat;
        mpq_get_den(resultat.get_data(), _data);
        return resultat;
    }

};

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpq_fraction operator+(const T &op1, const mpq_fraction &op2) {
    return op2.operator+(op1);
}

inline mpq_fraction operator+(const mpz_nombre &op1, const mpq_fraction &op2) {
    return op2.operator+(op1);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpq_fraction operator-(const T &op1, const mpq_fraction &op2) {
    mpq_fraction n(op1);
    return n.operator-(op2);
}

inline mpq_fraction operator-(const mpz_nombre &op1, const mpq_fraction &op2) {
    mpq_fraction n(op1);
    return n.operator-(op2);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpq_fraction operator*(const T &op1, const mpq_fraction &op2) {
    return op2.operator*(op1);
}

inline mpq_fraction operator*(const mpz_nombre &op1, const mpq_fraction &op2) {
    return op2.operator*(op1);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpq_fraction operator/(const T &op1, const mpq_fraction &op2) {
    mpq_fraction n(op1);
    return n.operator/(op2);
}

inline mpq_fraction operator/(const mpz_nombre &op1, const mpq_fraction &op2) {
    mpq_fraction n(op1);
    return n.operator/(op2);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator==(const T &a, const mpq_fraction &b) {
    return b.compare(a) == 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator!=(const T &a, const mpq_fraction &b) {
    return b.compare(a) != 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator<(const T &a, const mpq_fraction &b) {
    return b.compare(a) > 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator>(const T &a, const mpq_fraction &b) {
    return b.compare(a) < 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator<=(const T &a, const mpq_fraction &b) {
    return b.compare(a) >= 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator>=(const T &a, const mpq_fraction &b) {
    return b.compare(a) <= 0;
}

namespace std {
    mpq_fraction abs(const mpq_fraction &op);

    void swap(mpq_fraction &op1, mpq_fraction &op2);

    std::ostream &operator<<(std::ostream &os, const mpq_fraction &op);

    std::istream &operator>>(std::istream &is, mpq_fraction &op);
}
