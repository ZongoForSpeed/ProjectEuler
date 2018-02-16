//
// Created by zongo on 04/02/18.
//

#include "mp_decimal.h"
#include "mp_decimal.h"

const mp_decimal mp_decimal::PI = mp_decimal::calcul_pi();
const mp_decimal mp_decimal::EULER = mp_decimal::calcul_euler();
const mp_decimal mp_decimal::E = mp_decimal::calcul_e();
const mp_decimal mp_decimal::CATALAN = mp_decimal::calcul_catalan();

mp_decimal::mp_decimal() {
    mpfr_init(_data);
}

mp_decimal::mp_decimal(const mp_decimal &op) {
    mpfr_init_set(_data, op._data, MPFR_RNDN);
}

mp_decimal::mp_decimal(unsigned long int op) {
    mpfr_init_set_ui(_data, op, MPFR_RNDN);
}

mp_decimal::mp_decimal(long int op) {
    mpfr_init_set_si(_data, op, MPFR_RNDN);
}

mp_decimal::mp_decimal(double op) {
    mpfr_init_set_d(_data, op, MPFR_RNDN);
}

mp_decimal::mp_decimal(long double op) {
    mpfr_init_set_ld(_data, op, MPFR_RNDN);
}

mp_decimal::mp_decimal(const mp_nombre &op) {
    mpfr_init_set_z(_data, op.get_data(), MPFR_RNDN);
}

mp_decimal::mp_decimal(const std::string &op, int base /*= 10*/) {
    mpfr_init_set_str(_data, op.c_str(), base, MPFR_RNDN);
}

mp_decimal::~mp_decimal() {
    mpfr_clear(_data);
}

void mp_decimal::set(const mp_decimal &op) {
    mpfr_set(_data, op._data, MPFR_RNDN);
}

void mp_decimal::set(unsigned long int op) {
    mpfr_set_ui(_data, op, MPFR_RNDN);
}

void mp_decimal::set(long int op) {
    mpfr_set_si(_data, op, MPFR_RNDN);
}

void mp_decimal::set(float op) {
    mpfr_set_flt(_data, op, MPFR_RNDN);
}

void mp_decimal::set(double op) {
    mpfr_set_d(_data, op, MPFR_RNDN);
}

void mp_decimal::set(long double op) {
    mpfr_set_ld(_data, op, MPFR_RNDN);
}

void mp_decimal::set(const mp_nombre &op) {
    mpfr_set_z(_data, op.get_data(), MPFR_RNDN);
}

void mp_decimal::set(const std::string &op, int base /*= 10*/) {
    mpfr_set_str(_data, op.c_str(), base, MPFR_RNDN);
}

long int mp_decimal::get_long() const {
    return mpfr_get_si(_data, MPFR_RNDN);
}

unsigned long int mp_decimal::get_unsigned_long() const {
    return mpfr_get_ui(_data, MPFR_RNDN);
}

float mp_decimal::get_float() const {
    return mpfr_get_flt(_data, MPFR_RNDN);
}

double mp_decimal::get_double() const {
    return mpfr_get_d(_data, MPFR_RNDN);
}

long double mp_decimal::get_long_double() const {
    return mpfr_get_ld(_data, MPFR_RNDN);
}

mp_nombre mp_decimal::get_mp_nombre() const {
    mp_nombre rop;
    mpfr_get_z(rop.get_data(), _data, MPFR_RNDN);
    return rop;
}

std::string mp_decimal::to_string(size_t precision /*= 8*/) const {
    std::ostringstream format;
    format << "%." << precision << "Rg";
    char *str = nullptr;
    mpfr_asprintf(&str, format.str().c_str(), _data);
    std::string resultat(str);
    mpfr_free_str(str);
    return resultat;
}

int mp_decimal::compare(unsigned long op) const {
    return mpfr_cmp_ui(_data, op);
}

int mp_decimal::compare(long op) const {
    return mpfr_cmp_si(_data, op);
}

int mp_decimal::compare(double op) const {
    return mpfr_cmp_d(_data, op);
}

int mp_decimal::compare(long double op) const {
    return mpfr_cmp_ld(_data, op);
}

