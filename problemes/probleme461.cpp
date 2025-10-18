#include "problemes.h"
#include "timer.h"
#include "utilitaires.h"

#include <cmath>

typedef std::tuple<long double/*value*/, size_t /*a*/, size_t /*b*/> valeur;

namespace {
    long double fn(size_t n, size_t k) {
        return std::expm1((1.0L * k) / n);
    }

    bool comparateur_min(const valeur &v, long double objectif) {
        return std::get<0>(v) < objectif;
    }

    bool comparateur_max(long double objectif, const valeur &v) {
        return objectif < std::get<0>(v);
    }

    std::tuple<size_t, size_t, size_t, size_t> g(size_t n, long double epsilon) {
        std::vector<valeur> cache;

        {
            Timer t("Construction cache");
            size_t a_max = static_cast<size_t>(std::log(M_PIl / 2 + 1) * n + 1);
            for (size_t a = 1; a < a_max; ++a) {
                long double fa = fn(n, a);
                size_t b_max = static_cast<size_t>(std::log((M_PIl - fa) + 1) * n + 1);
                for (size_t b = a; b < b_max; ++b) {
                    long double fb = fn(n, b);
                    cache.emplace_back(fa + fb, a, b);
                }
            }

            std::cout << "Taille cache = " << cache.size() << std::endl;
            std::sort(cache.begin(), cache.end());
        }

        std::tuple<size_t, size_t, size_t, size_t> optimum;
        long double delta_min = std::numeric_limits<long double>::max();

        for (auto &[fab, a, b]: cache) {
            auto it = std::lower_bound(cache.begin(), cache.end(), M_PIl - fab - epsilon, comparateur_min);
            auto en = std::upper_bound(cache.begin(), cache.end(), M_PIl - fab + epsilon, comparateur_max);
            for (; it != en; ++it) {
                auto&[fcd, c, d] = *it;
                long double delta = std::abs(fab + fcd - M_PIl);
                if (delta < delta_min) {
                    delta_min = delta;
                    optimum = std::make_tuple(a, b, c, d);
                }
            }
        }

        std::cout << "g(" << n << ") = " << optimum << std::endl;
        return optimum;
    }
}

ENREGISTRER_PROBLEME(461, "Almost Pi") {
    // Let fn(k) = ek/n - 1, for all non-negative integers k.
    //                                                         _______
    // Remarkably, f200(6) + f200(75) + f200(89) + f200(226) = 3.141592644529… ≈ π.
    //
    // In fact, it is the best approximation of π of the form fn(a) + fn(b) + fn(c) + fn(d) for n = 200.
    //
    // Let g(n) = a² + b² + c² + d² for a, b, c, d that minimize the error: | fn(a) + fn(b) + fn(c) + fn(d) - π|
    // (where |x| denotes the absolute value of x).
    //
    // You are given g(200) = 6² + 75² + 89² + 226² = 64658.
    //
    // Find g(10000).
    g(200, 0.0001L);

    auto[a, b, c, d] = g(10000, 0.000000001L);
    size_t resultat = a * a + b * b + c * c + d * d;
    return std::to_string(resultat);
}
