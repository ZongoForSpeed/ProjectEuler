#pragma once

#include <deque>
#include <iostream>
#include <limits>
#include <type_traits>
#include <optional>
#include <functional>

#include <gmp.h>

class mpz_nombre {
    mpz_t _data;

public:
    // region Constructors
    mpz_nombre();

    virtual ~mpz_nombre();

    mpz_nombre(const mpz_t &op);

    mpz_nombre(const mpz_nombre &op);

    mpz_nombre(unsigned int op);

    mpz_nombre(signed int op);

    mpz_nombre(unsigned long op);

    mpz_nombre(signed long op);

    mpz_nombre(double op);

    mpz_nombre(const std::string &op, int base = 10);

    mpz_nombre(unsigned long long op);

    mpz_nombre(signed long long op);
    // endregion Constructors

    // region Setters
    void set(const mpz_t &op);

    void set(const mpz_nombre &op);

    void set(unsigned long int op);

    void set(signed long int op);

    void set(double op);

    void set(const std::string &op, int base = 10);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    void set(T x) {
        static_assert(std::is_integral<T>::value, "Integer required.");
        set(x, std::is_signed<T>());
    }
    // endregion Setters

    // region Getters
    unsigned long get_unsigned_long() const;

    signed long get_signed_long() const;

    double get_double() const;

    unsigned long long get_unsigned_long_long() const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    T get() const {
        static_assert(std::is_integral<T>::value, "Integer required.");
        return get(T(0), std::is_signed<T>());
    }

    mpz_t &get_data() {
        return _data;
    }

    const mpz_t &get_data() const {
        return _data;
    }
    // endregion Getters

    void swap(mpz_nombre &op);

    std::string to_string(int base = 10) const;

    mpz_nombre &negation();

    mpz_nombre operator-() const;

    mpz_nombre operator~() const;

    mpz_nombre &operator++();

    mpz_nombre &operator--();

    const mpz_nombre operator++(int);

    mpz_nombre operator--(int);

    [[nodiscard]] signed short signe() const;

    mpz_nombre &operator=(const mpz_nombre &op);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpz_nombre &operator=(const T &op) {
        set(op);
        return *this;
    }

    // region Comparaison
    [[nodiscard]] int compare(const mpz_nombre &op) const;

    [[nodiscard]] int compare(double op) const;

    [[nodiscard]] int compare(signed long int op) const;

    [[nodiscard]] int compare(unsigned long int op) const;

    template<typename T>
    [[nodiscard]] int compare(const T &op) const {
        mpz_nombre n(op);
        return compare(n);
    }

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

    static mpz_nombre abs(const mpz_nombre &op);

    static mpz_nombre racine_carre(const mpz_nombre &op);

    static bool carre_parfait(const mpz_nombre &op);

    static mpz_nombre racine(const mpz_nombre &op, unsigned long int n);

    static bool racine_parfaite(const mpz_nombre &op, unsigned long int n);

    // region Puissance
    static mpz_nombre puissance(const mpz_nombre &base, unsigned long exposant);

    static mpz_nombre puissance(unsigned long base, unsigned long exposant);

    static mpz_nombre puissance_modulaire(const mpz_nombre &base, unsigned long exposant, const mpz_nombre &modulo);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    static mpz_nombre puissance_modulaire(const mpz_nombre &base, unsigned long exposant, const T &modulo) {
        mpz_nombre tmp_modulo(modulo);
        return puissance_modulaire(base, exposant, tmp_modulo);
    }
    // endregion Puissance

    // region Arithmetiques
    [[nodiscard]] bool premier(int probabilite = 25) const;

    static bool premier(const mpz_nombre &op, int probabilite = 25);

    static mpz_nombre premier_suivant(const mpz_nombre &op);

    mpz_nombre &premier_suivant();

    static mpz_nombre PGCD(const mpz_nombre &op1, const mpz_nombre &op2);