int mp_decimal::compare(const mp_nombre &op) const {
    return mpfr_cmp_z(_data, op.get_data());
}

bool mp_decimal::operator>(const mp_decimal &op) const {
    return mpfr_greater_p(_data, op._data) != 0;
}

bool mp_decimal::operator>=(const mp_decimal &op) const {
    return mpfr_greaterequal_p(_data, op._data) != 0;
}

bool mp_decimal::operator<(const mp_decimal &op) const {
    return mpfr_less_p(_data, op._data) != 0;
}

bool mp_decimal::operator<=(const mp_decimal &op) const {
    return mpfr_lessequal_p(_data, op._data) != 0;
}

bool mp_decimal::operator==(const mp_decimal &op) const {
    return mpfr_equal_p(_data, op._data) != 0;
}

bool mp_decimal::operator!=(const mp_decimal &op) const {
    return mpfr_equal_p(_data, op._data) == 0;
}

mp_decimal &mp_decimal::negation() {
    mpfr_neg(_data, _data, MPFR_RNDN);
    return *this;
}

mp_decimal &mp_decimal::inverse() {
    mpfr_ui_div(_data, 1ul, _data, MPFR_RNDN);
    return *this;
}

void mp_decimal::addition(mp_decimal &rop, const mp_decimal &op1, const mp_decimal &op2) {
    mpfr_add(*rop, *op1, *op2, MPFR_RNDN);
}

