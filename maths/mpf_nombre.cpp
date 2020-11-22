#include "mpf_nombre.h"

long mpf_nombre::DEFAULT_PRECISION = 128;
mpfr_rnd_t mpf_nombre::DEFAULT_ROUNDING = MPFR_RNDN;
mpf_nombre mpf_nombre::PI = calcul_pi();
mpf_nombre mpf_nombre::E = calcul_e();
mpf_nombre mpf_nombre::PHI = calcul_phi();

void mpf_nombre::setPrecision(long precision) {
    mpfr_set_default_prec(precision);
    DEFAULT_PRECISION = precision;
}

void mpf_nombre::setRounding(mpfr_rnd_t rounding) {
    mpfr_set_default_rounding_mode(rounding);
    DEFAULT_ROUNDING = rounding;
}

mpf_nombre::mpf_nombre() {
    init();
    mpfr_init2(_data, DEFAULT_PRECISION);
    mpfr_set_zero(_data, +1);
}

mpf_nombre::mpf_nombre(const mpf_nombre &op) {
    init();
    mpfr_init_set(_data, op._data, DEFAULT_ROUNDING);
}

mpf_nombre::mpf_nombre(unsigned long op) {
    init();
    mpfr_init_set_ui(_data, op, DEFAULT_ROUNDING);
}

mpf_nombre::mpf_nombre(long op) {
    init();
    mpfr_init_set_si(_data, op, DEFAULT_ROUNDING);
}

mpf_nombre::mpf_nombre(double op) {
    init();
    mpfr_init_set_d(_data, op, DEFAULT_ROUNDING);
}

mpf_nombre::mpf_nombre(long double op) {
    init();
    mpfr_init_set_ld(_data, op, DEFAULT_ROUNDING);
}

mpf_nombre::mpf_nombre(const mpz_nombre &op) {
    init();
    mpfr_init_set_z(_data, op.get_data(), DEFAULT_ROUNDING);
}

mpf_nombre::mpf_nombre(const mpq_fraction &op) {
    init();
    mpfr_init_set_q(_data, op.get_data(), DEFAULT_ROUNDING);
}

mpf_nombre::mpf_nombre(const std::string &op, int base) {
    init();
    mpfr_init_set_str(_data, op.c_str(), base, DEFAULT_ROUNDING);
}

void mpf_nombre::init() { _data = new __mpfr_struct(); }

void mpf_nombre::clear() {
    if (_data != nullptr) {
        mpfr_clear(_data);
        delete _data;
    }
}

mpf_nombre::~mpf_nombre() {
    clear();
}

void mpf_nombre::set(const mpf_nombre &op) {
    mpfr_set(_data, op._data, DEFAULT_ROUNDING);
}

void mpf_nombre::set(unsigned long op) {
    mpfr_set_ui(_data, op, DEFAULT_ROUNDING);
}

void mpf_nombre::set(long op) {
    mpfr_set_si(_data, op, DEFAULT_ROUNDING);
}

void mpf_nombre::set(float op) {
    mpfr_set_flt(_data, op, DEFAULT_ROUNDING);
}

void mpf_nombre::set(double op) {
    mpfr_set_d(_data, op, DEFAULT_ROUNDING);
}

void mpf_nombre::set(long double op) {
    mpfr_set_ld(_data, op, DEFAULT_ROUNDING);
}

void mpf_nombre::set(const mpz_nombre &op) {
    mpfr_set_z(_data, op.get_data(), DEFAULT_ROUNDING);
}

void mpf_nombre::set(const mpq_fraction &op) {
    mpfr_set_q(_data, op.get_data(), DEFAULT_ROUNDING);
}

void mpf_nombre::set(const std::string &op, int base) {
    mpfr_set_str(_data, op.c_str(), base, DEFAULT_ROUNDING);
}

void mpf_nombre::swap(mpf_nombre &op) {
    mpfr_swap(_data, op._data);
}

mpfr_ptr mpf_nombre::get_data() {
    return _data;
}

mpfr_srcptr mpf_nombre::get_data() const {
    return _data;
}

float mpf_nombre::get_float() const {
    return mpfr_get_flt(_data, DEFAULT_ROUNDING);
}

