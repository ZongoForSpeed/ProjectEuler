#include "problemes.h"
#include "premiers.h"

#include <boost/rational.hpp>

#include "mpq_fraction.h"

typedef std::vector<size_t> vecteur;

namespace {
    size_t generer(const vecteur &premiers, const size_t premier, const mpq_fraction& f = mpq_fraction(0), size_t a = 0) {
        mpq_fraction objectif(1ul, 2ul);
        size_t resultat = 0;
        for (size_t m = a + 1; m * premier < 80 + 1; ++m) {
            size_t q = m;
            // remove factors f<=p
            for (size_t pp: premiers) {
                if (pp > premier)
                    break;
                while (q % pp == 0)
                    q = q / pp;
            }

            // m has factors f<=p only
            if (q == 1) {
                mpq_fraction f1 = f + mpq_fraction(1ul, m * m * premier * premier);
                if (f1 == objectif)
                    ++resultat;
                else {
                    if (f1.denominateur() % premier != 0)
                        for (size_t pp: premiers)
                            if (pp < premier) resultat += generer(premiers, pp, f1);
                    resultat += generer(premiers, premier, f1, m);
                }
            }
        }
        return resultat;
    }
}

ENREGISTRER_PROBLEME(152, "Writing 1/2 as a sum of inverse squares") {
    // There are several ways to write the number 1/2 as a sum of inverse squares using distinct integers.
    //
    // For instance, the numbers {2,3,4,5,7,12,15,20,28,35} can be used:
    //
    //      1/2 = 1/2² + 1/3² + 1/4² + 1/5² + 1/7² + 1/12² + 1/15² + 1/20² + 1/28² + 1/35²
    //
    // In fact, only using integers between 2 and 45 inclusive, there are exactly three ways to do it, the remaining two
    // being: {2,3,4,6,7,9,10,20,28,35,36,45} and {2,3,4,6,7,9,12,15,28,30,35,36,45}.
    //
    // How many ways are there to write the number 1/2 as a sum of inverse squares using distinct integers between 2 and
    // 80 inclusive?
    vecteur premiers;
    premiers::crible2<size_t>(40, std::back_inserter(premiers));

    mpz_nombre resultat = 0;
    for (size_t p: premiers)
        resultat += generer(premiers, p);

    return resultat.to_string();
}
