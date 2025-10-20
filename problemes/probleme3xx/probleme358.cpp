#include "../problemes.h"
#include "arithmetique.h"
#include "premiers.h"
#include "timer.h"

#include <boost/range/adaptor/reversed.hpp>

namespace {
    bool critere_56789(unsigned long long prime) {
        return (56789 * prime + 1) % 100000 == 0;
    }

    bool critere_137(unsigned long long prime) {
        long double cycle = 1.0L / prime;
        return cycle > 0.00000000137L &&
               cycle < 0.00000000138L;
    }

    std::optional<unsigned long long> cycle(unsigned long long p) {
        unsigned long long resultat = 0;
        unsigned long long numerateur = 1;
        size_t longueur = 0;
        while (true) {
            longueur++;
            numerateur *= 10;
            resultat += numerateur / p;
            numerateur %= p;

            if (numerateur <= 1 || longueur == p)
                break;
        }

        if (longueur != p - 1)
            return std::nullopt;

        return resultat;
    }
}

ENREGISTRER_PROBLEME(358, "Cyclic numbers") {
    // A cyclic number with n digits has a very interesting property:
    //
    // When it is multiplied by 1, 2, 3, 4, ... n, all the products have exactly the same digits, in the same order,
    // but rotated in a circular fashion!
    //
    // The smallest cyclic number is the 6-digit number 142857 :
    // 142857 × 1 = 142857
    // 142857 × 2 = 285714
    // 142857 × 3 = 428571
    // 142857 × 4 = 571428
    // 142857 × 5 = 714285
    // 142857 × 6 = 857142
    //
    // The next cyclic number is 0588235294117647 with 16 digits :
    // 0588235294117647 × 1 = 0588235294117647
    // 0588235294117647 × 2 = 1176470588235294
    // 0588235294117647 × 3 = 1764705882352941
    // ...
    // 0588235294117647 × 16 = 9411764705882352
    //
    // Note that for cyclic numbers, leading zeros are important.
    //
    // There is only one cyclic number for which, the eleven leftmost digits are 00000000137 and the five rightmost
    // digits are 56789 (i.e., it has the form 00000000137...56789 with an unknown number of digits in the middle).
    //
    // Find the sum of all its digits.
    std::vector<unsigned long long> premiers;
    {
        Timer t("Crible");
        premiers::crible235<unsigned long long>(750000000ul, std::back_inserter(premiers));
    }

    unsigned long long resultat = 0;
    for (const auto &p: boost::adaptors::reverse(premiers)) {
        if (critere_137(p) && critere_56789(p)) {
            if (auto longueur_cycle = cycle(p)) {
                resultat = longueur_cycle.value();
                break;
            }
        }
    }

    return std::to_string(resultat);
}
