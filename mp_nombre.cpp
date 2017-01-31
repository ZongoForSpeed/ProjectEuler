//
// Created by zongo on 31/01/17.
//

#include "mp_nombre.h"

mp_nombre::mp_nombre() {
    mpz_init(data);
}

mp_nombre::~mp_nombre() {
    mpz_clear(data);
}

mp_nombre::mp_nombre(const mpz_t &op) {
    mpz_init_set(data, op);
}

mp_nombre::mp_nombre(const mp_nombre &op) {
    mpz_init_set(data, op.data);
}

mp_nombre::mp_nombre(unsigned int op) {
    mpz_init_set_ui(data, op);
}

mp_nombre::mp_nombre(signed int op) {
    mpz_init_set_si(data, op);
}

mp_nombre::mp_nombre(unsigned long op) {
    mpz_init_set_ui(data, op);
}

mp_nombre::mp_nombre(signed long op) {
    mpz_init_set_si(data, op);
}

mp_nombre::mp_nombre(double op) {
    mpz_init_set_d(data, op);
}

mp_nombre::mp_nombre(const std::string &op, int base) {
    mpz_init_set_str(data, op.c_str(), base);
}

mp_nombre::mp_nombre(unsigned long long op) {
    mpz_init(data);
    set(op);
}

mp_nombre::mp_nombre(signed long long op) {
    mpz_init(data);
    set(op);
}

void mp_nombre::set(const mpz_t &op) {
    mpz_set(data, op);
}

void mp_nombre::set(const mp_nombre &op) {
    mpz_set(data, op.data);
}

void mp_nombre::set(unsigned long int op) {
    mpz_set_ui(data, op);
}

void mp_nombre::set(signed long int op) {
    mpz_set_si(data, op);
}

void mp_nombre::set(double op) {
    mpz_set_d(data, op);
}

void mp_nombre::set(const std::string &op, int base) {
    mpz_set_str(data, op.c_str(), base);
}

unsigned long mp_nombre::get_unsigned_long() const {
    return mpz_get_ui(data);
}

signed long mp_nombre::get_signed_long() const {
    return mpz_get_si(data);
}

double mp_nombre::get_double() const {
    return mpz_get_d(data);
}

unsigned long long mp_nombre::get_unsigned_long_long() const {
    unsigned long long result = 0;
    mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
    return result;
}

void mp_nombre::swap(mp_nombre &op) {
    mpz_swap(data, op.data);
}

const std::string mp_nombre::to_string(int base) const {
    char *str = mpz_get_str(NULL, base, data);
    std::string resultat(str);
    free(str);
    return resultat;
}

mp_nombre &mp_nombre::negation() {
    mpz_neg(data, data);
    return *this;
}

mp_nombre mp_nombre::operator-() const {
    mp_nombre resultat;
    mpz_neg(resultat.data, data);
    return resultat;
}

mp_nombre mp_nombre::operator~() const {
    mp_nombre resultat;
    mpz_com(resultat.data, data);
    return resultat;
}

mp_nombre &mp_nombre::operator++() {
    mpz_add_ui(data, data, 1);
    return *this;
}

mp_nombre &mp_nombre::operator--() {
    mpz_sub_ui(data, data, 1);
    return *this;
}

mp_nombre mp_nombre::operator++(int) {
    mp_nombre copie(data);
    mpz_add_ui(data, data, 1);
    return copie;
}

mp_nombre mp_nombre::operator--(int) {
    mp_nombre copie(data);
    mpz_sub_ui(data, data, 1);
    return copie;
}

signed short mp_nombre::signe() const {
    return mpz_sgn(data);
}

mp_nombre &mp_nombre::operator=(const mp_nombre &op) {
    set(op);
    return *this;
}

int mp_nombre::compare(const mp_nombre &op) const {
    return mpz_cmp(data, op.data);
}

int mp_nombre::compare(double op) const {
    return mpz_cmp_d(data, op);
}

int mp_nombre::compare(signed long int op) const {
    return mpz_cmp_si(data, op);
}

int mp_nombre::compare(unsigned long int op) const {
    return mpz_cmp_ui(data, op);
}

mp_nombre mp_nombre::abs(const mp_nombre &op) {
    mp_nombre resultat;
    mpz_abs(resultat.data, op.data);
    return resultat;
}

mp_nombre mp_nombre::racine_carre(const mp_nombre &op) {
    mp_nombre resultat;
    mpz_sqrt(resultat.data, op.data);
    return resultat;
}

