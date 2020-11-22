#include "mpq_fraction.h"

mpq_fraction::mpq_fraction() {
    init();
    mpq_init(_data);
}

mpq_fraction::~mpq_fraction() {
    if (_data != nullptr) {
        mpq_clear(_data);
        delete _data;
    }
}

mpq_fraction::mpq_fraction(const mpq_fraction &op) {
    init();
    mpq_set(_data, op._data);
    mpq_canonicalize(_data);
}

mpq_fraction::mpq_fraction(mpq_fraction &&op) : _data(std::exchange(op._data, nullptr)) {
}

mpq_fraction::mpq_fraction(const mpz_nombre &op) {
    init();
    mpq_set_z(_data, op.get_data());
    mpq_canonicalize(_data);
}

mpq_fraction::mpq_fraction(unsigned long op1, unsigned long op2) {
    init();
    mpq_set_ui(_data, op1, op2);
    mpq_canonicalize(_data);
}

mpq_fraction::mpq_fraction(long op1, unsigned long op2) {
    init();
    mpq_set_si(_data, op1, op2);
    mpq_canonicalize(_data);
}

mpq_fraction::mpq_fraction(const std::string &op, int base) {
    init();
    mpq_set_str(_data, op.c_str(), base);
    mpq_canonicalize(_data);
}

mpq_fraction::mpq_fraction(double op) {
    init();
    mpq_set_d(_data, op);
    mpq_canonicalize(_data);
}

void mpq_fraction::init() {
    _data = new __mpq_struct();
}

void mpq_fraction::clear() {
    if (_data != nullptr) {
        mpq_clear(_data);
        delete _data;
        _data = nullptr;
    }
}

void mpq_fraction::swap(mpq_fraction &op) {
    mpq_swap(_data, op._data);
    mpq_canonicalize(_data);
}

double mpq_fraction::get_double() const {
    return mpq_get_d(_data);
}

std::string mpq_fraction::to_string(int base) const {
    char *str = mpq_get_str(nullptr, base, _data);
    std::string resultat(str);
    free(str);
    return resultat;
}

mpq_fraction &mpq_fraction::operator+=(mpq_fraction &op) {
    mpq_add(_data, _data, op._data);
    mpq_canonicalize(_data);
    return *this;
}

mpq_fraction mpq_fraction::operator+(const mpq_fraction &op) const {
    mpq_fraction resultat;
    mpq_add(resultat._data, _data, op._data);
    mpq_canonicalize(resultat._data);
    return resultat;
}

mpq_fraction &mpq_fraction::operator-=(mpq_fraction &op) {
    mpq_sub(_data, _data, op._data);
    mpq_canonicalize(_data);
    return *this;
}

mpq_fraction mpq_fraction::operator-(const mpq_fraction &op) const {
    mpq_fraction resultat;
    mpq_sub(resultat._data, _data, op._data);
    mpq_canonicalize(resultat._data);
    return resultat;
}

mpq_fraction &mpq_fraction::operator*=(mpq_fraction &op) {
    mpq_mul(_data, _data, op._data);
    mpq_canonicalize(_data);
    return *this;
}

mpq_fraction mpq_fraction::operator*(const mpq_fraction &op) const {
    mpq_fraction resultat;
    mpq_mul(resultat._data, _data, op._data);
    mpq_canonicalize(resultat._data);
    return resultat;
}

mpq_fraction &mpq_fraction::operator/=(mpq_fraction &op) {
    mpq_div(_data, _data, op._data);
    mpq_canonicalize(_data);
    return *this;
}

mpq_fraction mpq_fraction::operator/(const mpq_fraction &op) const {
    mpq_fraction resultat;
    mpq_div(resultat._data, _data, op._data);
    mpq_canonicalize(resultat._data);
    return resultat;
}

int mpq_fraction::compare(const mpq_fraction &op) const {
    return mpq_cmp(_data, op._data);
}

int mpq_fraction::compare(const mpz_nombre &op) const {
    return mpq_cmp_z(_data, op.get_data());
}

int mpq_fraction::compare(unsigned long n, unsigned long d) const {
    return mpq_cmp_ui(_data, n, d);
}

int mpq_fraction::compare(long n, unsigned long d) const {
    return mpq_cmp_si (_data, n, d);
}

bool mpq_fraction::egale(const mpq_fraction &op) const {
    return mpq_equal(_data, op._data) != 0;
}

bool mpq_fraction::operator==(const mpq_fraction &op) const {
    return egale(op);
}

bool mpq_fraction::operator==(const mpz_nombre &op) const {
    return compare(op) == 0;
}

bool mpq_fraction::operator<(const mpq_fraction &op) const {
    return compare(op) < 0;
}

bool mpq_fraction::operator<(const mpz_nombre &op) const {
    return compare(op) < 0;
}

bool mpq_fraction::operator<=(const mpq_fraction &op) const {
    return compare(op) <= 0;
}

bool mpq_fraction::operator<=(const mpz_nombre &op) const {
    return compare(op) <= 0;
}

bool mpq_fraction::operator>(const mpq_fraction &op) const {
    return compare(op) > 0;
}

bool mpq_fraction::operator>(const mpz_nombre &op) const {
    return compare(op) > 0;
}

bool mpq_fraction::operator>=(const mpq_fraction &op) const {
    return compare(op) >= 0;
}

bool mpq_fraction::operator>=(const mpz_nombre &op) const {
    return compare(op) >= 0;
}

mpq_ptr mpq_fraction::get_data() {
    return _data;
}

mpq_srcptr mpq_fraction::get_data() const {
    return _data;
}

int mpq_fraction::compare(long op) const {
    return compare(op, 1ul);
}

int mpq_fraction::compare(unsigned long op) const {
    return compare(op, 1ul);
}

mpq_fraction &mpq_fraction::operator=(const mpq_fraction &op) {
    if (this != &op) {
        set(op);
    }
    return *this;
}

mpq_fraction &mpq_fraction::operator=(mpq_fraction &&op) noexcept {
    if (this != &op) {
        clear();
        _data = std::exchange(op._data, nullptr);
    }
    return *this;
}

mpq_fraction std::abs(const mpq_fraction &op) {
    return mpq_fraction::abs(op);
}

void std::swap(mpq_fraction &op1, mpq_fraction &op2) {
    op1.swap(op2);
}

std::ostream &std::operator<<(std::ostream &os, const mpq_fraction &op) {
    os << op.to_string();
    return os;
}

std::istream &std::operator>>(std::istream &is, mpq_fraction &op) {
    std::string str;
    is >> str;
    op.set(str);
    return is;
}
