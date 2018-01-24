//
// Created by zongo on 31/01/17.
//

#include "mp_nombre.h"

mp_nombre::mp_nombre() {
    mpz_init(_data);
}

mp_nombre::~mp_nombre() {
    mpz_clear(_data);
}

mp_nombre::mp_nombre(const mpz_t &op) {
    mpz_init_set(_data, op);
}

mp_nombre::mp_nombre(const mp_nombre &op) {
    mpz_init_set(_data, op._data);
}

mp_nombre::mp_nombre(unsigned int op) {
    mpz_init_set_ui(_data, op);
}

mp_nombre::mp_nombre(signed int op) {
    mpz_init_set_si(_data, op);
}

mp_nombre::mp_nombre(unsigned long op) {
    mpz_init_set_ui(_data, op);
}

mp_nombre::mp_nombre(signed long op) {
    mpz_init_set_si(_data, op);
}

mp_nombre::mp_nombre(double op) {
    mpz_init_set_d(_data, op);
}

mp_nombre::mp_nombre(const std::string &op, int base) {
    mpz_init_set_str(_data, op.c_str(), base);
}

mp_nombre::mp_nombre(unsigned long long op) {
    mpz_init(_data);
    set(op);
}

mp_nombre::mp_nombre(signed long long op) {
    mpz_init(_data);
    set(op);
}

void mp_nombre::set(const mpz_t &op) {
    mpz_set(_data, op);
}

void mp_nombre::set(const mp_nombre &op) {
    mpz_set(_data, op._data);
}

void mp_nombre::set(unsigned long int op) {
    mpz_set_ui(_data, op);
}

void mp_nombre::set(signed long int op) {
    mpz_set_si(_data, op);
}

void mp_nombre::set(double op) {
    mpz_set_d(_data, op);
}

void mp_nombre::set(const std::string &op, int base) {
    mpz_set_str(_data, op.c_str(), base);
}

unsigned long mp_nombre::get_unsigned_long() const {
    return mpz_get_ui(_data);
}

signed long mp_nombre::get_signed_long() const {
    return mpz_get_si(_data);
}

double mp_nombre::get_double() const {
    return mpz_get_d(_data);
}

unsigned long long mp_nombre::get_unsigned_long_long() const {
    unsigned long long result = 0;
    mpz_export(&result, nullptr, -1, sizeof result, 0, 0, _data);
    return result;
}

void mp_nombre::swap(mp_nombre &op) {
    mpz_swap(_data, op._data);
}

const std::string mp_nombre::to_string(int base) const {
    char *str = mpz_get_str(nullptr, base, _data);
    std::string resultat(str);
    free(str);
    return resultat;
}

mp_nombre &mp_nombre::negation() {
    mpz_neg(_data, _data);
    return *this;
}

mp_nombre mp_nombre::operator-() const {
    mp_nombre resultat;
    mpz_neg(resultat._data, _data);
    return resultat;
}

mp_nombre mp_nombre::operator~() const {
    mp_nombre resultat;
    mpz_com(resultat._data, _data);
    return resultat;
}

mp_nombre &mp_nombre::operator++() {
    mpz_add_ui(_data, _data, 1);
    return *this;
}

mp_nombre &mp_nombre::operator--() {
    mpz_sub_ui(_data, _data, 1);
    return *this;
}

mp_nombre mp_nombre::operator++(int) {
    mp_nombre copie(_data);
    mpz_add_ui(_data, _data, 1);
    return copie;
}

mp_nombre mp_nombre::operator--(int) {
    mp_nombre copie(_data);
    mpz_sub_ui(_data, _data, 1);
    return copie;
}

signed short mp_nombre::signe() const {
    return mpz_sgn(_data);
}

mp_nombre &mp_nombre::operator=(const mp_nombre &op) {
    set(op);
    return *this;
}

int mp_nombre::compare(const mp_nombre &op) const {
    return mpz_cmp(_data, op._data);
}

int mp_nombre::compare(double op) const {
    return mpz_cmp_d(_data, op);
}

int mp_nombre::compare(signed long int op) const {
    return mpz_cmp_si(_data, op);
}

int mp_nombre::compare(unsigned long int op) const {
    return mpz_cmp_ui(_data, op);
}

mp_nombre mp_nombre::abs(const mp_nombre &op) {
    mp_nombre resultat;
    mpz_abs(resultat._data, op._data);
    return resultat;
}

mp_nombre mp_nombre::racine_carre(const mp_nombre &op) {
    mp_nombre resultat;
    mpz_sqrt(resultat._data, op._data);
    return resultat;
}