bool mp_nombre::carre_parfait(const mp_nombre &op) {
    return mpz_perfect_square_p(op.data) != 0;
}

mp_nombre mp_nombre::racine(const mp_nombre &op, unsigned long int n) {
    mp_nombre resultat;
    mpz_root(resultat.data, op.data, n);
    return resultat;
}

mp_nombre mp_nombre::puissance(const mp_nombre &base, unsigned long exposant) {
    mp_nombre resultat;
    mpz_pow_ui(resultat.data, base.data, exposant);
    return resultat;
}

mp_nombre mp_nombre::puissance(unsigned long base, unsigned long exposant) {
    mp_nombre resultat;
    mpz_ui_pow_ui(resultat.data, base, exposant);
    return resultat;
}

mp_nombre mp_nombre::puissance_modulaire(const mp_nombre &base, unsigned long exposant, const mp_nombre &modulo) {
    mp_nombre resultat;
    mpz_powm_ui(resultat.data, base.data, exposant, modulo.data);
    return resultat;
}

bool mp_nombre::premier(const mp_nombre &op, int probabilite) {
    return mpz_probab_prime_p(op.data, probabilite) != 0;
}

mp_nombre mp_nombre::premier_suivant(const mp_nombre &op) {
    mp_nombre resultat;
    mpz_nextprime(resultat.data, op.data);
    return resultat;
}

mp_nombre mp_nombre::PGCD(const mp_nombre &op1, const mp_nombre &op2) {
    mp_nombre resultat;
    mpz_gcd(resultat.data, op1.data, op2.data);
    return resultat;
}

mp_nombre mp_nombre::PGCD(const mp_nombre &op1, unsigned long int op2) {
    mp_nombre resultat;
    mpz_gcd_ui(resultat.data, op1.data, op2);
    return resultat;
}

mp_nombre mp_nombre::PPCM(const mp_nombre &op1, const mp_nombre &op2) {
    mp_nombre resultat;
    mpz_lcm(resultat.data, op1.data, op2.data);
    return resultat;
}

mp_nombre mp_nombre::PPCM(const mp_nombre &op1, unsigned long int op2) {
    mp_nombre resultat;
    mpz_lcm_ui(resultat.data, op1.data, op2);
    return resultat;
}

boost::optional<mp_nombre> mp_nombre::inverse_modulaire(const mp_nombre &op, const mp_nombre &modulo) {
    mp_nombre resultat;
    if (mpz_invert(resultat.data, op.data, modulo.data) != 0)
        return resultat;

    return boost::none;
}

mp_nombre mp_nombre::coefficient_binomial(const mp_nombre &n, unsigned long int k) {
    mp_nombre resultat;
    mpz_bin_ui(resultat.data, n.data, k);
    return resultat;
}

mp_nombre mp_nombre::coefficient_binomial(unsigned long int n, unsigned long int k) {
    mp_nombre resultat;
    mpz_bin_uiui(resultat.data, n, k);
    return resultat;
}

mp_nombre mp_nombre::factorielle(unsigned long int n) {
    mp_nombre resultat;
    mpz_fac_ui(resultat.data, n);
    return resultat;
}

mp_nombre mp_nombre::catalan(unsigned long int n) {
    return coefficient_binomial(2 * n, n) / (n + 1);
}

mp_nombre &mp_nombre::operator+=(const mp_nombre &op) {
    mpz_add(data, data, op.data);
    return *this;
}

mp_nombre &mp_nombre::operator+=(unsigned long int op) {
    mpz_add_ui(data, data, op);
    return *this;
}

mp_nombre mp_nombre::operator+(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_add(resultat.data, data, op.data);
    return resultat;
}

mp_nombre mp_nombre::operator+(unsigned long int op) const {
    mp_nombre resultat;
    mpz_add_ui(resultat.data, data, op);
    return resultat;
}

mp_nombre &mp_nombre::operator-=(const mp_nombre &op) {
    mpz_sub(data, data, op.data);
    return *this;
}

mp_nombre &mp_nombre::operator-=(unsigned long int op) {
    mpz_sub_ui(data, data, op);
    return *this;
}

mp_nombre mp_nombre::operator-(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_sub(resultat.data, data, op.data);
    return resultat;
}

mp_nombre mp_nombre::operator-(unsigned long int op) const {
    mp_nombre resultat;
    mpz_sub_ui(resultat.data, data, op);
    return resultat;
}

