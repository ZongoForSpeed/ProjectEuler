#include "problemes.h"
#include "arithmetique.h"
#include "chiffres.h"
#include "mpz_nombre.h"

typedef std::vector<size_t> vecteur;

namespace {
    struct resultat {
        size_t sg;
        mpz_nombre g;
    };

    void algorithme(size_t f, const vecteur &factorielles, std::map<mpz_nombre, resultat> &cache) {
        const mpz_nombre sf = chiffres::somme_chiffres(f);

        size_t sg = 0;
        vecteur chiffres(10, 0);
        for (size_t i = 9; i >= 1; i--) {
            chiffres[i] = f / factorielles[i];
            f = f % factorielles[i];
            sg += i * chiffres[i];
        }

        mpz_nombre n = 0;
        for (size_t i = 1; i <= 9; i++) {
            for (size_t j = 0; j < chiffres[i]; j++) {
                n = n * 10 + i;
            }
        }

        resultat r{sg, n};

        if (auto it = cache.find(sf);it == cache.end() || r.g < it->second.g) {
            cache[sf] = r;
        }
    }
}

ENREGISTRER_PROBLEME(254, "Sums of Digit Factorials") {
    // Define f(n) as the sum of the factorials of the digits of n. For example, f(342) = 3! + 4! + 2! = 32.
    //
    // Define sf(n) as the sum of the digits of f(n). So sf(342) = 3 + 2 = 5.
    // 
    // Define g(i) to be the smallest positive integer n such that sf(n) = i. 
    // Though sf(342) is 5, sf(25) is also 5, and it can be verified that g(5) is 25.
    // 
    // Define sg(i) as the sum of the digits of g(i). So sg(5) = 2 + 5 = 7.
    // 
    // Further, it can be verified that g(20) is 267 and ∑ sg(i) for 1 ≤ i ≤ 20 is 156.
    //
    // What is ∑ sg(i) for 1 ≤ i ≤ 150?
    const vecteur factorielles{1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

    std::map<mpz_nombre, resultat> cache;

    size_t borne = 999999;      // all values must end in 9 after this
    size_t limite = 9999999;    // all values must be maximal after this

    for (size_t f = 1; f < borne; f++) {
        algorithme(f, factorielles, cache);
    }
    for (size_t f = borne; f < limite; f += 10) {
        algorithme(f, factorielles, cache);
        f += 90;
        algorithme(f, factorielles, cache);
    }

    mpz_nombre somme = 0;
    for (const auto &r : cache) {
        somme += r.second.sg;
    }

    mpz_nombre prefixe = 9;
    mpz_nombre neufs = 999999;
    for (size_t sf = 63; sf <= 150; sf++) {
        mpz_nombre lf = chiffres::concatener(prefixe, neufs);
        for (size_t i = 9; i >= 1; i--) {
            somme += i * (lf / factorielles[i]);
            lf %= factorielles[i];
        }
        prefixe = (prefixe % 9) + 1;
        if (prefixe == 1) {
            neufs = neufs * 10 + 9;
        }
    }

    return somme.to_string();
}
