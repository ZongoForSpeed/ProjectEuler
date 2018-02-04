#include "problemes.h"
#include "utilitaires.h"
#include "mp_nombre.h"
#include "chiffres.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(387, "Harshad Numbers") {
    // A Harshad or Niven number is a number that is divisible by the sum of its digits. 201 is a Harshad number because
    // it is divisible by 3 (the sum of its digits.)
    // When we truncate the last digit from 201, we get 20, which is a Harshad number. 
    // When we truncate the last digit from 20, we get 2, which is also a Harshad number. 
    // Let's call a Harshad number that, while recursively truncating the last digit, always results 
    // in a Harshad number a right truncatable Harshad number.
    //
    // Also: 
    // 201/3=67 which is prime. 
    // Let's call a Harshad number that, when divided by the sum of its digits, results in a prime a strong Harshad
    // number.
    //
    // Now take the number 2011 which is prime. 
    // When we truncate the last digit from it we get 201, a strong Harshad number that is also right truncatable.
    // Let's call such primes strong, right truncatable Harshad primes.
    //
    // You are given that the sum of the strong, right truncatable Harshad primes less than 10000 is 90619.
    //
    // Find the sum of the strong, right truncatable Harshad primes less than 10**14.
    nombre resultat = 0;
    nombre taille = 14;
    vecteur courantHarshad{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (nombre it = 0; it < taille - 2; ++it) {
        vecteur precHarshald = courantHarshad;
        courantHarshad.clear();
        for (auto p: precHarshald) {
            nombre b = 10 * p;
            for (nombre i = b; i < b + 10; ++i) {
                nombre d = chiffres::somme_chiffres(i);
                nombre q = i / d;
                nombre r = i % d;
                if (r == 0) {
                    courantHarshad.push_back(i);
                    if (mp_nombre::premier(q, 25)) {
                        nombre b2 = 10 * i;
                        vecteur v{b2 + 1, b2 + 3, b2 + 7, b2 + 9};
                        for (auto j: v) {
                            if (mp_nombre::premier(j, 25)) {
                                resultat += j;
                            }
                        }
                    }
                }
            }
        }
    }

    return std::to_string(resultat);
}
