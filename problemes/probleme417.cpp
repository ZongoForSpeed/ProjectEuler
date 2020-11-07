#include "problemes.h"
#include "utilitaires.h"
#include "arithmetique.h"
#include "arithmetique_modulaire.h"
#include "premiers.h"
#include "combinatoire.h"

namespace {
    long L(size_t n) {
        std::vector<size_t> restes;
        size_t reste = 1;
        while (std::find(restes.begin(), restes.end(), reste) == restes.end()) {
            restes.push_back(reste);
            while (reste % n == reste) reste *= 10;
            reste = reste % n;
        }

        return std::distance(std::find(restes.begin(), restes.end(), reste), restes.end());
    }

    size_t somme_periodes(size_t limite) {
        std::vector<size_t> premiers;
        premiers::crible2<size_t>(limite, std::back_inserter(premiers));

        std::vector<size_t> diviseursPremiers(limite, 0);
        std::iota(diviseursPremiers.begin(), diviseursPremiers.end(), 0ul);

        for (size_t p = 2, length = diviseursPremiers.size(); p < length; ++p) {
            if (p == diviseursPremiers[p]) {
                for (size_t k = p * p; k < limite; k += p) {
                    diviseursPremiers[k] = std::min(diviseursPremiers[k], p);
                }
            }
        }

        std::vector<std::pair<size_t/*p^k*/, size_t/*periode*/>> puissancesPremiersPeriodes;
        for (size_t p: premiers) {
            if (p == 2 || p == 5)
                continue;

            for (size_t pk = p, phi = p - 1; pk <= limite; pk *= p, phi *= p) {
                size_t periode = phi;

                size_t facteurs = periode;
                while (facteurs > 1) {
                    size_t q = diviseursPremiers[facteurs];
                    if (puissance::puissance_modulaire<size_t>(10, periode / q, pk) == 1)
                        periode /= q;
                    facteurs /= q;
                }
                puissancesPremiersPeriodes.emplace_back(pk, periode);
            }
        }

        std::sort(puissancesPremiersPeriodes.begin(), puissancesPremiersPeriodes.end());

        std::vector<size_t> periodes(limite + 1, 0);
        periodes[1] = 1;
        for (auto&[pk, period]: puissancesPremiersPeriodes) {
            for (size_t j = 0, max_j = limite / pk; j <= max_j; j++) {
                if (periodes[j] != 0)
                    periodes[j * pk] = arithmetique::PPCM(periodes[j], period);
            }
        }

        size_t resultat = 0;
        for (size_t i = 3; i <= limite; i++) {
            size_t n = i;

            while (n % 2 == 0) n /= 2;
            while (n % 5 == 0) n /= 5;

            if (n > 1) {
                resultat += periodes[n];
            }
        }
        return resultat;
    }
}

ENREGISTRER_PROBLEME(417, "Reciprocal cycles II") {
    // A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators
    // 2 to 10 are given:
    //
    //  1/2	= 	0.5
    //  1/3	= 	0.(3)
    //  1/4	= 	0.25
    //  1/5	= 	0.2
    //  1/6	= 	0.1(6)
    //  1/7	= 	0.(142857)
    //  1/8	= 	0.125
    //  1/9	= 	0.(1)
    // 1/10	= 	0.1
    //
    // Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit
    // recurring cycle.
    //
    // Unit fractions whose denominator has no other prime factors than 2 and/or 5 are not considered to have a
    // recurring cycle.
    //
    // We define the length of the recurring cycle of those unit fractions as 0.
    //
    // Let L(n) denote the length of the recurring cycle of 1/n. You are given that ∑ L(n) for 3 ≤ n ≤ 1 000 000
    // equals 55535191115.
    //
    // Find ∑ L(n) for 3 ≤ n ≤ 100 000 000.
    std::cout << "L(6) = " << L(6) << std::endl;
    std::cout << "L(7) = " << L(7) << std::endl;

    std::cout << "Somme 3 ≤ n ≤ 1 000 000 L(n) = " << somme_periodes(1'000'000) << std::endl;

    return std::to_string(somme_periodes(100'000'000));
}
