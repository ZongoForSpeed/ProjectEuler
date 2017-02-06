#pragma once

#include <iostream>
#include <gmp.h>

#include <boost/optional.hpp>
#include <limits>
#include <deque>

class mp_nombre {
    mpz_t data;

public:
    // region Constructors
    mp_nombre();
    virtual ~mp_nombre();

    mp_nombre(const mpz_t &op);
    mp_nombre(const mp_nombre &op);
    mp_nombre(unsigned int op);
    mp_nombre(signed int op);
    mp_nombre(unsigned long op);
    mp_nombre(signed long op);
    mp_nombre(double op);
    mp_nombre(const std::string &op, int base = 10);
    mp_nombre(unsigned long long op);
    mp_nombre(signed long long op);
    // endregion Constructors

    // region Setters
    void set(const mpz_t &op);
    void set(const mp_nombre &op);
    void set(unsigned long int op);
    void set(signed long int op);
    void set(double op);
    void set(const std::string &op, int base = 10);

    template<typename T> void set(T x);
    // endregion Setters

    // region Getters
    unsigned long get_unsigned_long() const;
    signed long get_signed_long() const;
    double get_double() const;
    unsigned long long get_unsigned_long_long() const;

    template<typename T>
    T get() const;
    
    const mpz_t & get_data() const {
        return data;
    }
    // endregion Getters

    void swap(mp_nombre &op);

    const std::string to_string(int base = 10) const;

    mp_nombre &negation();

    mp_nombre operator-() const;
    mp_nombre operator~() const;
    mp_nombre &operator++();
    mp_nombre &operator--();
    mp_nombre operator++(int);
    mp_nombre operator--(int);

    signed short signe() const;

    mp_nombre &operator=(const mp_nombre &op);

    template<typename T>
    mp_nombre &operator=(const T &op);

    // region Comparaison
    int compare(const mp_nombre &op) const;
    int compare(double op) const;
    int compare(signed long int op) const;
    int compare(unsigned long int op) const;

    template<typename T>
    int compare(const T &op) const;

    template<typename T>
    bool operator==(const T &b) const { return compare(b) == 0; }

    template<typename T>
    bool operator!=(const T &b) const { return compare(b) != 0; }

    template<typename T>
    bool operator<(const T &b) const { return compare(b) < 0; }

    template<typename T>
    bool operator>(const T &b) const { return compare(b) > 0; }

    template<typename T>
    bool operator<=(const T &b) const { return compare(b) < 1; }

    template<typename T>
    bool operator>=(const T &b) const { return compare(b) > -1; }
    // endregion Comparaison

    static mp_nombre abs(const mp_nombre &op);

    static mp_nombre racine_carre(const mp_nombre &op);

    static bool carre_parfait(const mp_nombre &op);

    static mp_nombre racine(const mp_nombre &op, unsigned long int n);

    // region Puissance
    static mp_nombre puissance(const mp_nombre &base, unsigned long exposant);

    static mp_nombre puissance(unsigned long base, unsigned long exposant);

    static mp_nombre puissance_modulaire(const mp_nombre &base, unsigned long exposant, const mp_nombre &modulo);

    template<typename T>
    static mp_nombre puissance_modulaire(const mp_nombre &base, unsigned long exposant, const T &modulo);
    // endregion Puissance

    // region Arithmetiques
    static bool premier(const mp_nombre &op, int probabilite = 25);

    static mp_nombre premier_suivant(const mp_nombre &op);

    static mp_nombre PGCD(const mp_nombre &op1, const mp_nombre &op2);
    static mp_nombre PGCD(const mp_nombre &op1, unsigned long int op2);

    template<typename T>
    static mp_nombre PGCD(const mp_nombre &op1, const T &op2);

    template<typename T>
    static mp_nombre PGCD(const T &op1, const mp_nombre &op2);

    static mp_nombre PPCM(const mp_nombre &op1, const mp_nombre &op2);
    static mp_nombre PPCM(const mp_nombre &op1, unsigned long int op2);

    template<typename T>
    static mp_nombre PPCM(const mp_nombre &op1, const T &op2);

    template<typename T>
    static mp_nombre PPCM(const T &op1, const mp_nombre &op2);

