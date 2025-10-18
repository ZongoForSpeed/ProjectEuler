#include "problemes.h"
#include "arithmetique.h"
#include "utilitaires.h"

typedef long nombre;
typedef std::pair<nombre, nombre> paire;

namespace {
    long double
    probabilite(std::map<std::tuple<nombre, nombre, bool>, long double> &cache, nombre m, nombre n, bool f) {
        auto key = std::make_tuple(m, n, f);
        auto it = cache.find(key);
        if (it != cache.end()) {
            return it->second;
        }

        long double resultat = 0;
        if (m == 1) {
            resultat = n;
        } else {
            resultat = probabilite(cache, m - 1, n, f) * (n + 1 - f);

            resultat += probabilite(cache, m - 1, n + 1, f)
                        * (f * std::max(0l, 999 - 2 * n + 1) + (1 - f) * std::max(0l, 999 - 2 * n - 1));

            resultat += probabilite(cache, m - 1, n + 1, true) * (1 - f);
        }

        resultat /= 1000.0l;

        cache.emplace(key, resultat);
        return resultat;
    }
}

ENREGISTRER_PROBLEME(371, "Licence plates") {
    // Oregon licence plates consist of three letters followed by a three digit number (each digit can be from [0..9]).
    // While driving to work Seth plays the following game:
    // Whenever the numbers of two licence plates seen on his trip add to 1000 that's a win.
    //
    // E.g. MIC-012 and HAN-988 is a win and RYU-500 and SET-500 too. (as long as he sees them in the same trip).
    //
    // Find the expected number of plates he needs to see for a win.
    // Give your answer rounded to 8 decimal places behind the decimal point.
    //
    // Note: We assume that each licence plate seen is equally likely to have any three digit number on it.
    long double resultat = 0;
    std::map<std::tuple<nombre, nombre, bool>, long double> cache;
    for (long i = 1; i < 300; ++i) {
        resultat += i * probabilite(cache, i, 0, false);
    }

    return std::to_fixed(resultat, 8);
}
