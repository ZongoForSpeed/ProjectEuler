#include "problemes.h"
#include "chiffres.h"
#include "timer.h"

#include <iostream>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;

ENREGISTRER_PROBLEME(25, "1000-digit Fibonacci number")
{
    Timer t("probleme 25");
    // The Fibonacci sequence is defined by the recurrence relation:
    //
    // Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
    // Hence the first 12 terms will be:
    // 
    // F1 = 1
    // F2 = 1
    // F3 = 2
    // F4 = 3
    // F5 = 5
    // F6 = 8
    // F7 = 13
    // F8 = 21
    // F9 = 34
    // F10 = 55
    // F11 = 89
    // F12 = 144
    // The 12th term, F12, is the first term to contain three digits.
    // 
    // What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
    nombre n = 1;
    nombre a = 0;
    nombre b = 1;
    while (chiffres::nombre_chiffres(b) < 1000)
    {
        nombre tmp = a;
        a = b;
        b += tmp;
        ++n;
    }
    std::cout << "Solution: " << n << std::endl;
}