    static boost::optional<mp_nombre> inverse_modulaire(const mp_nombre &op, const mp_nombre &modulo);

    static mp_nombre coefficient_binomial(const mp_nombre &n, unsigned long int k);

    static mp_nombre coefficient_binomial(unsigned long int n, unsigned long int k);

    static mp_nombre factorielle(unsigned long int n);

    static mp_nombre catalan(unsigned long int n);
    // endregion Arithmetiques

    // region Addition
    mp_nombre &operator+=(const mp_nombre &op);
    mp_nombre &operator+=(unsigned long int op);
    mp_nombre operator+(const mp_nombre &op) const;
    mp_nombre operator+(unsigned long int op) const;

    template<typename T>
    mp_nombre &operator+=(const T &op);

    template<typename T>
    mp_nombre operator+(const T &op) const;
    // endregion Addition

    // region Soustraction
    mp_nombre &operator-=(const mp_nombre &op);
    mp_nombre &operator-=(unsigned long int op);
    mp_nombre operator-(const mp_nombre &op) const;
    mp_nombre operator-(unsigned long int op) const;

    template<typename T>
    mp_nombre &operator-=(const T &op);

    template<typename T>
    mp_nombre operator-(const T &op) const;
    // endregion Soustraction

    // region Multiplication
    mp_nombre &operator*=(const mp_nombre &op);
    mp_nombre &operator*=(long int op);
    mp_nombre &operator*=(unsigned long int op);
    mp_nombre operator*(const mp_nombre &op) const;
    mp_nombre operator*(long int op) const;
    mp_nombre operator*(unsigned long int op) const;

    template<typename T>
    mp_nombre &operator*=(const T &op);

    template<typename T>
    mp_nombre operator*(const T &op) const;
    // endregion Multiplication

    // region Division
    mp_nombre &operator/=(const mp_nombre &op);
    mp_nombre &operator/=(unsigned long int op);
    mp_nombre operator/(const mp_nombre &op) const;
    mp_nombre operator/(unsigned long int op) const;

    template<typename T>
    mp_nombre &operator/=(const T &op);

    template<typename T>
    mp_nombre operator/(const T &op) const;

    static bool divisible(const mp_nombre & op1, const mp_nombre & op2);
    static bool divisible(const mp_nombre & op1, unsigned long int op2);
    // endregion Division

    // region Modulo
    mp_nombre &operator%=(const mp_nombre &op);
    mp_nombre &operator%=(unsigned long int op);
    mp_nombre operator%(const mp_nombre &op) const;
    unsigned long int operator%(unsigned long int op) const;

    template<typename T>
    mp_nombre &operator%=(const T &op);

    template<typename T>
    mp_nombre operator%(const T &op) const;
    // endregion Modulo

    // region AND
    mp_nombre &operator&=(const mp_nombre &op);

    mp_nombre operator&(const mp_nombre &op) const;

    template<typename T>
    mp_nombre &operator&=(const T &op);

    template<typename T>
    mp_nombre operator&(const T &op) const;
    // endregion AND

    // region OR
    mp_nombre &operator|=(const mp_nombre &op);

    mp_nombre operator|(const mp_nombre &op) const;

    template<typename T>
    mp_nombre &operator|=(const T &op);

    template<typename T>
    mp_nombre operator|(const T &op) const;
    // endregion OR

    // region XOR
    mp_nombre &operator^=(const mp_nombre &op);

    mp_nombre operator^(const mp_nombre &op) const;

    template<typename T>
    mp_nombre &operator^=(const T &op);

    template<typename T>
    mp_nombre operator^(const T &op) const;
    // endregion XOR

    mp_nombre operator<<(const unsigned long &b) const;

    mp_nombre operator>>(const unsigned long &b) const;

    // region Chiffres
    void boucle_chiffre(std::function<void(unsigned long int)> op, unsigned long int base = 10) const {
        mp_nombre n(data);
        while (n != 0) {
            unsigned long int r = mpz_fdiv_q_ui(n.data, n.data, base);
            op(r);
        }
    }

    size_t nombre_chiffres(unsigned long int base = 10) const {
        size_t d = 0;
        boucle_chiffre([&d](unsigned long int) { ++d; }, base);
        return d;
    }

