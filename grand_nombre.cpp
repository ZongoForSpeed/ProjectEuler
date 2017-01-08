#include "grand_nombre.h"
#include "utilitaires.h"

grand_nombre::grand_nombre()
{
    mpz_init (data);
}

grand_nombre::grand_nombre(const mpz_t & op)
{
    mpz_init_set (data, op);
}

grand_nombre::grand_nombre(const grand_nombre & op)
{
    mpz_init_set (data, op.data);
}

grand_nombre::grand_nombre(unsigned int op)
{
    mpz_init_set_ui(data, op);
}

grand_nombre::grand_nombre(signed int op)
{
    mpz_init_set_si(data, op);
}

grand_nombre::grand_nombre(unsigned long op)
{
    mpz_init_set_ui(data, op);
}

grand_nombre::grand_nombre(signed long op)
{
    mpz_init_set_si(data, op);
}

grand_nombre::grand_nombre(double op)
{
    mpz_init_set_d(data, op);
}

grand_nombre::grand_nombre(const std::string & op, int base /*= 10*/)
{
    mpz_init_set_str(data, op.c_str(), base);
}

grand_nombre::grand_nombre(unsigned long long op)
{
    mpz_init (data);
    set(op);
}

grand_nombre::grand_nombre(signed long long op)
{
    mpz_init (data);
    set(op);
}

grand_nombre::grand_nombre(long double op) : grand_nombre(std::to_string(op, 0), 10)
{
}

grand_nombre::~grand_nombre()
{
    mpz_clear (data);
}

void grand_nombre::set(const mpz_t & op)
{
    mpz_set (data, op);
}

void grand_nombre::set(const grand_nombre & op)
{
    mpz_set (data, op.data);
}

void grand_nombre::set(unsigned long op)
{
    mpz_set_ui (data, op);
}

void grand_nombre::set(signed long op)
{
    mpz_set_si (data, op);
}

void grand_nombre::set(unsigned int op)
{
    mpz_set_ui (data, op);
}

void grand_nombre::set(signed int op)
{
    mpz_set_si (data, op);
}

void grand_nombre::set(double op)
{
    mpz_set_d (data, op);
}

void grand_nombre::set(const std::string & op, int base /*= 10*/)
{
    mpz_set_str (data, op.c_str(), base);
}

void grand_nombre::set(long double op)
{
    set(std::to_string(op, 0), 10);
}

unsigned long grand_nombre::get_unsigned_long() const
{
    return mpz_get_ui(data);
}

signed long grand_nombre::get_signed_long() const
{
    return mpz_get_si(data);
}

double grand_nombre::get_double() const
{
    return mpz_get_d(data);
}

unsigned long long grand_nombre::get_unsigned_long_long() const
{
    unsigned long long result = 0;
    mpz_export(&result, 0, -1, sizeof result, 0, 0, data);
    return result;
}

signed short grand_nombre::signe() const
{
    return mpz_sgn (data);
}

int grand_nombre::compare(const grand_nombre & op) const
{
    return mpz_cmp(data, op.data);
}

int grand_nombre::compare(double op) const
{
    return mpz_cmp_d(data, op);
}

int grand_nombre::compare(signed long int op) const
{
    return mpz_cmp_si(data, op);
}

int grand_nombre::compare(unsigned long int op) const
{
    return mpz_cmp_ui(data, op);
}

void grand_nombre::swap(grand_nombre & op)
{
    mpz_swap(data, op.data);
}

const std::string grand_nombre::to_string(int base /*= 10*/) const
{
    // std::string resultat (mpz_sizeinbase(data, base) + 2, 0);
    // mpz_get_str(&resultat[0], base, data);
    // resultat.shrink_to_fit();
    char * str = mpz_get_str(NULL, base, data);
    std::string resultat(str);
    free(str);
    return resultat;
}

grand_nombre & grand_nombre::addition(const grand_nombre & op)
{
    mpz_add(data, data, op.data);
    return *this;
}

grand_nombre & grand_nombre::addition(unsigned long int op)
{
    mpz_add_ui(data, data, op);
    return *this;
}

grand_nombre & grand_nombre::soustraction(const grand_nombre & op)
{
    mpz_sub(data, data, op.data);
    return *this;
}

grand_nombre & grand_nombre::soustraction(unsigned long int op)
{
    mpz_sub_ui(data, data, op);
    return *this;
}

