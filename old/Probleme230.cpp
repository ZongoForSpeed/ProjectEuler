#include <iostream>
#include <cstdlib>
#include <limits>
#include <set>
#include <map>
#include <string>
#include <vector>

#include "Timer.h"

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

typedef unsigned long long nombre;
typedef std::pair<nombre, nombre> paire;
typedef std::map<nombre, nombre> dictionnaire;
typedef std::set<nombre> ensemble; 

typedef std::vector<nombre> vecteur;

class Probleme230
{
    // For any two strings of digits, A and B, we define FA,B to be the sequence (A,B,AB,BAB,ABBAB,...) 
    // in which each term is the concatenation of the previous two.
    // 
    // Further, we define DA,B(n) to be the nth digit in the first term of FA,B that contains at least n digits.
    // 
    // Example:
    // 
    // Let A=1415926535, B=8979323846. We wish to find DA,B(35), say.
    // 
    // The first few terms of FA,B are:
    // 1415926535
    // 8979323846
    // 14159265358979323846
    // 897932384614159265358979323846
    // 14159265358979323846897932384614159265358979323846
    // Then DA,B(35) is the 35th digit in the fifth term, which is 9.
    // 
    // Now we use for A the first 100 digits of pi behind the decimal point:
    // 
    // 14159265358979323846264338327950288419716939937510 
    // 58209749445923078164062862089986280348253421170679
    // 
    // and for B the next hundred digits:
    //
    // 82148086513282306647093844609550582231725359408128 
    // 48111745028410270193852110555964462294895493038196 .
    // 
    // Find sum n = 0,1,...,17   10n× DA,B((127+19n)×7n) .
    nombre limite;

public:
    Probleme230(nombre limite_) : limite(limite_) {}
    ~Probleme230() {}
    
    nombre puissance(nombre a, nombre p)
    {
        nombre resultat = 1;
        while (p > 0)
        {
            if (p%2 == 1)
                resultat *= a;
            a = a*a;
            p /= 2;
        }
        
        return resultat;
    }
    
    void algorithme()
    {
        Timer t("algorithme");
        const std::string A = std::string(
            "14159265358979323846264338327950288419716939937510"
            "58209749445923078164062862089986280348253421170679");
        const std::string B = std::string(
            "82148086513282306647093844609550582231725359408128"
            "48111745028410270193852110555964462294895493038196");
            
        nombre l_max = (127+19*limite)*puissance(7, limite);
        vecteur fibonacci;
        fibonacci.push_back(A.size());
        fibonacci.push_back(B.size());
        
        for (nombre n = 2; fibonacci.back() < l_max; ++n)
        {
            fibonacci.push_back(fibonacci[n-1] + fibonacci[n-2]);
        }
        
        nombre resultat = 0;
        for (nombre n = 0; n < limite + 1; ++n)
        {
            nombre l = (127+19*n)*puissance(7, n) - 1;
            // std::cout << "(127+19*" << n << ")*7^" << n << " = " << l << std::endl;
            
            size_t i = 0;
            for (; i < fibonacci.size(); ++i)
            {
                if (fibonacci[i] > l) break;
            }
            
            while (i > 1)
            {
                nombre f_i_1 = fibonacci[i-1];
                if (l < f_i_1)
                {
                    i = i - 2;
                }
                else
                {
                    l = l - f_i_1;
                    i = i - 1;
                }
            }

            char c;
            if (l < A.size())
            {
                std::cout << "A";
                c = A[l];
            }
            else
            {
                std::cout << "B";
                c = B[l-A.size()];
            }
            // std::cout << "c(" << n << ") = " << c << std::endl;
            
            resultat += (c - '0')*puissance(10,n);
        }
        std::cout << std::endl;
        std::cout << resultat << std::endl;
        std::cout << 850481152593119296LL << std::endl; 
    }
};

int main(int argc, char** argv)
{
    nombre limite = 0;
    if (argc == 2)
    {
        limite = atol(argv[1]);
    }
    else
    {
        std::cout << "Limite : ";
        std::cin >> limite;
    }
    
    std::cout << std::numeric_limits<nombre>::max() << std::endl;
    
    Probleme230 p(limite);
    p.algorithme();
    return 0;
}

