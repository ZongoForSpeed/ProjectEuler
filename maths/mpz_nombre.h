#pragma once

#include <deque>
#include <iostream>
#include <limits>
#include <type_traits>
#include <optional>
#include <functional>

#include <gmp.h>

class mpz_nombre {
    mpz_ptr _data;

    void init();

    void clear();

public:
    // region Constructors
    mpz_nombre();

    ~mpz_nombre();

    mpz_nombre(mpz_srcptr op);

    mpz_nombre(const mpz_nombre &op);

    mpz_nombre(mpz_nombre &&op);

    mpz_nombre(unsigned int op);

    mpz_nombre(signed int op);

    mpz_nombre(unsigned long op);

    mpz_nombre(signed long op);

    mpz_nombre(double op);

    mpz_nombre(const std::string &op, int base = 10);

    mpz_nombre(unsigned long long op);

    mpz_nombre(signed long long op);

    template<typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    mpz_nombre(T x) {
        init();
        set(x);
    }

    mpz_nombre &operator=(const mpz_nombre &op);

    mpz_nombre &operator=(mpz_nombre &&op) noexcept;
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

    mpz_ptr get_data() {
        return _data;
    }

    mpz_srcptr get_data() const {
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

    [[deprecated]]
    const mpz_nombre operator++(int);

    [[deprecated]]
    const mpz_nombre operator--(int);

    [[nodiscard]] signed short signe() const;

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    mpz_nombre &operator=(const T &op) {
        set(op);
        return *this;
    }

    // region Comparaison
    template<typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
    [[nodiscard]] int compare(const T &op) const {
        return compare(op, std::is_signed<T>());
    }

    template<typename Type>
    int compare(Type op, std::false_type /*is_signed*/) const {
        return mpz_cmp_ui(_data, op);
    }

    template<typename Type>
    int compare(Type op, std::true_type /*is_signed*/) const {
        return mpz_cmp_si(_data, op);
    }

    [[nodiscard]] int compare(const mpz_nombre &op) const;

    [[nodiscard]] int compare(double op) const;

    [[nodiscard]] int compare(signed long int op) const;

    [[nodiscard]] int compare(unsigned long int op) const;


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

    static void abs(mpz_nombre &rop, const mpz_nombre &op);

    static void racine_carre(mpz_nombre &rop, const mpz_nombre &op);

    static bool carre_parfait(const mpz_nombre &op);

    static void racine(mpz_nombre &rop, const mpz_nombre &op, unsigned long int n);

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

    static void premier_suivant(mpz_nombre &rop, const mpz_nombre &op);

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
    static void addition(mpz_nombre &rop, const mpz_nombre &op1, const mpz_nombre &op2) {
        mpz_add(rop._data, op1._data, op2._data);
    }

    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    static void addition(mpz_nombre &rop, const mpz_nombre &op1, Type op2) {
        addition(rop, op1, op2, std::is_signed<Type>());
    }

    template<typename Type>
    static void addition(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::false_type /*is_signed*/) {
        mpz_add_ui(rop._data, op1._data, op2);
    }

    template<typename Type>
    static void addition(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::true_type /*is_signed*/) {
        typedef typename std::make_unsigned<Type>::type unsigned_type;
        bool negatif = op2 < 0;
        auto unsignedOp2 = static_cast<unsigned_type>(negatif ? -op2 : op2);
        if (negatif) {
            mpz_sub_ui(rop._data, op1._data, unsignedOp2);
        } else {
            mpz_add_ui(rop._data, op1._data, unsignedOp2);
        }
    }

    template<typename T>
    mpz_nombre &operator+=(const T &op) {
        addition(*this, *this, op);
        return *this;
    }

    template<typename T>
    mpz_nombre operator+(const T &op) const {
        mpz_nombre rop;
        addition(rop, *this, op);
        return rop;
    }
    // endregion Addition

    // region Soustraction
    static void soustraction(mpz_nombre &rop, const mpz_nombre &op1, const mpz_nombre &op2) {
        mpz_sub(rop._data, op1._data, op2._data);
    }

    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    static void soustraction(mpz_nombre &rop, const mpz_nombre &op1, Type op2) {
        soustraction(rop, op1, op2, std::is_signed<Type>());
    }

    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    static void soustraction(mpz_nombre &rop, Type op1, const mpz_nombre &op2) {
        soustraction(rop, op1, op2, std::is_signed<Type>());
    }

    template<typename Type>
    static void soustraction(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::false_type /*is_signed*/) {
        mpz_sub_ui(rop._data, op1._data, op2);
    }

    template<typename Type>
    static void soustraction(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::true_type /*is_signed*/) {
        typedef typename std::make_unsigned<Type>::type unsigned_type;
        bool negatif = op2 < 0;
        auto unsignedOp2 = static_cast<unsigned_type>(negatif ? -op2 : op2);
        if (negatif) {
            mpz_add_ui(rop._data, op1._data, unsignedOp2);
        } else {
            mpz_sub_ui(rop._data, op1._data, unsignedOp2);
        }
    }


    template<typename Type>
    static void soustraction(mpz_nombre &rop, Type op1, const mpz_nombre &op2, std::false_type /*is_signed*/) {
        mpz_ui_sub(rop._data, op1, op2._data);
    }

    template<typename Type>
    static void soustraction(mpz_nombre &rop, Type op1, const mpz_nombre &op2, std::true_type /*is_signed*/) {
        typedef typename std::make_unsigned<Type>::type unsigned_type;
        bool negatif = op1 < 0;
        auto unsignedOp1 = static_cast<unsigned_type>(negatif ? -op1 : op1);
        if (negatif) {
            mpz_add_ui(rop._data, op2._data, unsignedOp1);
            mpz_neg(rop._data, rop._data);
        } else {
            mpz_ui_sub(rop._data, unsignedOp1, op2._data);
        }
    }

    template<typename T>
    mpz_nombre &operator-=(const T &op) {
        soustraction(*this, *this, op);
        return *this;
    }

    template<typename T>
    mpz_nombre operator-(const T &op) const {
        mpz_nombre rop;
        soustraction(rop, *this, op);
        return rop;
    }
    // endregion Soustraction

    // region Multiplication
    static void multiplication(mpz_nombre &rop, const mpz_nombre &op1, const mpz_nombre &op2) {
        mpz_mul(rop._data, op1._data, op2._data);
    }

    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    static void multiplication(mpz_nombre &rop, const mpz_nombre &op1, Type op2) {
        multiplication(rop, op1, op2, std::is_signed<Type>());
    }

    template<typename Type>
    static void multiplication(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::false_type /*is_signed*/) {
        mpz_mul_ui(rop._data, op1._data, op2);
    }

    template<typename Type>
    static void multiplication(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::true_type /*is_signed*/) {
        mpz_mul_si(rop._data, op1._data, op2);
    }

    template<typename T>
    mpz_nombre &operator*=(const T &op) {
        multiplication(*this, *this, op);
        return *this;
    }

    template<typename T>
    mpz_nombre operator*(const T &op) const {
        mpz_nombre rop;
        multiplication(rop, *this, op);
        return rop;
    }
    // endregion Multiplication

    // region Division
    static void division(mpz_nombre &rop, const mpz_nombre &op1, const mpz_nombre &op2) {
        mpz_fdiv_q(rop._data, op1._data, op2._data);
    }

    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    static void division(mpz_nombre &rop, const mpz_nombre &op1, Type op2) {
        division(rop, op1, op2, std::is_signed<Type>());
    }

    template<typename Type>
    static void division(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::false_type /*is_signed*/) {
        mpz_fdiv_q_ui(rop._data, op1._data, op2);
    }

    template<typename Type>
    static void division(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::true_type /*is_signed*/) {
        typedef typename std::make_unsigned<Type>::type unsigned_type;
        bool negatif = op2 < 0;
        auto unsignedOp2 = static_cast<unsigned_type>(negatif ? -op2 : op2);
        mpz_fdiv_q_ui(rop._data, op1._data, unsignedOp2);
        if (negatif) {
            mpz_neg(rop._data, rop._data);
        }
    }

    template<typename T>
    mpz_nombre &operator/=(const T &op) {
        division(*this, *this, op);
        return *this;
    }

    template<typename T>
    mpz_nombre operator/(const T &op) const {
        mpz_nombre rop;
        division(rop, *this, op);
        return rop;
    }

    static bool divisible(const mpz_nombre &op1, const mpz_nombre &op2);

    static bool divisible(const mpz_nombre &op1, unsigned long int op2);
    // endregion Division

    // region Modulo
    static void modulo(mpz_nombre &rop, const mpz_nombre &op1, const mpz_nombre &op2) {
        mpz_mod(rop._data, op1._data, op2._data);
    }

    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    static void modulo(mpz_nombre &rop, const mpz_nombre &op1, Type op2) {
        modulo(rop, op1, op2, std::is_signed<Type>());
    }

    template<typename Type, typename = typename std::enable_if<std::is_integral<Type>::value, Type>::type>
    static void modulo(Type &rop, const mpz_nombre &op1, Type op2) {
        modulo(rop, op1, op2, std::is_signed<Type>());
    }

    template<typename Type>
    static void modulo(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::false_type /*is_signed*/) {
        mpz_mod_ui(rop._data, op1._data, op2);
    }

    template<typename Type>
    static void modulo(mpz_nombre &rop, const mpz_nombre &op1, Type op2, std::true_type /*is_signed*/) {
        typedef typename std::make_unsigned<Type>::type unsigned_type;
        bool negatif = op2 < 0;
        auto unsignedOp2 = static_cast<unsigned_type>(negatif ? -op2 : op2);
        mpz_mod_ui(rop._data, op1._data, unsignedOp2);
        if (negatif) {
            mpz_neg(rop._data, rop._data);
        }
    }

    template<typename Type>
    static void modulo(Type &rop, const mpz_nombre &op1, Type op2, std::false_type /*is_signed*/) {
        rop = mpz_fdiv_ui(op1._data, op2);
    }

    template<typename Type>
    static void modulo(Type &rop, const mpz_nombre &op1, Type op2, std::true_type /*is_signed*/) {
        typedef typename std::make_unsigned<Type>::type unsigned_type;
        bool negatif = op2 < 0;
        auto unsignedOp2 = static_cast<unsigned_type>(negatif ? -op2 : op2);
        unsigned long unsignedRop = mpz_fdiv_ui(op1._data, unsignedOp2);
        rop = static_cast<Type>(unsignedRop);
    }

    template<typename T>
    mpz_nombre &operator%=(const T &op) {
        modulo(*this, *this, op);
        return *this;
    }

    template<typename T>
    T operator%(const T &op) const {
        T rop;
        modulo(rop, *this, op);
        return rop;
    }
    // endregion Modulo

    // region AND
    mpz_nombre &operator&=(const mpz_nombre &op);

    mpz_nombre operator&(const mpz_nombre &op) const;
    // endregion AND

    // region OR
    mpz_nombre &operator|=(const mpz_nombre &op);

    mpz_nombre operator|(const mpz_nombre &op) const;
    // endregion OR

    // region XOR
    mpz_nombre &operator^=(const mpz_nombre &op);

    mpz_nombre operator^(const mpz_nombre &op) const;
    // endregion XOR

    mpz_nombre operator<<(const unsigned long &b) const;

    mpz_nombre operator>>(const unsigned long &b) const;

    // region Chiffres
    void boucle_chiffre(const std::function<void(unsigned long int)> &op, unsigned long int base = 10) const {
        mpz_nombre n(_data);
        while (n != 0l) {
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

    friend void swap(mpz_nombre &a, mpz_nombre &b) {
        std::swap(a._data, b._data);
    }

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
        op = negatif ? -op : op;
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
    mpz_nombre rop;
    mpz_nombre::addition(rop, op2, op1);
    return rop;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator-(const T &op1, const mpz_nombre &op2) {
    mpz_nombre rop;
    mpz_nombre::soustraction(rop, op1, op2);
    return rop;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator*(const T &op1, const mpz_nombre &op2) {
    mpz_nombre rop;
    mpz_nombre::multiplication(rop, op2, op1);
    return rop;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator/(const T &op1, const mpz_nombre &op2) {
    mpz_nombre n(op1);
    mpz_nombre rop;
    mpz_nombre::division(rop, n, op2);
    return rop;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline mpz_nombre operator%(const T &op1, const mpz_nombre &op2) {
    mpz_nombre n(op1);
    mpz_nombre rop;
    mpz_nombre::modulo(rop, n, op2);
    return rop;
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
