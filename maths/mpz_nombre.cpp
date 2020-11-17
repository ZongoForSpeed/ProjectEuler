//
// Created by zongo on 31/01/17.
//

#include "mpz_nombre.h"

mpz_nombre::mpz_nombre() {
    mpz_init(_data);
}

mpz_nombre::~mpz_nombre() {
    mpz_clear(_data);
}

mpz_nombre::mpz_nombre(const mpz_t &op) {
    mpz_init_set(_data, op);
}

mpz_nombre::mpz_nombre(const mpz_nombre &op) {
    mpz_init_set(_data, op._data);
}

mpz_nombre::mpz_nombre(unsigned int op) {
    mpz_init_set_ui(_data, op);
}

mpz_nombre::mpz_nombre(signed int op) {
    mpz_init_set_si(_data, op);
}

mpz_nombre::mpz_nombre(unsigned long op) {
    mpz_init_set_ui(_data, op);
}

mpz_nombre::mpz_nombre(signed long op) {
    mpz_init_set_si(_data, op);
}

mpz_nombre::mpz_nombre(double op) {
    mpz_init_set_d(_data, op);
}

mpz_nombre::mpz_nombre(const std::string &op, int base) {
    mpz_init_set_str(_data, op.c_str(), base);
}

mpz_nombre::mpz_nombre(unsigned long long op) {
    mpz_init(_data);
    set(op);
}

mpz_nombre::mpz_nombre(signed long long op) {
    mpz_init(_data);
    set(op);
}

void mpz_nombre::set(const mpz_t &op) {
    mpz_set(_data, op);
}

void mpz_nombre::set(const mpz_nombre &op) {
    mpz_set(_data, op._data);
}

void mpz_nombre::set(unsigned long int op) {
    mpz_set_ui(_data, op);
}

void mpz_nombre::set(signed long int op) {
    mpz_set_si(_data, op);
}

void mpz_nombre::set(double op) {
    mpz_set_d(_data, op);
}

void mpz_nombre::set(const std::string &op, int base) {
    mpz_set_str(_data, op.c_str(), base);
}

unsigned long mpz_nombre::get_unsigned_long() const {
    return mpz_get_ui(_data);
}

signed long mpz_nombre::get_signed_long() const {
    return mpz_get_si(_data);
}

double mpz_nombre::get_double() const {
    return mpz_get_d(_data);
}

#ifdef WIN32
unsigned long long mpz_nombre::get_unsigned_long_long() const {
    return std::stoull(to_string());
}
#else
unsigned long long mpz_nombre::get_unsigned_long_long() const {
    unsigned long long result = 0;
    mpz_export(&result, nullptr, -1, sizeof result, 0, 0, _data);
    return result;
}
#endif

void mpz_nombre::swap(mpz_nombre &op) {
    mpz_swap(_data, op._data);
}

std::string mpz_nombre::to_string(int base) const {
    char *str = mpz_get_str(nullptr, base, _data);
    std::string resultat(str);
    free(str);
    return resultat;
}

mpz_nombre &mpz_nombre::negation() {
    mpz_neg(_data, _data);
    return *this;
}

mpz_nombre mpz_nombre::operator-() const {
    mpz_nombre resultat;
    mpz_neg(resultat._data, _data);
    return resultat;
}

mpz_nombre mpz_nombre::operator~() const {
    mpz_nombre resultat;
    mpz_com(resultat._data, _data);
    return resultat;
}

mpz_nombre &mpz_nombre::operator++() {
    mpz_add_ui(_data, _data, 1);
    return *this;
}

mpz_nombre &mpz_nombre::operator--() {
    mpz_sub_ui(_data, _data, 1);
    return *this;
}

const mpz_nombre mpz_nombre::operator++(int) {
    mpz_nombre copie(_data);
    mpz_add_ui(_data, _data, 1);
    return copie;
}

mpz_nombre mpz_nombre::operator--(int) {
    mpz_nombre copie(_data);
    mpz_sub_ui(_data, _data, 1);
    return copie;
}

signed short mpz_nombre::signe() const {
    return mpz_sgn(_data);
}

mpz_nombre &mpz_nombre::operator=(const mpz_nombre &op) {
    set(op);
    return *this;
}

int mpz_nombre::compare(const mpz_nombre &op) const {
    return mpz_cmp(_data, op._data);
}

int mpz_nombre::compare(double op) const {
    return mpz_cmp_d(_data, op);
}

int mpz_nombre::compare(signed long int op) const {
    return mpz_cmp_si(_data, op);
}

int mpz_nombre::compare(unsigned long int op) const {
    return mpz_cmp_ui(_data, op);
}

mpz_nombre mpz_nombre::abs(const mpz_nombre &op) {
    mpz_nombre resultat;
    mpz_abs(resultat._data, op._data);
    return resultat;
}

mpz_nombre mpz_nombre::racine_carre(const mpz_nombre &op) {
    mpz_nombre resultat;
    mpz_sqrt(resultat._data, op._data);
    return resultat;
}

