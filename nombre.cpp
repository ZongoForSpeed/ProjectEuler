#include "nombre.h"
#include "utilitaires.h"

Nombre::Nombre()
{
    mpz_init (data);
}

Nombre::Nombre(const mpz_t & op)
{
    mpz_init_set (data, op);
}

Nombre::Nombre(const Nombre & op)
{
    mpz_init_set (data, op.data);
}

Nombre::Nombre(unsigned int op)
{
    mpz_init_set_ui(data, op);
}

Nombre::Nombre(signed int op)
{
    mpz_init_set_si(data, op);
}

Nombre::Nombre(unsigned long op)
{
    mpz_init_set_ui(data, op);
}

Nombre::Nombre(signed long op)
{
    mpz_init_set_si(data, op);
}

Nombre::Nombre(double op)
{
    mpz_init_set_d(data, op);
}

Nombre::Nombre(const std::string & op, int base /*= 10*/)
{
    mpz_init_set_str(data, op.c_str(), base);
}

Nombre::Nombre(unsigned long long op)
{
    mpz_init (data);
    set(op);
}

Nombre::Nombre(signed long long op)
{
    mpz_init (data);
    set(op);
}

Nombre::Nombre(long double op) : Nombre(std::to_string(op, 0), 10)
{
}

Nombre::~Nombre()
{
    mpz_clear (data);
}

void Nombre::set(const mpz_t & op)
{
    mpz_set (data, op);
}

void Nombre::set(const Nombre & op)
{
    mpz_set (data, op.data);
}

void Nombre::set(unsigned long op)
{
    mpz_set_ui (data, op);
}

void Nombre::set(signed long op)
{
    mpz_set_si (data, op);
}

void Nombre::set(unsigned int op)
{
    mpz_set_ui (data, op);
}

void Nombre::set(signed int op)
{
    mpz_set_si (data, op);
}

void Nombre::set(double op)
{
    mpz_set_d (data, op);
}

void Nombre::set(const std::string & op, int base /*= 10*/)
{
    mpz_set_str (data, op.c_str(), base);
}

void Nombre::set(long double op)
{
    set(std::to_string(op, 0), 10);
}

namespace std
{
    Nombre abs(const Nombre & op)
    {
        return Nombre::abs(op);
    }
    
    void swap(Nombre & op1, Nombre & op2)
    {
        op1.swap(op2);
    }
    
    Nombre sqrt(const Nombre & op)
    {
        return op.racine_carre();
    }
    
    Nombre cbrt(const Nombre & op)
    {
        return op.racine(3);
    }
    
    std::ostream& operator<<(std::ostream& os, const Nombre & op)
    {
        os << op.get_string();
        return os;
    }
    
    std::istream& operator>>(std::istream& is, Nombre & op)
    {
        std::string str;
        is >> str;
        op.set(str);
        return is;
    }
    
    std::string to_string( const Nombre & n )
    {
        return n.get_string();
    }
}
