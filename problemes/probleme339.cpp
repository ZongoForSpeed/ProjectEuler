#include "problemes.h"
#include "utilitaires.h"

#include <deque>

ENREGISTRER_PROBLEME(339, "Peredur fab Efrawg") {
    // "And he came towards a valley, through which ran a river; and the borders of the valley were wooded, and on each
    // side of the river were level meadows. And on one side of the river he saw a flock of white sheep, and on the
    // other a flock of black sheep. And whenever one of the white sheep bleated, one of the black sheep would cross
    // over and become white; and when one of the black sheep bleated, one of the white sheep would cross over and
    // become black."
    // en.wikisource.org
    //
    // Initially each flock consists of n sheep. Each sheep (regardless of colour) is equally likely to be the next
    // sheep to bleat. After a sheep has bleated and a sheep from the other flock has crossed over, Peredur may remove
    // a number of white sheep in order to maximize the expected final number of black sheep. Let E(n) be the expected
    // final number of black sheep if Peredur uses an optimal strategy.
    //
    // You are given that E(5) = 6.871346 rounded to 6 places behind the decimal point.
    // Find E(10 000) and give your answer rounded to 6 places behind the decimal point.
    size_t n = 10000;
    long double resultat = 0.0L;

    std::deque<std::tuple<size_t, size_t, long double>> queue;
    queue.emplace_back(n, n, 1.0);
    while (!queue.empty()) {
        auto[white_sheep, black_sheep, r] = queue.front();
        queue.pop_front();

        if (white_sheep == 0) {
            resultat += r * black_sheep;
        } else if (black_sheep > white_sheep) {
            long double p = (white_sheep + black_sheep - 1.0L) / (white_sheep + black_sheep);
            for (size_t ws = 2; ws <= white_sheep; ws++) {
                long double r2 = p * (white_sheep + black_sheep - ws);
                p = r2 / (ws + r2);
            }

            resultat += r * p * (white_sheep + black_sheep);
            queue.emplace_back(black_sheep - 2, black_sheep - 1, r * (1 - p));
        } else {
            queue.emplace_back(white_sheep - 1, black_sheep + 1, r * black_sheep / (white_sheep + black_sheep));
            queue.emplace_back(black_sheep - 2, black_sheep - 1, r * white_sheep / (white_sheep + black_sheep));
        }
    }

    return std::to_fixed(resultat, 6);
}
