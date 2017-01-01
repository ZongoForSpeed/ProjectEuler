#include "nombre.h"
#include "utilitaires.h"

nombre::nombre()
{
    mpz_init (data);
}

nombre::nombre(const mpz_t & op)
{
    mpz_init_set (data, op);
}

nombre::nombre(const nombre & op)
{
    mpz_init_set (data, op.data);
}

nombre::nombre(unsigned int op)
{
    mpz_init_set_ui(data, op);
}

nombre::nombre(signed int op)
{
    mpz_init_set_si(data, op);
}

nombre::nombre(unsigned long op)
{
    mpz_init_set_ui(data, op);
}

nombre::nombre(signed long op)
{
    mpz_init_set_si(data, op);
}

nombre::nombre(double op)
{
    mpz_init_set_d(data, op);
}

nombre::nombre(const std::string & op, int base /*= 10*/)
{
    mpz_init_set_str(data, op.c_str(), base);
}

nombre::nombre(unsigned long long op)
{
    mpz_init (data);
    set(op);
}

nombre::nombre(signed long long op)
{
    mpz_init (data);
    set(op);
}

nombre::nombre(long double op) : nombre(std::to_string(op, 0), 10)
{
}

nombre::~nombre()
{
    mpz_clear (data);
}

void nombre::set(const mpz_t & op)
{
    mpz_set (data, op);
}

void nombre::set(const nombre & op)
{
    mpz_set (data, op.data);
}

void nombre::set(unsigned long op)
{
    mpz_set_ui (data, op);
}

void nombre::set(signed long op)
{
    mpz_set_si (data, op);
}

void nombre::set(unsigned int op)
{
    mpz_set_ui (data, op);
}

void nombre::set(signed int op)
{
    mpz_set_si (data, op);
}

void nombre::set(double op)
{
    mpz_set_d (data, op);
}

void nombre::set(const std::string & op, int base /*= 10*/)
{
    mpz_set_str (data, op.c_str(), base);
}

void nombre::set(long double op)
{
    set(std::to_string(op, 0), 10);
}

unsigned long nombre::get_unsigned_long() const
{
    return mpz_get_ui(data);
}

signed long nombre::get_signed_long() const
{
    return mpz_get_si(data);
}

double nombre::get_double() const
{
    return mpz_get_d(data);
}

unsigned long long nombre::get_unsigned_long_long() const
{
    unsigned long long result = 0;
    mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
    return result;
}

signed short nombre::signe() const
{
    return mpz_sgn (data);
}

int nombre::compare(const nombre & op) const
{
    return mpz_cmp(data, op.data);
}

int nombre::compare(double op) const
{
    return mpz_cmp_d(data, op);
}

int nombre::compare(signed long int op) const
{
    return mpz_cmp_si(data, op);
}

int nombre::compare(unsigned long int op) const
{
    return mpz_cmp_ui(data, op);
}

void nombre::swap(nombre & op)
{
    mpz_swap(data, op.data);
}

const std::string nombre::to_string(int base /*= 10*/) const
{
    // std::string resultat (mpz_sizeinbase(data, base) + 2, 0);
    // mpz_get_str(&resultat[0], base, data);
    // resultat.shrink_to_fit();
    char * str = mpz_get_str(NULL, base, data);
    std::string resultat(str);
    free(str);
    return resultat;
}

nombre & nombre::addition(const nombre & op)
{
    mpz_add(data, data, op.data);
    return *this;
}

nombre & nombre::addition(unsigned long int op)
{
    mpz_add_ui(data, data, op);
    return *this;
}

nombre & nombre::soustraction(const nombre & op)
{
    mpz_sub(data, data, op.data);
    return *this;
}

nombre & nombre::soustraction(unsigned long int op)
{
    mpz_sub_ui(data, data, op);
    return *this;
}

nombre & nombre::multiplication(const nombre & op)
{
    mpz_mul(data, data, op.data);
    return *this;
}

nombre & nombre::multiplication(unsigned long int op)
{
    mpz_mul_ui(data, data, op);
    return *this;
}

nombre & nombre::multiplication(signed long int op)
{
    mpz_mul_si(data, data, op);
    return *this;
}

nombre & nombre::division(const nombre & op)
{
    mpz_fdiv_q (data, data, op.data);
    return *this;
}

nombre & nombre::division(unsigned long int op)
{
    mpz_fdiv_q_ui (data, data, op);
    return *this;
}

nombre & nombre::modulo(const nombre & op)
{
    mpz_mod (data, data, op.data);
    return *this;
}

nombre & nombre::modulo(unsigned long int op)
{
    mpz_mod_ui (data, data, op);
    return *this;
}

bool nombre::divisible(const nombre & op) const
{
    return mpz_divisible_p(data, op.data) != 0;
}

bool nombre::divisible(unsigned long int op) const
{
    return mpz_divisible_ui_p(data, op) != 0;
}

namespace std
{
    nombre abs(const nombre & op)
    {
        return nombre::abs(op);
    }
    
    void swap(nombre & op1, nombre & op2)
    {
        op1.swap(op2);
    }
    
    nombre sqrt(const nombre & op)
    {
        return op.racine_carre();
    }
    
    nombre cbrt(const nombre & op)
    {
        return op.racine(3);
    }
    
    std::ostream& operator<<(std::ostream& os, const nombre & op)
    {
        os << op.to_string();
        return os;
    }
    
    std::istream& operator>>(std::istream& is, nombre & op)
    {
        std::string str;
        is >> str;
        op.set(str);
        return is;
    }
}
