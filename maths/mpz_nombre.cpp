//
// Created by zongo on 31/01/17.
//

#include "mpz_nombre.h"

mpz_nombre::mpz_nombre() {
    init();
    mpz_init(_data);
}

mpz_nombre::~mpz_nombre() {
    clear();
}

mpz_nombre::mpz_nombre(mpz_srcptr op) {
    init();
    mpz_init_set(_data, op);
}

mpz_nombre::mpz_nombre(const mpz_nombre &op) {
    init();
    mpz_init_set(_data, op._data);
}

mpz_nombre::mpz_nombre(mpz_nombre &&op) : _data(std::exchange(op._data, nullptr)) {
}

mpz_nombre::mpz_nombre(unsigned int op) {
    init();
    mpz_init_set_ui(_data, op);
}

mpz_nombre::mpz_nombre(signed int op) {
    init();
    mpz_init_set_si(_data, op);
}

mpz_nombre::mpz_nombre(unsigned long op) {
    init();
    mpz_init_set_ui(_data, op);
}

mpz_nombre::mpz_nombre(signed long op) {
    init();
    mpz_init_set_si(_data, op);
}

mpz_nombre::mpz_nombre(double op) {
    init();
    mpz_init_set_d(_data, op);
}

mpz_nombre::mpz_nombre(const std::string &op, int base) {
    init();
    mpz_init_set_str(_data, op.c_str(), base);
}

mpz_nombre::mpz_nombre(unsigned long long op) {
    init();
    mpz_init(_data);
    set(op);
}

mpz_nombre::mpz_nombre(signed long long op) {
    init();
    mpz_init(_data);
    set(op);
}

void mpz_nombre::init() {
    _data = new __mpz_struct();
}

void mpz_nombre::clear() {
    if (_data != nullptr) {
        mpz_clear(_data);
        delete _data;
        _data = nullptr;
    }
}

mpz_nombre &mpz_nombre::operator=(const mpz_nombre &op) {
    if (this != &op) {
        set(op);
    }
    return *this;
}

mpz_nombre &mpz_nombre::operator=(mpz_nombre &&op) noexcept {
    if (this != &op) {
        clear();
        _data = std::exchange(op._data, nullptr);
    }
    return *this;
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
    std::swap(_data, op._data);
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

const mpz_nombre mpz_nombre::operator--(int) {
    mpz_nombre copie(_data);
    mpz_sub_ui(_data, _data, 1);
    return copie;
}

signed short mpz_nombre::signe() const {
    return mpz_sgn(_data);
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

void mpz_nombre::abs(mpz_nombre &rop, const mpz_nombre &op) {
    mpz_abs(rop._data, op._data);
}

void mpz_nombre::racine_carre(mpz_nombre &rop, const mpz_nombre &op) {
    mpz_sqrt(rop._data, op._data);
}

bool mpz_nombre::carre_parfait(const mpz_nombre &op) {
    return mpz_perfect_square_p(op._data) != 0;
}

void mpz_nombre::racine(mpz_nombre &rop, const mpz_nombre &op, unsigned long int n) {
    mpz_root(rop._data, op._data, n);
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

void mpz_nombre::premier_suivant(mpz_nombre &rop, const mpz_nombre &op) {
    mpz_nextprime(rop._data, op._data);
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

bool mpz_nombre::divisible(const mpz_nombre &op1, const mpz_nombre &op2) {
    return mpz_divisible_p(op1._data, op2._data) != 0;
}

bool mpz_nombre::divisible(const mpz_nombre &op1, unsigned long int op2) {
    return mpz_divisible_ui_p(op1._data, op2) != 0;
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

void mpz_nombre::boucle_chiffre(const std::function<void(unsigned long)> &op, unsigned long base) const {
    mpz_nombre n(_data);
    while (n != 0l) {
        unsigned long int r = mpz_fdiv_q_ui(n._data, n._data, base);
        op(r);
    }
}

size_t mpz_nombre::nombre_chiffres(unsigned long base) const {
    size_t d = 0;
    boucle_chiffre([&d](unsigned long int) { ++d; }, base);
    return d;
}

mpz_nombre mpz_nombre::somme_chiffres(unsigned long base) const {
    mpz_nombre resultat = 0;
    boucle_chiffre([&resultat](unsigned long int d) { resultat += d; }, base);
    return resultat;
}

std::deque<unsigned long int> mpz_nombre::extraire_chiffres(unsigned long base) const {
    std::deque<unsigned long int> resultat;
    boucle_chiffre([&resultat](unsigned long int d) { resultat.push_front(d); }, base);
    return resultat;
}

mpz_nombre mpz_nombre::inverser_nombre(unsigned long base) const {
    mpz_nombre resultat = 0;
    boucle_chiffre([&resultat, &base](unsigned long int d) {
        resultat *= base;
        resultat += d;
    }, base);
    return resultat;
}

bool mpz_nombre::palindrome(unsigned long base) const {
    const auto chiffres = extraire_chiffres(base);
    return std::equal(chiffres.begin(), chiffres.begin() + chiffres.size() / 2, chiffres.rbegin());
}

int mpz_nombre::jacobi(const mpz_nombre &a, const mpz_nombre &b) {
    return mpz_jacobi(a._data, b._data);
}

namespace std {
    mpz_nombre abs(const mpz_nombre &op) {
        mpz_nombre rop;
        mpz_nombre::abs(rop, op);
        return rop;
    }

    void swap(mpz_nombre &op1, mpz_nombre &op2) {
        op1.swap(op2);
    }

    mpz_nombre sqrt(const mpz_nombre &op) {
        mpz_nombre rop;
        mpz_nombre::racine_carre(rop, op);
        return rop;
    }

    mpz_nombre cbrt(const mpz_nombre &op) {
        mpz_nombre rop;
        mpz_nombre::racine(rop, op, 3);
        return rop;
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