bool mp_nombre::carre_parfait(const mp_nombre &op) {
    return mpz_perfect_square_p(op._data) != 0;
}

mp_nombre mp_nombre::racine(const mp_nombre &op, unsigned long int n) {
    mp_nombre resultat;
    mpz_root(resultat._data, op._data, n);
    return resultat;
}

bool mp_nombre::racine_parfaite(const mp_nombre &op, unsigned long int n) {
    mp_nombre resultat;
    return mpz_root(resultat._data, op._data, n) != 0;
}

mp_nombre mp_nombre::puissance(const mp_nombre &base, unsigned long exposant) {
    mp_nombre resultat;
    mpz_pow_ui(resultat._data, base._data, exposant);
    return resultat;
}

mp_nombre mp_nombre::puissance(unsigned long base, unsigned long exposant) {
    mp_nombre resultat;
    mpz_ui_pow_ui(resultat._data, base, exposant);
    return resultat;
}

mp_nombre mp_nombre::puissance_modulaire(const mp_nombre &base, unsigned long exposant, const mp_nombre &modulo) {
    mp_nombre resultat;
    mpz_powm_ui(resultat._data, base._data, exposant, modulo._data);
    return resultat;
}

bool mp_nombre::premier(const mp_nombre &op, int probabilite) {
    return mpz_probab_prime_p(op._data, probabilite) != 0;
}

mp_nombre mp_nombre::premier_suivant(const mp_nombre &op) {
    mp_nombre resultat;
    mpz_nextprime(resultat._data, op._data);
    return resultat;
}

mp_nombre mp_nombre::PGCD(const mp_nombre &op1, const mp_nombre &op2) {
    mp_nombre resultat;
    mpz_gcd(resultat._data, op1._data, op2._data);
    return resultat;
}

mp_nombre mp_nombre::PGCD(const mp_nombre &op1, unsigned long int op2) {
    mp_nombre resultat;
    mpz_gcd_ui(resultat._data, op1._data, op2);
    return resultat;
}

mp_nombre mp_nombre::PPCM(const mp_nombre &op1, const mp_nombre &op2) {
    mp_nombre resultat;
    mpz_lcm(resultat._data, op1._data, op2._data);
    return resultat;
}

mp_nombre mp_nombre::PPCM(const mp_nombre &op1, unsigned long int op2) {
    mp_nombre resultat;
    mpz_lcm_ui(resultat._data, op1._data, op2);
    return resultat;
}

boost::optional<mp_nombre> mp_nombre::inverse_modulaire(const mp_nombre &op, const mp_nombre &modulo) {
    mp_nombre resultat;
    if (mpz_invert(resultat._data, op._data, modulo._data) != 0)
        return resultat;

    return boost::none;
}

mp_nombre mp_nombre::coefficient_binomial(const mp_nombre &n, unsigned long int k) {
    mp_nombre resultat;
    mpz_bin_ui(resultat._data, n._data, k);
    return resultat;
}

mp_nombre mp_nombre::coefficient_binomial(unsigned long int n, unsigned long int k) {
    mp_nombre resultat;
    mpz_bin_uiui(resultat._data, n, k);
    return resultat;
}

mp_nombre mp_nombre::factorielle(unsigned long int n) {
    mp_nombre resultat;
    mpz_fac_ui(resultat._data, n);
    return resultat;
}

mp_nombre mp_nombre::catalan(unsigned long int n) {
    return coefficient_binomial(2 * n, n) / (n + 1);
}

mp_nombre &mp_nombre::operator+=(const mp_nombre &op) {
    mpz_add(_data, _data, op._data);
    return *this;
}

mp_nombre &mp_nombre::operator+=(unsigned long int op) {
    mpz_add_ui(_data, _data, op);
    return *this;
}

mp_nombre mp_nombre::operator+(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_add(resultat._data, _data, op._data);
    return resultat;
}

mp_nombre mp_nombre::operator+(unsigned long int op) const {
    mp_nombre resultat;
    mpz_add_ui(resultat._data, _data, op);
    return resultat;
}

mp_nombre &mp_nombre::operator-=(const mp_nombre &op) {
    mpz_sub(_data, _data, op._data);
    return *this;
}

mp_nombre &mp_nombre::operator-=(unsigned long int op) {
    mpz_sub_ui(_data, _data, op);
    return *this;
}

mp_nombre mp_nombre::operator-(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_sub(resultat._data, _data, op._data);
    return resultat;
}

mp_nombre mp_nombre::operator-(unsigned long int op) const {
    mp_nombre resultat;
    mpz_sub_ui(resultat._data, _data, op);
    return resultat;
}