mp_nombre &mp_nombre::operator*=(const mp_nombre &op) {
    mpz_mul(data, data, op.data);
    return *this;
}

mp_nombre &mp_nombre::operator*=(long int op) {
    mpz_mul_si(data, data, op);
    return *this;
}

mp_nombre &mp_nombre::operator*=(unsigned long int op) {
    mpz_mul_ui(data, data, op);
    return *this;
}

mp_nombre mp_nombre::operator*(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_mul(resultat.data, data, op.data);
    return resultat;
}

mp_nombre mp_nombre::operator*(long int op) const {
    mp_nombre resultat;
    mpz_mul_si(resultat.data, data, op);
    return resultat;
}

mp_nombre mp_nombre::operator*(unsigned long int op) const {
    mp_nombre resultat;
    mpz_mul_ui(resultat.data, data, op);
    return resultat;
}

mp_nombre &mp_nombre::operator/=(const mp_nombre &op) {
    mpz_fdiv_q(data, data, op.data);
    return *this;
}

mp_nombre &mp_nombre::operator/=(unsigned long int op) {
    mpz_fdiv_q_ui(data, data, op);
    return *this;
}

mp_nombre mp_nombre::operator/(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_fdiv_q(resultat.data, data, op.data);
    return resultat;
}

mp_nombre mp_nombre::operator/(unsigned long int op) const {
    mp_nombre resultat;
    mpz_fdiv_q_ui(resultat.data, data, op);
    return resultat;
}

bool mp_nombre::divisible(const mp_nombre &op1, const mp_nombre &op2) {
    return mpz_divisible_p(op1.data, op2.data) != 0;
}

bool mp_nombre::divisible(const mp_nombre &op1, unsigned long int op2) {
    return mpz_divisible_ui_p(op1.data, op2) != 0;
}

mp_nombre &mp_nombre::operator%=(const mp_nombre &op) {
    mpz_mod(data, data, op.data);
    return *this;
}

mp_nombre &mp_nombre::operator%=(unsigned long int op) {
    mpz_mod_ui(data, data, op);
    return *this;
}

mp_nombre mp_nombre::operator%(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_mod(resultat.data, data, op.data);
    return resultat;
}

unsigned long int mp_nombre::operator%(unsigned long int op) const {
    mp_nombre resultat;
    return mpz_mod_ui(resultat.data, data, op);
}

mp_nombre &mp_nombre::operator&=(const mp_nombre &op) {
    mpz_and(data, data, op.data);
    return *this;
}

mp_nombre mp_nombre::operator&(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_and(resultat.data, data, op.data);
    return resultat;
}

mp_nombre &mp_nombre::operator|=(const mp_nombre &op) {
    mpz_ior(data, data, op.data);
    return *this;
}

mp_nombre mp_nombre::operator|(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_ior(resultat.data, data, op.data);
    return resultat;
}

mp_nombre &mp_nombre::operator^=(const mp_nombre &op) {
    mpz_xor(data, data, op.data);
    return *this;
}

mp_nombre mp_nombre::operator^(const mp_nombre &op) const {
    mp_nombre resultat;
    mpz_xor(resultat.data, data, op.data);
    return resultat;
}

mp_nombre mp_nombre::operator<<(const unsigned long &b) const {
    mp_nombre resultat;
    mpz_mul_2exp(resultat.data, data, b);
    return resultat;
}

mp_nombre mp_nombre::operator>>(const unsigned long &b) const {
    mp_nombre resultat;
    mpz_fdiv_q_2exp(resultat.data, data, b);
    return resultat;
}

namespace std
{
    mp_nombre abs(const mp_nombre & op)
    {
        return mp_nombre::abs(op);
    }

    void swap(mp_nombre & op1, mp_nombre & op2)
    {
        op1.swap(op2);
    }

    mp_nombre sqrt(const mp_nombre & op)
    {
        return mp_nombre::racine_carre(op);
    }

    mp_nombre cbrt(const mp_nombre & op)
    {
        return mp_nombre::racine(op, 3);
    }

    std::ostream& operator<<(std::ostream& os, const mp_nombre & op)
    {
        os << op.to_string();
        return os;
    }

    std::istream& operator>>(std::istream& is, mp_nombre & op)
    {
        std::string str;
        is >> str;
        op.set(str);
        return is;
    }
}
