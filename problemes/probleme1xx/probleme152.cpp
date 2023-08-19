#include "problemes.h"
#include "numerique.h"
#include "premiers.h"

#include <boost/rational.hpp>

typedef std::vector<size_t> vecteur;
typedef boost::rational<uint128_t> fraction;

namespace {
    size_t generer(const vecteur &premiers, const size_t premier, fraction f = fraction(0), size_t a = 0) {
        fraction objectif(1, 2);
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
                fraction f1 = f + fraction(1, m * m * premier * premier);
                if (f1 == objectif)
                    ++resultat;
                else {
                    if (f1.denominator() % premier != 0)
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

    uint128_t resultat = 0;
    for (size_t p: premiers)
        resultat += generer(premiers, p);

    return std::to_string(resultat);
}
