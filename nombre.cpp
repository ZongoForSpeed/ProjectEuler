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
