#pragma once

#include <utility>
#include <iostream>

class nombre_modulaire {
    template<typename Type>
    void set(Type op, std::false_type /*is_signed*/) {
        _value = op % _modulo;
    }

    template<typename Type>
    void set(Type op, std::true_type /*is_signed*/) {
        bool negatif = (op < 0);
        op = std::abs(op);
        _value = static_cast<size_t>(op) % _modulo;
        if (negatif) {
            _value = _modulo - _value;
        }
    }

    static std::pair<size_t, nombre_modulaire> factoriel2(size_t modulo, size_t n);

    static void meme_mod(const nombre_modulaire &n1, const nombre_modulaire &n2);

    void meme_mod(const nombre_modulaire &n) const;

    size_t _modulo;
    unsigned long long _value;
public:
    template<typename Type>
    nombre_modulaire(size_t modulo, Type n) : _modulo(modulo), _value(0) {
        set(n);
    }

    nombre_modulaire(const nombre_modulaire &n);

    //nombre_modulaire(size_t modulo) : _modulo(modulo), _value(0) {
    //}

    template<typename T>
    void set(T x) {
        static_assert(std::is_integral<T>::value, "Integer required.");
        set(x, std::is_signed<T>());
    }

    static nombre_modulaire puissance(nombre_modulaire a, size_t n);

    [[nodiscard]] unsigned long long value() const;

    [[nodiscard]] size_t modulo() const;

    nombre_modulaire operator-() const;

    nombre_modulaire &operator=(const nombre_modulaire &op);

    template<typename T>
    nombre_modulaire &operator=(const T &op) {
        set(op);
        return *this;
    }

    nombre_modulaire &operator+=(const nombre_modulaire &op);

    nombre_modulaire &operator-=(const nombre_modulaire &op);

    nombre_modulaire &operator*=(const nombre_modulaire &op);

    nombre_modulaire &operator/=(const nombre_modulaire &op);

    nombre_modulaire operator+(const nombre_modulaire &op) const;

    nombre_modulaire operator-(const nombre_modulaire &op) const;

    nombre_modulaire operator*(const nombre_modulaire &op) const;

    nombre_modulaire operator/(const nombre_modulaire &op) const;

    template<typename T>
    nombre_modulaire &operator+=(const T &op) {
        nombre_modulaire n(_modulo, op);
        return this->operator+=(n);
    }

    template<typename T>
    nombre_modulaire &operator-=(const T &op) {
        nombre_modulaire n(_modulo, op);
        return this->operator-=(n);
    }

    template<typename T>
    nombre_modulaire &operator*=(const T &op) {
        nombre_modulaire n(_modulo, op);
        return this->operator*=(n);
    }

    template<typename T>
    nombre_modulaire &operator/=(const T &op) {
        nombre_modulaire n(_modulo, op);
        return this->operator/=(n);
    }

    template<typename T>
    nombre_modulaire operator+(const T &op) const {
        nombre_modulaire n(_modulo, op);
        return this->operator+(n);
    }

    template<typename T>
    nombre_modulaire operator-(const T &op) const {
        nombre_modulaire n(_modulo, op);
        return this->operator-(n);
    }

    template<typename T>
    nombre_modulaire operator*(const T &op) const {
        nombre_modulaire n(_modulo, op);
        return this->operator*(n);
    }

    template<typename T>
    nombre_modulaire operator/(const T &op) const {
        nombre_modulaire n(_modulo, op);
        return this->operator/(n);
    }

    static nombre_modulaire factoriel(size_t modulo, size_t n);

    static nombre_modulaire arrangement(size_t modulo, size_t n, size_t k);

    static nombre_modulaire coefficient_binomial(size_t modulo, size_t n, size_t k);
};

template<typename T>
inline nombre_modulaire operator+(const T &op1, const nombre_modulaire &op2) {
    return op2.operator+(op1);
}

template<typename T>
inline nombre_modulaire operator-(const T &op1, const nombre_modulaire &op2) {
    nombre_modulaire n(op1);
    return n.operator-(op2);
}

template<typename T>
inline nombre_modulaire operator*(const T &op1, const nombre_modulaire &op2) {
    return op2.operator*(op1);
}

template<typename T>
inline nombre_modulaire operator/(const T &op1, const nombre_modulaire &op2) {
    nombre_modulaire n(op1);
    return n.operator/(op2);
}

std::ostream &operator<<(std::ostream &os, const nombre_modulaire &a);