    static mpz_nombre PGCD(const mpz_nombre &op1, unsigned long int op2);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpz_nombre PGCD(const mpz_nombre &op1, const T &op2) {
        mpz_nombre n2(op2);
        return PGCD(op1, n2);
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpz_nombre PGCD(const T &op1, const mpz_nombre &op2) {
        return PGCD(op2, op1);
    }

    static mpz_nombre PPCM(const mpz_nombre &op1, const mpz_nombre &op2);

    static mpz_nombre PPCM(const mpz_nombre &op1, unsigned long int op2);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpz_nombre PPCM(const mpz_nombre &op1, const T &op2) {
        mpz_nombre n2(op2);
        return PPCM(op1, n2);
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpz_nombre PPCM(const T &op1, const mpz_nombre &op2) {
        return PPCM(op2, op1);
    }

    static std::optional<mpz_nombre> inverse_modulaire(const mpz_nombre &op, const mpz_nombre &modulo);

    static mpz_nombre coefficient_binomial(const mpz_nombre &n, unsigned long int k);

    static mpz_nombre coefficient_binomial(unsigned long int n, unsigned long int k);

    static mpz_nombre factorielle(unsigned long int n);

    static mpz_nombre catalan(unsigned long int n);
    // endregion Arithmetiques

    // region Addition
    mpz_nombre &operator+=(const mpz_nombre &op);

    mpz_nombre &operator+=(unsigned long int op);

    mpz_nombre operator+(const mpz_nombre &op) const;

    mpz_nombre operator+(unsigned long int op) const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpz_nombre &operator+=(const T &op) {
        mpz_nombre n(op);
        return this->operator+=(n);
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpz_nombre operator+(const T &op) const {
        mpz_nombre resultat;
        mpz_nombre n(op);
        mpz_add(resultat._data, _data, n._data);
        return resultat;
    }
    // endregion Addition

    // region Soustraction
    mpz_nombre &operator-=(const mpz_nombre &op);

    mpz_nombre &operator-=(unsigned long int op);

    mpz_nombre operator-(const mpz_nombre &op) const;

    mpz_nombre operator-(unsigned long int op) const;

    template<typename T>
    mpz_nombre &operator-=(const T &op) {
        mpz_nombre n(op);
        return this->operator-=(n);
    }

    template<typename T>
    mpz_nombre operator-(const T &op) const {
        mpz_nombre n(op);
        return this->operator-(n);
    }
    // endregion Soustraction

    // region Multiplication
    mpz_nombre &operator*=(const mpz_nombre &op);

    mpz_nombre &operator*=(long int op);

    mpz_nombre &operator*=(unsigned long int op);

    mpz_nombre operator*(const mpz_nombre &op) const;

    mpz_nombre operator*(long int op) const;

    mpz_nombre operator*(unsigned long int op) const;

    template<typename T>
    mpz_nombre &operator*=(const T &op) {
        mpz_nombre n(op);
        return this->operator*=(n);
    }

    template<typename T>
    mpz_nombre operator*(const T &op) const {
        mpz_nombre n(op);
        return this->operator*(n);
    }
    // endregion Multiplication

    // region Division
    mpz_nombre &operator/=(const mpz_nombre &op);

    mpz_nombre &operator/=(unsigned long int op);

    mpz_nombre operator/(const mpz_nombre &op) const;

    mpz_nombre operator/(unsigned long int op) const;

    template<typename T>
    mpz_nombre &operator/=(const T &op) {
        mpz_nombre n(op);
        return this->operator/=(n);
    }

    template<typename T>
    mpz_nombre operator/(const T &op) const {
        mpz_nombre n(op);
        return this->operator/(n);
    }

    static bool divisible(const mpz_nombre &op1, const mpz_nombre &op2);

    static bool divisible(const mpz_nombre &op1, unsigned long int op2);
    // endregion Division

    // region Modulo
    mpz_nombre &operator%=(const mpz_nombre &op);

    mpz_nombre &operator%=(unsigned long int op);

    mpz_nombre operator%(const mpz_nombre &op) const;

    unsigned long int operator%(unsigned long int op) const;

    template<typename T>
    mpz_nombre &operator%=(const T &op) {
        mpz_nombre n(op);
        return this->operator%=(n);
    }

    template<typename T>
    mpz_nombre operator%(const T &op) const {
        mpz_nombre n(op);
        return this->operator%(n);
    }
    // endregion Modulo

    // region AND
    mpz_nombre &operator&=(const mpz_nombre &op);

    mpz_nombre operator&(const mpz_nombre &op) const;

    template<typename T>
    mpz_nombre &operator&=(const T &op) {
        mpz_nombre n(op);
        return this->operator&=(n);
    }

    template<typename T>
    mpz_nombre operator&(const T &op) const {
        mpz_nombre n(op);
        return this->operator&(n);
    }
    // endregion AND

    // region OR
    mpz_nombre &operator|=(const mpz_nombre &op);

    mpz_nombre operator|(const mpz_nombre &op) const;

    template<typename T>
    mpz_nombre &operator|=(const T &op) {
        mpz_nombre n(op);
        return this->operator|=(n);
    }

    template<typename T>
    mpz_nombre operator|(const T &op) const {
        mpz_nombre n(op);
        return this->operator|(n);
    }
    // endregion OR

    // region XOR
    mpz_nombre &operator^=(const mpz_nombre &op);

    mpz_nombre operator^(const mpz_nombre &op) const;

    template<typename T>
    mpz_nombre &operator^=(const T &op) {
        mpz_nombre n(op);
        return this->operator^=(n);
    }

    template<typename T>
    mpz_nombre operator^(const T &op) const {
        mpz_nombre n(op);
        return this->operator^(n);
    }
    // endregion XOR

    mpz_nombre operator<<(const unsigned long &b) const;

    mpz_nombre operator>>(const unsigned long &b) const;

    // region Chiffres
    void boucle_chiffre(const std::function<void(unsigned long int)> &op, unsigned long int base = 10) const {
        mpz_nombre n(_data);
        while (n != 0) {
            unsigned long int r = mpz_fdiv_q_ui(n._data, n._data, base);
            op(r);
        }
    }

    [[nodiscard]] size_t nombre_chiffres(unsigned long int base = 10) const {
        size_t d = 0;
        boucle_chiffre([&d](unsigned long int) { ++d; }, base);
        return d;
    }

    [[nodiscard]] mpz_nombre somme_chiffres(unsigned long int base = 10) const {
        mpz_nombre resultat = 0;
        boucle_chiffre([&resultat](unsigned long int d) { resultat += d; }, base);
        return resultat;
    }

    [[nodiscard]] std::deque<unsigned long int> extraire_chiffres(unsigned long int base = 10) const {
        std::deque<unsigned long int> resultat;
        boucle_chiffre([&resultat](unsigned long int d) { resultat.push_front(d); }, base);
        return resultat;
    }

    [[nodiscard]] mpz_nombre inverser_nombre(unsigned long int base = 10) const {
        mpz_nombre resultat = 0;
        boucle_chiffre([&resultat, &base](unsigned long int d) {
            resultat *= base;
            resultat += d;
        }, base);
        return resultat;
    }

    [[nodiscard]] bool palindrome(unsigned long int base = 10) const {
        const auto chiffres = extraire_chiffres(base);
        return std::equal(chiffres.begin(), chiffres.begin() + chiffres.size() / 2, chiffres.rbegin());
    }
    // endregion Chiffres

private:

#ifdef WIN32
    template<typename Type>
    void set(Type op, std::false_type /*is_signed*/) {
        set(std::to_string(op));
   }

    template<typename Type>
    void set(Type op, std::true_type /*is_signed*/) {
        set(std::to_string(op));
    }
#else

    template<typename Type>
    void set(Type op, std::true_type /*is_signed*/) {
        bool negatif = (op < 0);
        op = std::abs(op);
        mpz_import(_data, 1, -1, sizeof op, 0, 0, &op);
        if (negatif) negation();
    }

    template<typename Type>
    void set(Type op, std::false_type /*is_signed*/) {
        mpz_import(_data, 1, -1, sizeof op, 0, 0, &op);
    }

#endif

    template<typename Type>
    Type get(Type /*type*/, std::false_type /*is_signed*/) const {
        Type result = 0;
        mpz_export(&result, nullptr, -1, sizeof result, 0, 0, _data);
        return result;
    }

    template<typename Type>
    Type get(Type /*type*/, std::true_type /*is_signed*/) const {
        Type result = 0;
        mpz_export(&result, nullptr, -1, sizeof result, 0, 0, _data);
        return signe() * result;
    }
};

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator+(const T &op1, const mpz_nombre &op2) {
    return op2.operator+(op1);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator-(const T &op1, const mpz_nombre &op2) {
    mpz_nombre n(op1);
    return n.operator-(op2);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator*(const T &op1, const mpz_nombre &op2) {
    return op2.operator*(op1);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator/(const T &op1, const mpz_nombre &op2) {
    mpz_nombre n(op1);
    return n.operator/(op2);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator%(const T &op1, const mpz_nombre &op2) {
    mpz_nombre n(op1);
    return n.operator%(op2);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator&(const T &op1, const mpz_nombre &op2) {
    return op2.operator&(op1);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator|(const T &op1, const mpz_nombre &op2) {
    return op2.operator|(op1);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator^(const T &op1, const mpz_nombre &op2) {
    return op2.operator^(op1);
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator==(const T &a, const mpz_nombre &b) {
    return b.compare(a) == 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator!=(const T &a, const mpz_nombre &b) {
    return b.compare(a) != 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator<(const T &a, const mpz_nombre &b) {
    return b.compare(a) > 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator>(const T &a, const mpz_nombre &b) {
    return b.compare(a) < 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator<=(const T &a, const mpz_nombre &b) {
    return b.compare(a) > -1;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline bool operator>=(const T &a, const mpz_nombre &b) {
    return b.compare(a) < 1;
}

namespace std {
    mpz_nombre abs(const mpz_nombre &op);

    void swap(mpz_nombre &op1, mpz_nombre &op2);

    mpz_nombre sqrt(const mpz_nombre &op);

    mpz_nombre cbrt(const mpz_nombre &op);

    std::ostream &operator<<(std::ostream &os, const mpz_nombre &op);

    std::istream &operator>>(std::istream &is, mpz_nombre &op);

    template<>
    class numeric_limits<mpz_nombre> : public numeric_limits<long long> {
    public:
        static constexpr int digits = INT_MAX;
        static constexpr int digits10 = INT_MAX;

        static mpz_nombre max() {
            return mpz_nombre::puissance(2, digits);
        }

        static mpz_nombre min() {
            return max().negation();
        }

        static mpz_nombre lowest() {
            return min();
        }
    };

    inline string to_string(const mpz_nombre &op) {
        return op.to_string();
    }
}