    mp_nombre somme_chiffres(unsigned long int base = 10) const {
        mp_nombre resultat = 0;
        boucle_chiffre([&resultat](unsigned long int d) { resultat += d; }, base);
        return resultat;
    }

    std::deque<unsigned long int> extraire_chiffres(unsigned long int base = 10) const {
        std::deque<unsigned long int> resultat;
        boucle_chiffre([&resultat](unsigned long int d) { resultat.push_front(d); }, base);
        return resultat;
    }

    mp_nombre inverser_nombre(unsigned long int base = 10) const {
        mp_nombre resultat = 0;
        boucle_chiffre([&resultat, &base](unsigned long int d) {
            resultat *= base;
            resultat += d;
        }, base);
        return resultat;
    }

    bool palindrome(unsigned long int base = 10) const {
        const auto chiffres = extraire_chiffres(base);
        return std::equal(chiffres.begin(), chiffres.begin() + chiffres.size() / 2, chiffres.rbegin());
    }
    // endregion Chiffres

private:
    template<typename Type>
    void set(Type op, std::false_type /*is_signed*/) {
        mpz_import(data, 1, -1, sizeof op, 0, 0, &op);
    }

    template<typename Type>
    void set(Type op, std::true_type /*is_signed*/) {
        bool negatif = (op < 0);
        op = std::abs(op);
        mpz_import(data, 1, -1, sizeof op, 0, 0, &op);
        if (negatif) negation();
    }

    template<typename Type>
    Type get(Type /*type*/, std::false_type /*is_signed*/) const {
        Type result = 0;
        mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
        return result;
    }

    template<typename Type>
    Type get(Type /*type*/, std::true_type /*is_signed*/) const {
        Type result = 0;
        mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
        return signe() * result;
    }
};

template<typename T>
inline mp_nombre operator+(const T &op1, const mp_nombre &op2) {
    return op2.operator+(op1);
}

template<typename T>
inline mp_nombre operator-(const T &op1, const mp_nombre &op2) {
    mp_nombre n(op1);
    return n.operator-(op2);
}

template<typename T>
inline mp_nombre operator*(const T &op1, const mp_nombre &op2) {
    return op2.operator*(op1);
}

template<typename T>
inline mp_nombre operator/(const T &op1, const mp_nombre &op2) {
    mp_nombre n(op1);
    return n.operator/(op2);
}

template<typename T>
inline mp_nombre operator%(const T &op1, const mp_nombre &op2) {
    mp_nombre n(op1);
    return n.operator%(op2);
}

template<typename T>
inline mp_nombre operator&(const T &op1, const mp_nombre &op2) {
    return op2.operator&(op1);
}

template<typename T>
inline mp_nombre operator|(const T &op1, const mp_nombre &op2) {
    return op2.operator|(op1);
}

template<typename T>
inline mp_nombre operator^(const T &op1, const mp_nombre &op2) {
    return op2.operator^(op1);
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator==(const T &a, const mp_nombre &b) {
    return b.compare(a) == 0;
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator!=(const T &a, const mp_nombre &b) {
    return b.compare(a) != 0;
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator<(const T &a, const mp_nombre &b) {
    return b.compare(a) > 0;
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator>(const T &a, const mp_nombre &b) {
    return b.compare(a) < 0;
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator<=(const T &a, const mp_nombre &b) {
    return b.compare(a) > -1;
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>::type>
inline bool operator>=(const T &a, const mp_nombre &b) {
    return b.compare(a) < 1;
}

#include "mp_nombre.inl"

namespace std {
    mp_nombre abs(const mp_nombre &op);

    void swap(mp_nombre &op1, mp_nombre &op2);

    mp_nombre sqrt(const mp_nombre &op);

    mp_nombre cbrt(const mp_nombre &op);

    std::ostream &operator<<(std::ostream &os, const mp_nombre &op);

    std::istream &operator>>(std::istream &is, mp_nombre &op);

    template<>
    class numeric_limits<mp_nombre> : public numeric_limits<long long> {
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
    
    inline string to_string(const mp_nombre & op) {
        return op.to_string();
    }
}