bool mpz_nombre::carre_parfait(const mpz_nombre &op) {
    return mpz_perfect_square_p(op._data) != 0;
}

mpz_nombre mpz_nombre::racine(const mpz_nombre &op, unsigned long int n) {
    mpz_nombre resultat;
    mpz_root(resultat._data, op._data, n);
    return resultat;
}

bool mpz_nombre::racine_parfaite(const mpz_nombre &op, unsigned long int n) {
    mpz_nombre resultat;
    return mpz_root(resultat._data, op._data, n) != 0;
}

mpz_nombre mpz_nombre::puissance(const mpz_nombre &base, unsigned long exposant) {
    mpz_nombre resultat;
    mpz_pow_ui(resultat._data, base._data, exposant);
    return resultat;
}

mpz_nombre mpz_nombre::puissance(unsigned long base, unsigned long exposant) {
    mpz_nombre resultat;
    mpz_ui_pow_ui(resultat._data, base, exposant);
    return resultat;
}

mpz_nombre mpz_nombre::puissance_modulaire(const mpz_nombre &base, unsigned long exposant, const mpz_nombre &modulo) {
    mpz_nombre resultat;
    mpz_powm_ui(resultat._data, base._data, exposant, modulo._data);
    return resultat;
}

bool mpz_nombre::premier(const mpz_nombre &op, int probabilite) {
    return mpz_probab_prime_p(op._data, probabilite) != 0;
}

mpz_nombre mpz_nombre::premier_suivant(const mpz_nombre &op) {
    mpz_nombre resultat;
    mpz_nextprime(resultat._data, op._data);
    return resultat;
}

mpz_nombre mpz_nombre::PGCD(const mpz_nombre &op1, const mpz_nombre &op2) {
    mpz_nombre resultat;
    mpz_gcd(resultat._data, op1._data, op2._data);
    return resultat;
}

mpz_nombre mpz_nombre::PGCD(const mpz_nombre &op1, unsigned long int op2) {
    mpz_nombre resultat;
    mpz_gcd_ui(resultat._data, op1._data, op2);
    return resultat;
}

mpz_nombre mpz_nombre::PPCM(const mpz_nombre &op1, const mpz_nombre &op2) {
    mpz_nombre resultat;
    mpz_lcm(resultat._data, op1._data, op2._data);
    return resultat;
}

mpz_nombre mpz_nombre::PPCM(const mpz_nombre &op1, unsigned long int op2) {
    mpz_nombre resultat;
    mpz_lcm_ui(resultat._data, op1._data, op2);
    return resultat;
}

std::optional<mpz_nombre> mpz_nombre::inverse_modulaire(const mpz_nombre &op, const mpz_nombre &modulo) {
    mpz_nombre resultat;
    if (mpz_invert(resultat._data, op._data, modulo._data) != 0)
        return std::move(resultat);

    return std::nullopt;
}

mpz_nombre mpz_nombre::coefficient_binomial(const mpz_nombre &n, unsigned long int k) {
    mpz_nombre resultat;
    mpz_bin_ui(resultat._data, n._data, k);
    return resultat;
}

mpz_nombre mpz_nombre::coefficient_binomial(unsigned long int n, unsigned long int k) {
    mpz_nombre resultat;
    mpz_bin_uiui(resultat._data, n, k);
    return resultat;
}

mpz_nombre mpz_nombre::factorielle(unsigned long int n) {
    mpz_nombre resultat;
    mpz_fac_ui(resultat._data, n);
    return resultat;
}

mpz_nombre mpz_nombre::catalan(unsigned long int n) {
    return coefficient_binomial(2 * n, n) / (n + 1);
}

mpz_nombre &mpz_nombre::operator+=(const mpz_nombre &op) {
    mpz_add(_data, _data, op._data);
    return *this;
}

mpz_nombre &mpz_nombre::operator+=(unsigned long int op) {
    mpz_add_ui(_data, _data, op);
    return *this;
}

mpz_nombre mpz_nombre::operator+(const mpz_nombre &op) const {
    mpz_nombre resultat;
    mpz_add(resultat._data, _data, op._data);
    return resultat;
}

mpz_nombre mpz_nombre::operator+(unsigned long int op) const {
    mpz_nombre resultat;
    mpz_add_ui(resultat._data, _data, op);
    return resultat;
}

mpz_nombre &mpz_nombre::operator-=(const mpz_nombre &op) {
    mpz_sub(_data, _data, op._data);
    return *this;
}

mpz_nombre &mpz_nombre::operator-=(unsigned long int op) {
    mpz_sub_ui(_data, _data, op);
    return *this;
}

mpz_nombre mpz_nombre::operator-(const mpz_nombre &op) const {
    mpz_nombre resultat;
    mpz_sub(resultat._data, _data, op._data);
    return resultat;
}

mpz_nombre mpz_nombre::operator-(unsigned long int op) const {
    mpz_nombre resultat;
    mpz_sub_ui(resultat._data, _data, op);
    return resultat;
}

mpz_nombre &mpz_nombre::operator*=(const mpz_nombre &op) {
    mpz_mul(_data, _data, op._data);
    return *this;
}

