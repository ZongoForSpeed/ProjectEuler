#include "problemes.h"
#include "format.h"
#include "premiers.h"
#include "utilitaires.h"

#include <boost/math/constants/constants.hpp>

namespace {
    long double integral(long double beta) {
        return beta + (std::log(std::cos(beta)) - std::log(std::cos(0.0L))) / std::tan(beta);
    }
}

ENREGISTRER_PROBLEME(613, "Pythagorean Ant") {
    // Dave is doing his homework on the balcony and, preparing a presentation about Pythagorean triangles, has just
    // cut out a triangle with side lengths 30cm, 40cm and 50cm from some cardboard, when a gust of wind blows the
    // triangle down into the garden.
    //
    // Another gust blows a small ant straight onto this triangle. The poor ant is completely disoriented and starts to
    // crawl straight ahead in random direction in order to get back into the grass.
    //
    // Assuming that all possible positions of the ant within the triangle and all possible directions of moving on are
    // equiprobable, what is the probability that the ant leaves the triangle along its longest side?
    //
    // Give your answer rounded to 10 digits after the decimal point.
    const long double beta1 = std::acos(0.6L);
    const long double beta2 = std::acos(0.8L);

    long double resultat = 1.0L / 4 + (integral(beta1) + integral(beta2)) / (2 * M_PIl);
    return format::to_fixed(resultat, 10);
}
