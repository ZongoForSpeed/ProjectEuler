#include "problemes.h"
#include "chiffres.h"
#include "arithmetique.h"
#include "racine.h"
#include "mpz_nombre.h"

typedef std::vector<mpz_nombre> vecteur;
typedef std::pair<mpz_nombre, mpz_nombre> paire;
typedef std::map<mpz_nombre, mpz_nombre> dictionnaire;

namespace {
    bool test(const mpz_nombre &n) {
        auto chiffres = n.extraire_chiffres();
        return chiffres[0] == 1 && chiffres[2] == 2 && chiffres[4] == 3 && chiffres[6] == 4 && chiffres[8] == 5
               && chiffres[10] == 6 && chiffres[12] == 7 && chiffres[14] == 8 && chiffres[16] == 9 && chiffres[18] == 0;
    }
}

ENREGISTRER_PROBLEME(206, "Concealed Square") {
    // Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0,
    // where each “_” is a single digit.
    mpz_nombre minimum = racine::racine_carre(102030405060708LL); // 0900
    mpz_nombre maximum = racine::racine_carre(192939495969798LL); // 9900

    mpz_nombre resultat = 0;
    for (mpz_nombre n = minimum; n < maximum; ++n) {
        mpz_nombre carre3 = (n * 100 + 30) * (n * 100 + 30);
        if (test(carre3)) {
            resultat = n * 100 + 30;
            break;
        }

        mpz_nombre carre7 = (n * 100 + 70) * (n * 100 + 70);
        if (test(carre7)) {
            resultat = n * 100 + 70;
            break;
        }
    }

    return resultat.to_string();
}