double mpf_nombre::get_double() const {
    return mpfr_get_d(_data, DEFAULT_ROUNDING);
}

long double mpf_nombre::get_long_double() const {
    return mpfr_get_ld(_data, DEFAULT_ROUNDING);
}

long mpf_nombre::get_signed_long() const {
    return mpfr_get_si(_data, DEFAULT_ROUNDING);
}

unsigned long mpf_nombre::get_unsigned_long() const {
    return mpfr_get_ui(_data, DEFAULT_ROUNDING);
}

mpz_nombre mpf_nombre::get_mpz_nombre() {
    mpz_nombre resultat;
    mpfr_get_z(resultat.get_data(), _data, DEFAULT_ROUNDING);
    return resultat;
}

mpq_fraction mpf_nombre::get_mpq_fraction() {
    mpq_fraction resultat;
    mpfr_get_q(resultat.get_data(), _data);
    return resultat;
}

std::string mpf_nombre::to_string(size_t precision) const {
    std::ostringstream format;
    format << "%." << precision << "R*g";
    char buffer[1024];
    mpfr_sprintf(buffer, format.str().c_str(), DEFAULT_ROUNDING, _data);
    std::string resultat(buffer);
    return resultat;
}

mpf_nombre &mpf_nombre::operator+=(const mpf_nombre &op) {
    mpfr_add(_data, _data, op._data, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator+=(unsigned long op) {
    mpfr_add_ui(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator+=(long op) {
    mpfr_add_si(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator+=(double op) {
    mpfr_add_d(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator+=(const mpq_fraction &op) {
    mpfr_add_q(_data, _data, op.get_data(), DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator+=(const mpz_nombre &op) {
    mpfr_add_z(_data, _data, op.get_data(), DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator-=(const mpf_nombre &op) {
    mpfr_sub(_data, _data, op._data, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator-=(unsigned long op) {
    mpfr_sub_ui(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator-=(long op) {
    mpfr_sub_si(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator-=(double op) {
    mpfr_sub_d(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator-=(const mpq_fraction &op) {
    mpfr_sub_q(_data, _data, op.get_data(), DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator-=(const mpz_nombre &op) {
    mpfr_sub_z(_data, _data, op.get_data(), DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator*=(const mpf_nombre &op) {
    mpfr_mul(_data, _data, op._data, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator*=(unsigned long op) {
    mpfr_mul_ui(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator*=(long op) {
    mpfr_mul_si(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator*=(double op) {
    mpfr_mul_d(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator*=(const mpq_fraction &op) {
    mpfr_mul_q(_data, _data, op.get_data(), DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator*=(const mpz_nombre &op) {
    mpfr_mul_z(_data, _data, op.get_data(), DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator/=(const mpf_nombre &op) {
    mpfr_div(_data, _data, op._data, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator/=(unsigned long op) {
    mpfr_div_ui(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator/=(long op) {
    mpfr_div_si(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator/=(double op) {
    mpfr_div_d(_data, _data, op, DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator/=(const mpq_fraction &op) {
    mpfr_div_q(_data, _data, op.get_data(), DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre &mpf_nombre::operator/=(const mpz_nombre &op) {
    mpfr_div_z(_data, _data, op.get_data(), DEFAULT_ROUNDING);
    return *this;
}

mpf_nombre mpf_nombre::operator-() const {
    mpf_nombre resultat;
    mpfr_neg(resultat._data, _data, DEFAULT_ROUNDING);
    return resultat;
}

const mpf_nombre &mpf_nombre::pi() {
    return PI;
}

const mpf_nombre &mpf_nombre::e() {
    return E;
}

mpf_nombre mpf_nombre::calcul_pi() {
    mpf_nombre pi;
    mpfr_const_pi(pi._data, DEFAULT_ROUNDING);
    return pi;
}

mpf_nombre mpf_nombre::calcul_e() {
    mpf_nombre e(1l);
    mpfr_exp(e._data, e._data, DEFAULT_ROUNDING);
    return e;
}

mpf_nombre mpf_nombre::calcul_phi() {
    mpf_nombre phi;
    mpfr_sqrt_ui(phi._data, 5, DEFAULT_ROUNDING);
    mpfr_add_ui(phi._data, phi._data, 1, DEFAULT_ROUNDING);
    mpfr_div_ui(phi._data, phi._data, 2, DEFAULT_ROUNDING);
    return phi;
}

mpf_nombre &mpf_nombre::operator=(const mpf_nombre &op) {
    if (this != &op) {
        set(op);
    }
    return *this;
}

mpf_nombre &mpf_nombre::operator=(mpf_nombre &&op) noexcept {
    if (this != &op) {
        _data = std::exchange(op._data, nullptr);
    }
    return *this;
}

mpf_nombre mpf_nombre::operator+(const mpf_nombre &op) const {
    mpf_nombre rop;
    mpfr_add(rop._data, _data, op._data, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator+(unsigned long op) const {
    mpf_nombre rop;
    mpfr_add_ui(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator+(long op) const {
    mpf_nombre rop;
    mpfr_add_si(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator+(double op) const {
    mpf_nombre rop;
    mpfr_add_d(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator+(const mpq_fraction &op) const {
    mpf_nombre rop;
    mpfr_add_q(rop._data, _data, op.get_data(), DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator+(const mpz_nombre &op) const {
    mpf_nombre rop;
    mpfr_add_z(rop._data, _data, op.get_data(), DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator-(const mpf_nombre &op) const {
    mpf_nombre rop;
    mpfr_sub(rop._data, _data, op._data, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator-(unsigned long op) const {
    mpf_nombre rop;
    mpfr_sub_ui(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator-(long op) const {
    mpf_nombre rop;
    mpfr_sub_si(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator-(double op) const {
    mpf_nombre rop;
    mpfr_sub_d(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator-(const mpq_fraction &op) const {
    mpf_nombre rop;
    mpfr_sub_q(rop._data, _data, op.get_data(), DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator-(const mpz_nombre &op) const {
    mpf_nombre rop;
    mpfr_sub_z(rop._data, _data, op.get_data(), DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator*(const mpf_nombre &op) const {
    mpf_nombre rop;
    mpfr_mul(rop._data, _data, op._data, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator*(unsigned long op) const {
    mpf_nombre rop;
    mpfr_mul_ui(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator*(long op) const {
    mpf_nombre rop;
    mpfr_mul_si(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator*(double op) const {
    mpf_nombre rop;
    mpfr_mul_d(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator*(const mpq_fraction &op) const {
    mpf_nombre rop;
    mpfr_mul_q(rop._data, _data, op.get_data(), DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator*(const mpz_nombre &op) const {
    mpf_nombre rop;
    mpfr_mul_z(rop._data, _data, op.get_data(), DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator/(const mpf_nombre &op) const {
    mpf_nombre rop;
    mpfr_div(rop._data, _data, op._data, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator/(unsigned long op) const {
    mpf_nombre rop;
    mpfr_div_ui(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator/(long op) const {
    mpf_nombre rop;
    mpfr_div_si(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator/(double op) const {
    mpf_nombre rop;
    mpfr_div_d(rop._data, _data, op, DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator/(const mpq_fraction &op) const {
    mpf_nombre rop;
    mpfr_div_q(rop._data, _data, op.get_data(), DEFAULT_ROUNDING);
    return rop;
}

mpf_nombre mpf_nombre::operator/(const mpz_nombre &op) const {
    mpf_nombre rop;
    mpfr_div_z(rop._data, _data, op.get_data(), DEFAULT_ROUNDING);
    return rop;
}

int mpf_nombre::compare(const mpf_nombre &op) const {
    return mpfr_cmp(_data, op._data);
}

int mpf_nombre::compare(unsigned long op) const {
    return mpfr_cmp_ui(_data, op);
}

int mpf_nombre::compare(long op) const {
    return mpfr_cmp_si(_data, op);
}

int mpf_nombre::compare(double op) const {
    return mpfr_cmp_d(_data, op);
}

int mpf_nombre::compare(long double op) const {
    return mpfr_cmp_ld(_data, op);
}

int mpf_nombre::compare(const mpz_nombre &op) const {
    return mpfr_cmp_z(_data, op.get_data());
}

int mpf_nombre::compare(const mpq_fraction &op) const {
    return mpfr_cmp_q(_data, op.get_data());
}

bool mpf_nombre::operator>(const mpf_nombre &op) const {
    return mpfr_greater_p(_data, op._data) != 0;
}

bool mpf_nombre::operator>=(const mpf_nombre &op) const {
    return mpfr_greaterequal_p(_data, op._data) != 0;
}

bool mpf_nombre::operator<(const mpf_nombre &op) const {
    return mpfr_less_p(_data, op._data) != 0;
}

bool mpf_nombre::operator<=(const mpf_nombre &op) const {
    return mpfr_lessequal_p(_data, op._data) != 0;
}

bool mpf_nombre::operator==(const mpf_nombre &op) const {
    return mpfr_equal_p(_data, op._data) != 0;
}

bool mpf_nombre::operator!=(const mpf_nombre &op) const {
    return mpfr_lessgreater_p(_data, op._data) != 0;
}

const mpf_nombre &mpf_nombre::phi() {
    return PHI;
}

void std::swap(mpf_nombre &op1, mpf_nombre &op2) {
    op1.swap(op2);
}

mpf_nombre std::abs(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::abs(rop, op);
    return rop;
}

std::ostream &std::operator<<(std::ostream &os, const mpf_nombre &op) {
    os << op.to_string();
    return os;
}

std::istream &std::operator>>(std::istream &is, mpf_nombre &op) {
    std::string str;
    is >> str;
    op.set(str);
    return is;
}

mpf_nombre std::sqrt(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::racine_carre(rop, op);
    return rop;
}

mpf_nombre std::cbrt(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::racine_cubique(rop, op);
    return rop;

}

mpf_nombre std::hypot(const mpf_nombre &x, const mpf_nombre &y) {
    mpf_nombre rop;
    mpf_nombre::hypothenuse(rop, x, y);
    return rop;
}


mpf_nombre std::log(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::log(rop, op);
    return rop;
}

mpf_nombre std::log2(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::log2(rop, op);
    return rop;
}

mpf_nombre std::log10(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::log10(rop, op);
    return rop;
}

mpf_nombre std::exp(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::exp(rop, op);
    return rop;
}

mpf_nombre std::exp2(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::exp2(rop, op);
    return rop;
}

mpf_nombre std::exp10(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::exp10(rop, op);
    return rop;
}

mpf_nombre std::expm1(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::expm1(rop, op);
    return rop;

}

mpf_nombre std::pow(const mpf_nombre &op1, const mpf_nombre &op2) {
    mpf_nombre rop;
    mpf_nombre::puissance(rop, op1, op2);
    return rop;
}

mpf_nombre std::pow(const mpf_nombre &op1, unsigned long op2) {
    mpf_nombre rop;
    mpf_nombre::puissance(rop, op1, op2);
    return rop;
}

mpf_nombre std::pow(const mpf_nombre &op1, signed long op2) {
    mpf_nombre rop;
    mpf_nombre::puissance(rop, op1, op2);
    return rop;
}

mpf_nombre std::pow(const mpf_nombre &op1, const mpz_nombre &op2) {
    mpf_nombre rop;
    mpf_nombre::puissance(rop, op1, op2);
    return rop;
}

mpf_nombre std::pow(unsigned long op1, const mpf_nombre &op2) {
    mpf_nombre rop;
    mpf_nombre::puissance(rop, op1, op2);
    return rop;
}

mpf_nombre std::sin(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::sin(rop, op);
    return rop;
}

mpf_nombre std::cos(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::cos(rop, op);
    return rop;
}

mpf_nombre std::tan(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::tan(rop, op);
    return rop;
}

mpf_nombre std::asin(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::arcsin(rop, op);
    return rop;
}

mpf_nombre std::acos(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::arccos(rop, op);
    return rop;
}

mpf_nombre std::atan(const mpf_nombre &op) {
    mpf_nombre rop;
    mpf_nombre::arctan(rop, op);
    return rop;
}

mpf_nombre std::atan2(const mpf_nombre &x, const mpf_nombre &y) {
    mpf_nombre rop;
    mpf_nombre::arctan2(rop, x, y);
    return rop;
}
