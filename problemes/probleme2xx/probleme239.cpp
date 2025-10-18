#include "problemes.h"
#include "puissance.h"
#include "combinatoire.h"
#include "mpz_nombre.h"
#include "utilitaires.h"

ENREGISTRER_PROBLEME(239, "Infinite string tour") {
    // A set of disks numbered 1 through 100 are placed in a line in random order.
    //
    // What is the probability that we have a partial derangement such that exactly 22 prime number discs are found away
    // from their natural positions? (Any number of non-prime disks may also be found in or out of their natural
    // positions.)
    //
    // Give your answer rounded to 12 places behind the decimal point in the form 0.abcdefghijkl.
    const mpz_nombre denominateur = mpz_nombre::factorielle(100);

    mpz_nombre numerateur = 0;
    for (size_t n = 0; n <= 22; ++n) {
        numerateur += (n % 2 == 0 ? 1 : -1)
                      * mpz_nombre::coefficient_binomial(22, n)
                      * mpz_nombre::factorielle(97 - n);
    }

    numerateur *= mpz_nombre::coefficient_binomial(25, 22);

    const auto masque = puissance::puissance<size_t, unsigned>(10, 12);
    numerateur *= masque;
    numerateur /= denominateur;

    double resultat = numerateur.get_double() / masque;
    return std::to_fixed(resultat, 12);
}
