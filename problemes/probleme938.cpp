#include "problemes.h"
#include "multidimension.h"
#include "utilitaires.h"

#include <iomanip>
#include <iostream>
#include <string>

namespace {
    long double pRed(size_t red, size_t black) {
        return (1.0L * red) / (red + black);
    }

    long double pBlack(size_t red, size_t black) {
        return (1.0L * black) / (red + black);
    }

    long double pRR(size_t red, size_t black) {
        return pRed(red, black) * pRed(red - 1, black);
    }

    long double pBB(size_t red, size_t black) {
        return pBlack(red, black) * pBlack(red, black - 1);
    }

    long double pDifferent(size_t red, size_t black) {
        return pRed(red, black) * pBlack(red - 1, black)
               + pBlack(red, black) * pRed(red, black - 1);
    }

    long double p(multidimension<long double, 2> &cache, size_t red, size_t black) {
        long double result = cache[red][black];
        if (result >= 0) {
            return result;
        }

        result = 0;
        if (red == 0) {
            result = 1;
        } else if (black == 0) {
            result = 0;
        } else {
            // p(R, B) = pRED * p(R-2, B) + pDifferent * p(R-1, B) + pBLACK * p(R, B)
            // (1 - pBLACK) * p(R, B) = pRED * p(R-2, B) + pDifferent * p(R-1, B)
            // p(R, B) = (pRED * p(R-2, B) + pDifferent * p(R-1, B)) / (1 - pBLACK)

            // If both cards are red, they are discarded.
            if (red >= 2) {
                result += pRR(red, black) * p(cache, red - 2, black);
            }
            // If they are different colours, the red card is put back in the deck and the black card is discarded.a
            if (black >= 1 && red >= 1) {
                result += pDifferent(red, black) * p(cache, red, black - 1);
            }
            // If both cards are black, they are both put back in the deck.
            result /= 1 - pBB(red, black);
        }

        cache[red][black] = result;
        return result;
    }
}

ENREGISTRER_PROBLEME(938, "Exhausting a Colour") {
    // A deck of cards contains $R$ red cards and $B$ black cards.
    //
    // A card is chosen uniformly randomly from the deck and removed. A second card is then chosen uniformly randomly
    // from the cards remaining and removed.
    //
    //      If both cards are red, they are discarded.
    //      If both cards are black, they are both put back in the deck.
    //      If they are different colours, the red card is put back in the deck and the black card is discarded.
    //
    // Play ends when all the remaining cards in the deck are the same colour and let $P(R,B)$ be the probability that
    // this colour is black.
    //
    // You are given $P(2,2) = 0.4666666667$, $P(10,9) = 0.4118903397$ and $P(34,25) = 0.3665688069$.
    //
    // Find $P(24690,12345)$. Give your answer with 10 digits after the decimal point.
    multidimension<long double, 2> cache(24690u + 1, 12345u + 1, -1);
    std::cout << std::setprecision(10);
    std::cout << "P(2,2)    = " << p(cache, 2, 2) << std::endl;
    std::cout << "P(10,9)   = " << p(cache, 10, 9) << std::endl;
    std::cout << "P(34,25)  = " << p(cache, 34, 25) << std::endl;
    long double result = p(cache, 24690, 12345);
    std::cout << "P(24690,12345) = " << result << std::endl;

    return std::to_fixed(result, 10);
}
