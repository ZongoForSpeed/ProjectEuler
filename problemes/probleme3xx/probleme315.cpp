#include "../problemes.h"
#include "premiers.h"
#include "multidimension.h"
#include "chiffres.h"

#include <bitset>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    size_t transition(const multidimension<size_t, 2> &transitions,
                      const std::vector<std::bitset<7>> &digits, size_t a, size_t b) {
        auto chiffres_a = chiffres::extraire_chiffres(a);
        auto chiffres_b = chiffres::extraire_chiffres(b);

        auto ita = chiffres_a.rbegin();
        auto ena = chiffres_a.rend();

        auto itb = chiffres_b.rbegin();
        auto enb = chiffres_b.rend();
        size_t total = 0;
        for (; ita != ena && itb != enb; ++ita, ++itb) {
            total += transitions[*ita][*itb];
        }

        for (; ita != ena; ++ita) {
            total += digits[*ita].count();
        }

        for (; itb != enb; ++itb) {
            total += digits[*itb].count();
        }

        return total;
    }

    size_t compteur(const std::vector<std::bitset<7>> &digits, size_t n) {
        size_t total = 0;
        chiffres::boucle_chiffre(n, [&total, &digits](size_t d) { total += digits[d].count(); });
        return total;
    }

    size_t suivant(size_t n) {
        return n < 10 ? 0 : chiffres::somme_chiffres(n);
    }

    std::vector<size_t> clocks(size_t n) {
        std::vector<size_t> result;
        for (; n > 0; n = suivant(n)) {
            result.push_back(n);
        }

        return result;
    }
}

ENREGISTRER_PROBLEME(315, "Digital root clocks") {
    // Sam and Max are asked to transform two digital clocks into two "digital root" clocks.
    // A digital root clock is a digital clock that calculates digital roots step by step.
    //
    // When a clock is fed a number, it will show it and then it will start the calculation, showing all the
    // intermediate values until it gets to the result. For example, if the clock is fed the number 137, it will show:
    // "137" → "11" → "2" and then it will go black, waiting for the next number.
    //
    // Every digital number consists of some light segments: three horizontal (top, middle, bottom) and four vertical
    // (top-left, top-right, bottom-left, bottom-right). Number "1" is made of vertical top-right and bottom-right,
    // number "4" is made by middle horizontal and vertical top-left, top-right and bottom-right. Number "8" lights
    // them all.
    //
    // The clocks consume energy only when segments are turned on/off.
    // To turn on a "2" will cost 5 transitions, while a "7" will cost only 4 transitions.
    //
    // Sam and Max built two different clocks.
    //
    // Sam's clock is fed e.g. number 137: the clock shows "137", then the panel is turned off, then the next number
    // ("11") is turned on, then the panel is turned off again and finally the last number ("2") is turned on and, after
    // some time, off.
    // For the example, with number 137, Sam's clock requires:
    //
    // "137":   (2 + 5 + 4) × 2 = 22 transitions ("137" on/off).
    // "11" :   (2 + 2) × 2 = 8 transitions ("11" on/off).
    // "2"  :   (5) × 2 = 10 transitions ("2" on/off).
    // For a grand total of 40 transitions.
    // Max's clock works differently. Instead of turning off the whole panel, it is smart enough to turn off only those
    // segments that won't be needed for the next number.
    // For number 137, Max's clock requires:
    //
    // "137":
    // 2 + 5 + 4 = 11 transitions ("137" on)
    // 7 transitions (to turn off the segments that are not needed for number "11").
    // "11" :
    // 0 transitions (number "11" is already turned on correctly)
    // 3 transitions (to turn off the first "1" and the bottom part of the second "1"; the top part is common with
    // number "2").
    // "2"  :
    // 4 transitions (to turn on the remaining segments in order to get a "2")
    // 5 transitions (to turn off number "2").
    // For a grand total of 30 transitions.
    // Of course, Max's clock consumes less power than Sam's one.
    // The two clocks are fed all the prime numbers between A = 10**7 and B = 2×10**7. 
    // Find the difference between the total number of transitions needed by Sam's clock and that needed by Max's one.
    size_t borne_inf = 10000000;
    size_t borne_sup = 20000000;

    vecteur premiers;
    premiers::crible2<size_t>(borne_sup, std::back_inserter(premiers));

    premiers.erase(premiers.begin(), std::upper_bound(premiers.begin(), premiers.end(), borne_inf));

    const std::vector<std::bitset<7>> digits{
            std::bitset<7>("1111101"),  // 0
            std::bitset<7>("1010000"),  // 1
            std::bitset<7>("0110111"),  // 2
            std::bitset<7>("1010111"),  // 3
            std::bitset<7>("1011010"),  // 4
            std::bitset<7>("1001111"),  // 5
            std::bitset<7>("1101111"),  // 6
            std::bitset<7>("1011001"),  // 7
            std::bitset<7>("1111111"),  // 8
            std::bitset<7>("1011111")   // 9
    };

    multidimension<size_t, 2> transitions(10u, 10u, 0u);
    for (size_t d1 = 0; d1 < 10; ++d1)
        for (size_t d2 = 0; d2 < 10; ++d2) {
            auto d = digits[d1] ^digits[d2];
            transitions[d1][d2] = d.count();
        }

    size_t totalSam = 0;
    size_t totalMax = 0;
    for (auto p: premiers) {
        size_t precedent = 0;
        for (auto n: clocks(p)) {
            totalSam += 2 * compteur(digits, n);
            if (precedent == 0)
                totalMax += compteur(digits, n);
            else
                totalMax += transition(transitions, digits, precedent, n);

            precedent = n;
        }

        totalMax += compteur(digits, precedent);
    }

    return std::to_string(totalSam - totalMax);
}
