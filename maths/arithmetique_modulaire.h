#pragma once

#include <ostream>
#include <utility>

#include "arithmetique.h"
#include "puissance.h"
#include "utilitaires.h"

namespace arithmetique_modulaire {

    template<typename Nombre, typename Conteneur>
    Nombre inverse_modulaire(Nombre a, Nombre n, const Conteneur &premiers) {
        // https://fr.wikipedia.org/wiki/Inverse_modulaire
        // si PGCD(a, n) = 1
        // alors a**phi(n) mod n = 1
        //       a**-1 = a**(phi(n) - 1) mod n
        Nombre _phi = arithmetique::phi<Nombre>(n, premiers);
        return puissance::puissance_modulaire<Nombre>(a, _phi - 1, n);
    }

    template<typename Nombre>
    Nombre inverse_modulaire(Nombre a, Nombre n) {
        Nombre inverse, ignore;
        arithmetique::Bezout(a, n, inverse, ignore);

        if (inverse < 0)
            return inverse + n;
        else
            return inverse;
    }

    template<typename Nombre, typename Conteneur1, typename Conteneur2, typename Conteneur3>
    Nombre restes_chinois(const Conteneur1 &modulos, const Conteneur2 &restes, const Conteneur3 &premiers) {
        // https://fr.wikipedia.org/wiki/Th%C3%A9or%C3%A8me_des_restes_chinois
        if (modulos.size() != restes.size())
            return 0;

        Nombre n = 1;
        for (const auto &p: modulos) n *= p;

        Nombre resultat = 0;

        std::for_each2(modulos.begin(), modulos.end(), restes.begin(),
                       [&resultat, &premiers, &n](const Nombre &modulo, const Nombre &reste) {
                           Nombre r = n / modulo;
                           resultat += r * inverse_modulaire(r, modulo, premiers) * reste;
                           resultat %= n;
                       }
        );
        return resultat;
    }

    template<typename Nombre, typename Conteneur1, typename Conteneur2>
    Nombre restes_chinois(const Conteneur1 &modulos, const Conteneur2 &restes) {
        // https://fr.wikipedia.org/wiki/Th%C3%A9or%C3%A8me_des_restes_chinois
        if (modulos.size() != restes.size())
            return 0;

        Nombre n = 1;
        for (const auto &p: modulos) n *= p;

        Nombre resultat = 0;

        std::for_each2(modulos.begin(), modulos.end(), restes.begin(),
                       [&resultat, &n](const Nombre &modulo, const Nombre &reste) {
                           Nombre r = n / modulo;
                           resultat += r * inverse_modulaire(r, modulo) * reste;
                           resultat %= n;
                       }
        );
        return resultat;
    }

    template<size_t modulo>
    class nombre_modulaire {
        template<typename Type>
        void set(Type op, std::false_type /*is_signed*/) {
            _value = op % modulo;
        }

        template<typename Type>
        void set(Type op, std::true_type /*is_signed*/) {
            bool negatif = (op < 0);
            op = std::abs(op);
            _value = static_cast<size_t>(op) % modulo;
            if (negatif) {
                _value = modulo - _value;
            }
        }

