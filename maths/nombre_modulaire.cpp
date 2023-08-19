#include "numerique.h"
#include "nombre_modulaire.h"

#include <boost/multiprecision/integer.hpp>

std::ostream &operator<<(std::ostream &os, const nombre_modulaire &a) {
    os << a.value() << "[" << a.modulo() << "]";
    return os;
}

std::pair<size_t, nombre_modulaire> nombre_modulaire::factoriel2(size_t modulo, size_t n) {
    nombre_modulaire resultat(modulo, 1);
    size_t exposant = 0;
    bool sgn = false;
    while (n > 0) {
        for (size_t i = n % modulo; i > 1; --i)
            resultat *= i;
        n /= modulo;
        sgn ^= (n % 2 == 1);
        exposant += n;
    }
    return std::make_pair(exposant, sgn ? -resultat : resultat);
}

void nombre_modulaire::meme_mod(const nombre_modulaire &n1, const nombre_modulaire &n2) {
    if (n1._modulo != n2._modulo) {
        throw std::domain_error("Modulo different !");
    }
}

void nombre_modulaire::meme_mod(const nombre_modulaire &n) const {
    meme_mod(*this, n);
}

nombre_modulaire::nombre_modulaire(const nombre_modulaire &n) : _modulo(n._modulo), _value(n._value) {
}

nombre_modulaire nombre_modulaire::puissance(nombre_modulaire a, size_t n) {
    nombre_modulaire result(a._modulo, 1);
    while (n > 0) {
        if (n % 2)
            result *= a;
        a *= a;
        n /= 2;
    }
    return result;
}

nombre_modulaire nombre_modulaire::puissance(size_t a, size_t n, size_t modulo) {
    nombre_modulaire result(modulo, 1);
    nombre_modulaire p(modulo, a);
    while (n > 0) {
        if (n % 2)
            result *= p;
        p *= a;
        n /= 2;
    }
    return result;
}


unsigned long long nombre_modulaire::value() const { return _value; }

size_t nombre_modulaire::modulo() const { return _modulo; }

nombre_modulaire nombre_modulaire::operator-() const {
    return nombre_modulaire(_modulo, _modulo - value());
}

nombre_modulaire &nombre_modulaire::operator=(const nombre_modulaire &op) {
    // meme_mod(op);

    _modulo = op._modulo;
    _value = op._value;
    return *this;
}

nombre_modulaire &nombre_modulaire::operator+=(const nombre_modulaire &op) {
    meme_mod(op);

    _value += op._value;
    if (_value >= _modulo) _value -= _modulo;
    return *this;
}

nombre_modulaire &nombre_modulaire::operator-=(const nombre_modulaire &op) {
    meme_mod(op);

    _value = _value < op._value ? _modulo + _value - op._value : _value - op._value;
    return *this;
}

nombre_modulaire &nombre_modulaire::operator*=(const nombre_modulaire &op) {
    meme_mod(op);

    uint128_t c = 0;
    boost::multiprecision::multiply(c, _value, op._value);
    _value = boost::multiprecision::integer_modulus(c, _modulo);

    return *this;
}

nombre_modulaire &nombre_modulaire::operator/=(const nombre_modulaire &op) {
    meme_mod(op);
    return operator*=(puissance(op, _modulo - 2));
}

nombre_modulaire nombre_modulaire::operator+(const nombre_modulaire &op) const {
    nombre_modulaire result(*this);
    result.operator+=(op);
    return result;
}

nombre_modulaire nombre_modulaire::operator-(const nombre_modulaire &op) const {
    nombre_modulaire result(*this);
    result.operator-=(op);
    return result;
}

nombre_modulaire nombre_modulaire::operator*(const nombre_modulaire &op) const {
    nombre_modulaire result(*this);
    result.operator*=(op);
    return result;
}

nombre_modulaire nombre_modulaire::operator/(const nombre_modulaire &op) const {
    nombre_modulaire result(*this);
    result.operator/=(op);
    return result;
}

nombre_modulaire nombre_modulaire::factoriel(size_t modulo, size_t n) {
    auto[exposant, resultat] = factoriel2(modulo, n);
    if (exposant > 0) {
        return nombre_modulaire(modulo, 0);
    } else {
        return resultat;
    }
}

nombre_modulaire nombre_modulaire::arrangement(size_t modulo, size_t n, size_t k) {
    auto fn = factoriel2(modulo, n);
    auto fnk = factoriel2(modulo, n - k);
    if (fn.first - fnk.first > 0)
        return nombre_modulaire(modulo, 0);
    return fn.second / fnk.second;
}

nombre_modulaire nombre_modulaire::coefficient_binomial(size_t modulo, size_t n, size_t k) {
    auto fn = factoriel2(modulo, n);
    auto fk = factoriel2(modulo, k);
    auto fnk = factoriel2(modulo, n - k);
    if (fn.first - fk.first - fnk.first > 0)
        return nombre_modulaire(modulo, 0);
    return fn.second / (fk.second * fnk.second);
}