void mp_decimal::addition(mp_decimal &rop, const mp_decimal &op1, unsigned long op2) {
    mpfr_add_ui(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::addition(mp_decimal &rop, const mp_decimal &op1, long op2) {
    mpfr_add_si(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::addition(mp_decimal &rop, const mp_decimal &op1, double op2) {
    mpfr_add_d(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::addition(mp_decimal &rop, const mp_decimal &op1, const mp_nombre &op2) {
    mpfr_add_z(*rop, *op1, op2.get_data(), MPFR_RNDN);
}

void mp_decimal::soustraction(mp_decimal &rop, const mp_decimal &op1, const mp_decimal &op2) {
    mpfr_sub(*rop, *op1, *op2, MPFR_RNDN);
}

void mp_decimal::soustraction(mp_decimal &rop, unsigned long int op1, const mp_decimal &op2) {
    mpfr_ui_sub(*rop, op1, *op2, MPFR_RNDN);
}

void mp_decimal::soustraction(mp_decimal &rop, const mp_decimal &op1, unsigned long int op2) {
    mpfr_sub_ui(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::soustraction(mp_decimal &rop, long int op1, const mp_decimal &op2) {
    mpfr_si_sub(*rop, op1, *op2, MPFR_RNDN);
}

void mp_decimal::soustraction(mp_decimal &rop, const mp_decimal &op1, long int op2) {
    mpfr_sub_si(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::soustraction(mp_decimal &rop, double op1, const mp_decimal &op2) {
    mpfr_d_sub(*rop, op1, *op2, MPFR_RNDN);
}

void mp_decimal::soustraction(mp_decimal &rop, const mp_decimal &op1, double op2) {
    mpfr_sub_d(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::soustraction(mp_decimal &rop, const mp_nombre &op1, const mp_decimal &op2) {
    mpfr_z_sub(*rop, op1.get_data(), *op2, MPFR_RNDN);
}

void mp_decimal::soustraction(mp_decimal &rop, const mp_decimal &op1, const mp_nombre &op2) {
    mpfr_sub_z(*rop, *op1, op2.get_data(), MPFR_RNDN);
}

void mp_decimal::multiplication(mp_decimal &rop, const mp_decimal &op1, const mp_decimal &op2) {
    mpfr_mul(*rop, *op1, *op2, MPFR_RNDN);
}

void mp_decimal::multiplication(mp_decimal &rop, const mp_decimal &op1, unsigned long op2) {
    mpfr_mul_ui(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::multiplication(mp_decimal &rop, const mp_decimal &op1, long op2) {
    mpfr_mul_si(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::multiplication(mp_decimal &rop, const mp_decimal &op1, double op2) {
    mpfr_mul_d(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::multiplication(mp_decimal &rop, const mp_decimal &op1, const mp_nombre &op2) {
    mpfr_mul_z(*rop, *op1, op2.get_data(), MPFR_RNDN);
}

void mp_decimal::division(mp_decimal &rop, const mp_decimal &op1, const mp_decimal &op2) {
    mpfr_div(*rop, *op1, *op2, MPFR_RNDN);
}

void mp_decimal::division(mp_decimal &rop, unsigned long int op1, const mp_decimal &op2) {
    mpfr_ui_div(*rop, op1, *op2, MPFR_RNDN);
}

void mp_decimal::division(mp_decimal &rop, const mp_decimal &op1, unsigned long int op2) {
    mpfr_div_ui(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::division(mp_decimal &rop, long int op1, const mp_decimal &op2) {
    mpfr_si_div(*rop, op1, *op2, MPFR_RNDN);
}

void mp_decimal::division(mp_decimal &rop, const mp_decimal &op1, long int op2) {
    mpfr_div_si(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::division(mp_decimal &rop, double op1, const mp_decimal &op2) {
    mpfr_d_div(*rop, op1, *op2, MPFR_RNDN);
}

void mp_decimal::division(mp_decimal &rop, const mp_decimal &op1, double op2) {
    mpfr_div_d(*rop, *op1, op2, MPFR_RNDN);
}

void mp_decimal::division(mp_decimal &rop, const mp_decimal &op1, const mp_nombre &op2) {
    mpfr_div_z(*rop, *op1, op2.get_data(), MPFR_RNDN);
}

mp_decimal mp_decimal::calcul_pi() {
    mp_decimal resultat;
    mpfr_const_pi(*resultat, MPFR_RNDN);
    return resultat;
}

mp_decimal mp_decimal::calcul_euler() {
    mp_decimal resultat;
    mpfr_const_euler(*resultat, MPFR_RNDN);
    return resultat;
}

mp_decimal mp_decimal::calcul_e() {
    mp_decimal resultat(1l);
    mpfr_exp(*resultat, *resultat, MPFR_RNDN);
    return resultat;
}

mp_decimal mp_decimal::calcul_catalan() {
    mp_decimal resultat;
    mpfr_const_catalan(*resultat, MPFR_RNDN);
    return resultat;
}

void mp_decimal::negation(mp_decimal &rop, const mp_decimal &op) {
    mpfr_neg(*rop, *op, MPFR_RNDN);
}

void mp_decimal::inverse(mp_decimal &rop, const mp_decimal &op) {
    mpfr_ui_div(*rop, 1ul, *op, MPFR_RNDN);
}

namespace std {
    mp_decimal abs(const mp_decimal &op) {
        return mp_decimal::abs(op);
    }

    void swap(mp_decimal &op1, mp_decimal &op2) {
        op1.swap(op2);
    }

    mp_decimal sqrt(const mp_decimal &op) {
        return mp_decimal::racine_carre(op);
    }

    mp_decimal cbrt(const mp_decimal &op) {
        return mp_decimal::racine_cubique(op);
    }

    std::ostream &operator<<(std::ostream &os, const mp_decimal &op) {
        os << op.to_string();
        return os;
    }

    std::istream &operator>>(std::istream &is, mp_decimal &op) {
        std::string str;
        is >> str;
        op.set(str);
        return is;
    }

    mp_decimal log(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_log(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal log2(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_log2(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal log10(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_log10(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal log1p(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_log1p(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal exp(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_exp(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal exp2(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_exp2(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal expm1(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_expm1(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal sin(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_sin(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal cos(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_cos(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal tan(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_tan(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal asin(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_asin(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal acos(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_acos(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal atan(const mp_decimal &op) {
        mp_decimal resultat;
        mpfr_atan(*resultat, *op, MPFR_RNDN);
        return resultat;
    }

    mp_decimal atan2(const mp_decimal &op1, const mp_decimal &op2) {
        mp_decimal resultat;
        mpfr_atan2(*resultat, *op1, *op2, MPFR_RNDN);
        return resultat;
    }
}