grand_nombre & grand_nombre::multiplication(const grand_nombre & op)
{
    mpz_mul(data, data, op.data);
    return *this;
}

grand_nombre & grand_nombre::multiplication(unsigned long int op)
{
    mpz_mul_ui(data, data, op);
    return *this;
}

grand_nombre & grand_nombre::multiplication(signed long int op)
{
    mpz_mul_si(data, data, op);
    return *this;
}

grand_nombre & grand_nombre::division(const grand_nombre & op)
{
    mpz_fdiv_q (data, data, op.data);
    return *this;
}

grand_nombre & grand_nombre::division(unsigned long int op)
{
    mpz_fdiv_q_ui (data, data, op);
    return *this;
}

grand_nombre & grand_nombre::modulo(const grand_nombre & op)
{
    mpz_mod (data, data, op.data);
    return *this;
}

grand_nombre & grand_nombre::modulo(unsigned long int op)
{
    mpz_mod_ui (data, data, op);
    return *this;
}

bool grand_nombre::divisible(const grand_nombre & op) const
{
    return mpz_divisible_p(data, op.data) != 0;
}

bool grand_nombre::divisible(unsigned long int op) const
{
    return mpz_divisible_ui_p(data, op) != 0;
}

grand_nombre grand_nombre::coefficient_binomial(const grand_nombre & n, unsigned long int k)
{
    grand_nombre resultat;
    mpz_bin_ui (resultat.data, n.data, k);
    return resultat;
}

grand_nombre grand_nombre::coefficient_binomial(unsigned long int n, unsigned long int k)
{
    grand_nombre resultat;
    mpz_bin_uiui (resultat.data, n, k);
    return resultat;
}

grand_nombre grand_nombre::factorielle(unsigned long int n)
{
    grand_nombre resultat;
    mpz_fac_ui (resultat.data, n);
    return resultat;
}

grand_nombre grand_nombre::catalan(unsigned long int n)
{
    return coefficient_binomial(2*n, n) / (n + 1);
}

void grand_nombre::boucle_chiffre(std::function<void(unsigned long int)> op, unsigned long int base /*= 10*/) const
{
    grand_nombre n(data);

    while (n != 0)
    {
        unsigned long int r = mpz_fdiv_q_ui (n.data, n.data, base);
        op(r);
    }
}

size_t grand_nombre::nombre_chiffres(unsigned long int base /*= 10*/) const
{
    size_t d = 0;
    boucle_chiffre([&d](unsigned long int) { ++d; }, base);
    return d;
}

grand_nombre grand_nombre::somme_chiffres(unsigned long int base /*= 10*/) const
{
    grand_nombre resultat = 0;
    boucle_chiffre([&resultat] (unsigned long int d){ resultat += d; }, base);
    return resultat;
}

std::deque<unsigned long int> grand_nombre::extraire_chiffres(unsigned long int base /*= 10*/) const
{
    std::deque<unsigned long int> resultat;
    boucle_chiffre([&resultat] (unsigned long int d){ resultat.push_front(d); }, base);
    return resultat;
}

grand_nombre grand_nombre::inverser_nombre(unsigned long int base /*= 10*/) const
{
    grand_nombre resultat = 0;
    boucle_chiffre([&resultat, &base] (unsigned long int d) {
        resultat *= base;
        resultat += d;
    }, base);
    return resultat;
}

bool grand_nombre::palindrome(unsigned long int base /*= 10*/) const
{
    const auto chiffres = extraire_chiffres(base);
    return std::equal(chiffres.begin(), chiffres.begin() + chiffres.size()/2, chiffres.rbegin());
}

namespace std
{
    grand_nombre abs(const grand_nombre & op)
    {
        return grand_nombre::abs(op);
    }
    
    void swap(grand_nombre & op1, grand_nombre & op2)
    {
        op1.swap(op2);
    }
    
    grand_nombre sqrt(const grand_nombre & op)
    {
        return op.racine_carre();
    }
    
    grand_nombre cbrt(const grand_nombre & op)
    {
        return op.racine(3);
    }
    
    std::ostream& operator<<(std::ostream& os, const grand_nombre & op)
    {
        os << op.to_string();
        return os;
    }
    
    std::istream& operator>>(std::istream& is, grand_nombre & op)
    {
        std::string str;
        is >> str;
        op.set(str);
        return is;
    }
}