mpz_nombre &mpz_nombre::operator*=(long int op) {
    mpz_mul_si(_data, _data, op);
    return *this;
}

mpz_nombre &mpz_nombre::operator*=(unsigned long int op) {
    mpz_mul_ui(_data, _data, op);
    return *this;
}

mpz_nombre mpz_nombre::operator*(const mpz_nombre &op) const {
    mpz_nombre resultat;
    mpz_mul(resultat._data, _data, op._data);
    return resultat;
}

mpz_nombre mpz_nombre::operator*(long int op) const {
    mpz_nombre resultat;
    mpz_mul_si(resultat._data, _data, op);
    return resultat;
}

mpz_nombre mpz_nombre::operator*(unsigned long int op) const {
    mpz_nombre resultat;
    mpz_mul_ui(resultat._data, _data, op);
    return resultat;
}

mpz_nombre &mpz_nombre::operator/=(const mpz_nombre &op) {
    mpz_fdiv_q(_data, _data, op._data);
    return *this;
}

mpz_nombre &mpz_nombre::operator/=(unsigned long int op) {
    mpz_fdiv_q_ui(_data, _data, op);
    return *this;
}

mpz_nombre mpz_nombre::operator/(const mpz_nombre &op) const {
    mpz_nombre resultat;
    mpz_fdiv_q(resultat._data, _data, op._data);
    return resultat;
}

mpz_nombre mpz_nombre::operator/(unsigned long int op) const {
    mpz_nombre resultat;
    mpz_fdiv_q_ui(resultat._data, _data, op);
    return resultat;
}

bool mpz_nombre::divisible(const mpz_nombre &op1, const mpz_nombre &op2) {
    return mpz_divisible_p(op1._data, op2._data) != 0;
}

bool mpz_nombre::divisible(const mpz_nombre &op1, unsigned long int op2) {
    return mpz_divisible_ui_p(op1._data, op2) != 0;
}

mpz_nombre &mpz_nombre::operator%=(const mpz_nombre &op) {
    mpz_mod(_data, _data, op._data);
    return *this;
}

mpz_nombre &mpz_nombre::operator%=(unsigned long int op) {
    mpz_mod_ui(_data, _data, op);
    return *this;
}

mpz_nombre mpz_nombre::operator%(const mpz_nombre &op) const {
    mpz_nombre resultat;
    mpz_mod(resultat._data, _data, op._data);
    return resultat;
}

unsigned long int mpz_nombre::operator%(unsigned long int op) const {
    mpz_nombre resultat;
    return mpz_mod_ui(resultat._data, _data, op);
}

mpz_nombre &mpz_nombre::operator&=(const mpz_nombre &op) {
    mpz_and(_data, _data, op._data);
    return *this;
}

mpz_nombre mpz_nombre::operator&(const mpz_nombre &op) const {
    mpz_nombre resultat;
    mpz_and(resultat._data, _data, op._data);
    return resultat;
}

mpz_nombre &mpz_nombre::operator|=(const mpz_nombre &op) {
    mpz_ior(_data, _data, op._data);
    return *this;
}

mpz_nombre mpz_nombre::operator|(const mpz_nombre &op) const {
    mpz_nombre resultat;
    mpz_ior(resultat._data, _data, op._data);
    return resultat;
}

mpz_nombre &mpz_nombre::operator^=(const mpz_nombre &op) {
    mpz_xor(_data, _data, op._data);
    return *this;
}

mpz_nombre mpz_nombre::operator^(const mpz_nombre &op) const {
    mpz_nombre resultat;
    mpz_xor(resultat._data, _data, op._data);
    return resultat;
}

mpz_nombre mpz_nombre::operator<<(const unsigned long &b) const {
    mpz_nombre resultat;
    mpz_mul_2exp(resultat._data, _data, b);
    return resultat;
}

mpz_nombre mpz_nombre::operator>>(const unsigned long &b) const {
    mpz_nombre resultat;
    mpz_fdiv_q_2exp(resultat._data, _data, b);
    return resultat;
}

bool mpz_nombre::premier(int probabilite) const {
    return mpz_probab_prime_p(_data, probabilite) != 0;
}

mpz_nombre &mpz_nombre::premier_suivant() {
    mpz_nextprime(_data, _data);
    return *this;
}

namespace std {
    mpz_nombre abs(const mpz_nombre &op) {
        return mpz_nombre::abs(op);
    }

    void swap(mpz_nombre &op1, mpz_nombre &op2) {
        op1.swap(op2);
    }

    mpz_nombre sqrt(const mpz_nombre &op) {
        return mpz_nombre::racine_carre(op);
    }

    mpz_nombre cbrt(const mpz_nombre &op) {
        return mpz_nombre::racine(op, 3);
    }

    std::ostream &operator<<(std::ostream &os, const mpz_nombre &op) {
        os << op.to_string();
        return os;
    }

    std::istream &operator>>(std::istream &is, mpz_nombre &op) {
        std::string str;
        is >> str;
        op.set(str);
        return is;
    }
}
