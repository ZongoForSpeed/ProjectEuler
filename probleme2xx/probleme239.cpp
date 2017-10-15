#include "problemes.h"
#include "utilitaires.h"
#include "mp_nombre.h"
#include "puissance.h"

ENREGISTRER_PROBLEME(239, "Infinite string tour") {
    // A set of disks numbered 1 through 100 are placed in a line in random order.
    //
    // What is the probability that we have a partial derangement such that exactly 22 prime number discs are found away
    // from their natural positions? (Any number of non-prime disks may also be found in or out of their natural
    // positions.)
    //
    // Give your answer rounded to 12 places behind the decimal point in the form 0.abcdefghijkl.
    const mp_nombre denominateur = mp_nombre::factorielle(100);

    mp_nombre numerateur = 0;
    for (size_t n = 0; n <= 22; ++n) {
        numerateur += (n % 2 == 0 ? 1 : -1)
                      * mp_nombre::coefficient_binomial(22, n)
                      * mp_nombre::factorielle(97 - n);
    }

    numerateur *= mp_nombre::coefficient_binomial(25, 22);

    const auto masque = puissance::puissance<size_t, unsigned>(10, 12);
    numerateur *= masque;
    numerateur /= denominateur;

    long double resultat = numerateur.get_double() / masque;
    return std::to_string(resultat, 12);
}
