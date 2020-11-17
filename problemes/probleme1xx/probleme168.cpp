#include "problemes.h"
#include "mpz_nombre.h"

ENREGISTRER_PROBLEME(168, "Number Rotations") {
    // Consider the number 142857. We can right-rotate this number by moving the last digit (7) to the front of it,
    // giving us 714285.
    // It can be verified that 714285=5×142857.
    // This demonstrates an unusual property of 142857: it is a divisor of its right-rotation.
    //
    // Find the last 5 digits of the sum of all integers n, 10 < n < 10^100, that have this property.
    mpz_nombre resultat = 0;
    for (size_t puissance = 1; puissance < 101; ++puissance) {
        for (size_t a = 1; a < 10; ++a)
            for (size_t n = 1; n < 10; ++n) {
                mpz_nombre numerateur = a * (mpz_nombre::puissance(10, puissance) - n);
                mpz_nombre denominateur = 10 * n - 1;

                if (numerateur % denominateur == 0) {
                    mpz_nombre valeur = numerateur / denominateur;
                    if (valeur.nombre_chiffres() == puissance) {
                        valeur = 10 * valeur + a;
                        if (valeur.nombre_chiffres() <= 100)
                            resultat += valeur;
                    }
                }
            }
    }

    resultat %= 100000ul;
    return resultat.to_string();
}