mp_nombre &mp_nombre::operator*=(const mp_nombre &op) {
    mpz_mul(_data, _data, op._data);
    return *this;
}

mp_nombre &mp_nombre::operator*=(long int op) {
    mpz_mul_si(_data, _data, op);
    return *this;
}

mp_nombre &mp_nombre::operator*=(unsigned long int op) {
    mpz_mul_ui(_data, _data, op);
    return *this;
}

mp_nombre mp_nombre::operator*(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_mul(resultat._data, _data, op._data);
    return resultat;
}

mp_nombre mp_nombre::operator*(long int op) const {
    mp_nombre resultat;
    mpz_mul_si(resultat._data, _data, op);
    return resultat;
}

mp_nombre mp_nombre::operator*(unsigned long int op) const {
    mp_nombre resultat;
    mpz_mul_ui(resultat._data, _data, op);
    return resultat;
}

mp_nombre &mp_nombre::operator/=(const mp_nombre &op) {
    mpz_fdiv_q(_data, _data, op._data);
    return *this;
}

mp_nombre &mp_nombre::operator/=(unsigned long int op) {
    mpz_fdiv_q_ui(_data, _data, op);
    return *this;
}

mp_nombre mp_nombre::operator/(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_fdiv_q(resultat._data, _data, op._data);
    return resultat;
}

mp_nombre mp_nombre::operator/(unsigned long int op) const {
    mp_nombre resultat;
    mpz_fdiv_q_ui(resultat._data, _data, op);
    return resultat;
}

bool mp_nombre::divisible(const mp_nombre &op1, const mp_nombre &op2) {
    return mpz_divisible_p(op1._data, op2._data) != 0;
}

bool mp_nombre::divisible(const mp_nombre &op1, unsigned long int op2) {
    return mpz_divisible_ui_p(op1._data, op2) != 0;
}

mp_nombre &mp_nombre::operator%=(const mp_nombre &op) {
    mpz_mod(_data, _data, op._data);
    return *this;
}

mp_nombre &mp_nombre::operator%=(unsigned long int op) {
    mpz_mod_ui(_data, _data, op);
    return *this;
}

mp_nombre mp_nombre::operator%(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_mod(resultat._data, _data, op._data);
    return resultat;
}

unsigned long int mp_nombre::operator%(unsigned long int op) const {
    mp_nombre resultat;
    return mpz_mod_ui(resultat._data, _data, op);
}

mp_nombre &mp_nombre::operator&=(const mp_nombre &op) {
    mpz_and(_data, _data, op._data);
    return *this;
}

mp_nombre mp_nombre::operator&(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_and(resultat._data, _data, op._data);
    return resultat;
}

mp_nombre &mp_nombre::operator|=(const mp_nombre &op) {
    mpz_ior(_data, _data, op._data);
    return *this;
}

mp_nombre mp_nombre::operator|(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_ior(resultat._data, _data, op._data);
    return resultat;
}

mp_nombre &mp_nombre::operator^=(const mp_nombre &op) {
    mpz_xor(_data, _data, op._data);
    return *this;
}

mp_nombre mp_nombre::operator^(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_xor(resultat._data, _data, op._data);
    return resultat;
}

mp_nombre mp_nombre::operator<<(const unsigned long &b) const {
    mp_nombre resultat;
    mpz_mul_2exp(resultat._data, _data, b);
    return resultat;
}

mp_nombre mp_nombre::operator>>(const unsigned long &b) const {
    mp_nombre resultat;
    mpz_fdiv_q_2exp(resultat._data, _data, b);
    return resultat;
}

bool mp_nombre::premier(int probabilite) const {
    return mpz_probab_prime_p(_data, probabilite) != 0;
}

mp_nombre &mp_nombre::premier_suivant() {
    mpz_nextprime(_data, _data);
    return *this;
}

namespace std {
    mp_nombre abs(const mp_nombre &op) {
        return mp_nombre::abs(op);
    }

    void swap(mp_nombre &op1, mp_nombre &op2) {
        op1.swap(op2);
    }

    mp_nombre sqrt(const mp_nombre &op) {
        return mp_nombre::racine_carre(op);
    }

    mp_nombre cbrt(const mp_nombre &op) {
        return mp_nombre::racine(op, 3);
    }

    std::ostream &operator<<(std::ostream &os, const mp_nombre &op) {
        os << op.to_string();
        return os;
    }

    std::istream &operator>>(std::istream &is, mp_nombre &op) {
        std::string str;
        is >> str;
        op.set(str);
        return is;
    }
}