        static std::pair<size_t, nombre_modulaire<modulo>> factoriel2(size_t n) {
            nombre_modulaire<modulo> resultat(1);
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

        size_t _value;
    public:
        template<typename Type>
        explicit nombre_modulaire(Type n) : _value(0) {
            set(n);
        }

        nombre_modulaire() : _value(0) {
        }

        template<typename T>
        void set(T x) {
            static_assert(std::is_integral<T>::value, "Integer required.");
            set(x, std::is_signed<T>());
        }

        static nombre_modulaire<modulo> puissance(nombre_modulaire<modulo> a, size_t n) {
            nombre_modulaire<modulo> result(1);
            while (n > 0) {
                if (n % 2)
                    result *= a;
                a *= a;
                n /= 2;
            }
            return result;
        }

        [[nodiscard]] size_t value() const { return _value; }

        nombre_modulaire<modulo> operator-() const {
            return nombre_modulaire<modulo>(modulo - value());
        }

        nombre_modulaire<modulo> &operator+=(const nombre_modulaire<modulo> &b) {
            _value += b._value;
            if (_value >= modulo) _value -= modulo;
            return *this;
        }

        nombre_modulaire<modulo> operator+(const nombre_modulaire<modulo> &op) const {
            nombre_modulaire<modulo> result(*this);
            result.operator+=(op);
            return result;
        }

        template<typename T>
        nombre_modulaire<modulo> &operator+=(const T &op) {
            nombre_modulaire<modulo> n(op);
            return this->operator+=(n);
        }

        template<typename T>
        nombre_modulaire<modulo> operator+(const T &op) const {
            nombre_modulaire<modulo> n(op);
            return this->operator+(n);
        }

        nombre_modulaire<modulo> &operator-=(const nombre_modulaire<modulo> &b) {
            _value = _value < b._value ? modulo + _value - b._value : _value - b._value;
            return *this;
        }

        nombre_modulaire<modulo> operator-(const nombre_modulaire<modulo> &op) const {
            nombre_modulaire<modulo> result(*this);
            result.operator-=(op);
            return result;
        }


        template<typename T>
        nombre_modulaire<modulo> &operator-=(const T &op) {
            nombre_modulaire<modulo> n(op);
            return this->operator-=(n);
        }

        template<typename T>
        nombre_modulaire<modulo> operator-(const T &op) const {
            nombre_modulaire<modulo> n(op);
            return this->operator-(n);
        }

        nombre_modulaire<modulo> &operator*=(const nombre_modulaire<modulo> &b) {
            size_t c = _value;
            c *= b._value;
            _value = c % modulo;
            return *this;
        }

        nombre_modulaire<modulo> operator*(const nombre_modulaire<modulo> &op) const {
            nombre_modulaire<modulo> result(*this);
            result.operator*=(op);
            return result;
        }

        template<typename T>
        nombre_modulaire<modulo> &operator*=(const T &op) {
            nombre_modulaire<modulo> n(op);
            return this->operator*=(n);
        }

        template<typename T>
        nombre_modulaire<modulo> operator*(const T &op) const {
            nombre_modulaire<modulo> n(op);
            return this->operator*(n);
        }

        nombre_modulaire<modulo> &operator/=(const nombre_modulaire<modulo> &b) {
            return operator*=(puissance(b, modulo - 2));
        }

        nombre_modulaire<modulo> operator/(const nombre_modulaire<modulo> &op) const {
            nombre_modulaire<modulo> result(*this);
            result.operator/=(op);
            return result;
        }

        template<typename T>
        nombre_modulaire<modulo> &operator/=(const T &op) {
            nombre_modulaire<modulo> n(op);
            return this->operator/=(n);
        }

        template<typename T>
        nombre_modulaire<modulo> operator/(const T &op) const {
            nombre_modulaire<modulo> n(op);
            return this->operator/(n);
        }

        static nombre_modulaire<modulo> factoriel(size_t n) {
            return factoriel2(n).second;
        }

        static nombre_modulaire<modulo> arrangement(size_t n, size_t k) {
            auto fn = factoriel2(n);
            auto fnk = factoriel2(n - k);
            if (fn.first - fnk.first > 0)
                return nombre_modulaire<modulo>(0);
            return fn.second / fnk.second;
        }

        static nombre_modulaire<modulo> coefficient_binomial(size_t n, size_t k) {
            auto fn = factoriel2(n);
            auto fk = factoriel2(k);
            auto fnk = factoriel2(n - k);
            if (fn.first - fk.first - fnk.first > 0)
                return nombre_modulaire<modulo>(0);
            return fn.second / (fk.second * fnk.second);
        }
    };

    template<size_t modulo, typename T>
    inline nombre_modulaire<modulo> operator+(const T &op1, const nombre_modulaire<modulo> &op2) {
        return op2.operator+(op1);
    }

    template<size_t modulo, typename T>
    inline nombre_modulaire<modulo> operator-(const T &op1, const nombre_modulaire<modulo> &op2) {
        nombre_modulaire<modulo> n(op1);
        return n.operator-(op2);
    }

    template<size_t modulo, typename T>
    inline nombre_modulaire<modulo> operator*(const T &op1, const nombre_modulaire<modulo> &op2) {
        return op2.operator*(op1);
    }

    template<size_t modulo, typename T>
    inline nombre_modulaire<modulo> operator/(const T &op1, const nombre_modulaire<modulo> &op2) {
        nombre_modulaire<modulo> n(op1);
        return n.operator/(op2);
    }
}

template<size_t modulo>
std::ostream &operator<<(std::ostream &os, const arithmetique_modulaire::nombre_modulaire<modulo> &a) {
    os << a.value() << "[" << modulo<< "]";
    return os;
}
