#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "mp_nombre.h"

#include <bitset>

typedef std::vector<mp_nombre> vecteur;

namespace {
    void ajout_facteur(const mp_nombre &n, std::map<mp_nombre, size_t> &resultat, const std::set<mp_nombre> &premiers) {
        std::map<mp_nombre, size_t> d;
        arithmetiques::decomposition(n, premiers, d);
        for (auto p: d) {
            resultat[p.first] += p.second;
        }
    }

    size_t algorithme(const mp_nombre &n,
                      const mp_nombre &lastp,
                      size_t pgcd,
                      std::map<mp_nombre, size_t> &decomposition,
                      const mp_nombre &limite,
                      const std::set<mp_nombre> &premiers) {
        size_t resultat = 0;
        if (pgcd == 1) {
            boost::optional<size_t> exposant;
            for (auto &it : decomposition) {
                if (it.second == 1) {
                    exposant = boost::none;
                    break;
                }
                if (exposant)
                    exposant = arithmetiques::PGCD(*exposant, it.second);
                else
                    exposant = it.second;
            }

            if (exposant && *exposant == 1)
                ++resultat;
        }

        mp_nombre maxp = mp_nombre::racine_carre(limite / n);
        if (maxp >= lastp)
            maxp = lastp - 1;

        mp_nombre minp = 2;
        for (auto it = decomposition.rbegin(), en = decomposition.rend(); it != en; ++it) {
            if (it->second < 2) {
                minp = it->first;
                break;
            }
        }

        // auto lower = std::lower_bound(premiers.begin(), premiers.end(), minp);
        // auto upper = std::upper_bound(premiers.begin(), premiers.end(), maxp);
        for (mp_nombre p = maxp; p >= minp; --p) {
            if (premiers.find(p) != premiers.end()) {
                mp_nombre m = n * p;
                std::map<mp_nombre, size_t> d2 = decomposition;
                ajout_facteur(p - 1, d2, premiers);
                for (size_t exposant = 2; p * m < limite; ++exposant) {
                    m *= p;
                    d2[p]++;
                    resultat += algorithme(m, p, arithmetiques::PGCD(pgcd, exposant), d2, limite, premiers);
                }
            }
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(302, "Strong Achilles Numbers") {
    // A positive integer n is powerful if p² is a divisor of n for every prime factor p in n.
    //
    // A positive integer n is a perfect power if n can be expressed as a power of another positive integer.
    //
    // A positive integer n is an Achilles number if n is powerful but not a perfect power. For example, 864 and 1800
    // are Achilles numbers:
    // 864 = 2**5·3**3 and 1800 = 2**3·3²·5².
    //
    // We shall call a positive integer S a Strong Achilles number if both S and φ(S) are Achilles numbers.1
    // For example, 864 is a Strong Achilles number: φ(864) = 288 = 2**5·3**2. 
    // However, 1800 isn't a Strong Achilles number because: φ(1800) = 480 = 
    // 2**5·3**1·5**1.
    //
    // There are 7 Strong Achilles numbers below 10**4 and 656 below 10**8.
    //
    // How many Strong Achilles numbers are there below 10**18?
    //
    // 1 φ denotes Euler's totient function.
    const size_t limite_crible = 1000000 + 1;
    std::set<mp_nombre> premiers;
    premiers::crible235<mp_nombre>(limite_crible, std::inserter(premiers, premiers.begin()));

    mp_nombre limite = mp_nombre::puissance(10, 18);

    std::map<mp_nombre, size_t> decomposition;
    mp_nombre resultat = algorithme(1, limite_crible, 0, decomposition, limite, premiers);

    return resultat.to_string();
}
