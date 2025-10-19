#include "problemes.h"
#include "arithmetique.h"
#include "format.h"
#include "timer.h"
#include "utilitaires.h"

typedef int64_t nombre;

namespace {
    nombre distance(const std::pair<nombre, nombre> &a, const std::pair<nombre, nombre> &b) {
        nombre dx = a.first - b.first;
        nombre dy = a.second - b.second;
        return dx * dx + dy * dy;
    }

    long double d(size_t k) {
        std::vector<nombre> s;
        s.emplace_back(290797);
        for (size_t i = 0; i <= 2 * k; ++i) {
            nombre sn = s.back();
            nombre sn1 = (sn * sn) % 50'515'093;
            s.emplace_back(sn1);
        }

        std::vector<std::pair<nombre, nombre>> P;
        for (size_t n = 0; n < k; ++n) {
            P.emplace_back(s[2 * n], s[2 * n + 1]);
        }

        std::ranges::sort(P, [](const std::pair<nombre, nombre> &a, const std::pair<nombre, nombre> &b) {
            if (a.first < b.first) {
                return true;
            } else if (a.first > b.first) {
                return false;
            } else {
                return a.second < b.second;
            }
        });

        nombre min = std::numeric_limits<nombre>::max();
        for (auto it1 = P.begin(), en = P.end(); it1 != en; ++it1) {
            nombre &x1 = it1->first;
            for (auto it2 = std::next(it1); it2 != en; ++it2) {
                nombre &x2 = it2->first;
                if (std::abs(x1 - x2) > min) {
                    break;
                }
                auto d = distance(*it1, *it2);
                if (d < min) {
                    min = d;
                    // std::cout << "found min = " << std::fixed << std::setprecision(9)
                    //          << std::sqrt(static_cast<long double>(min))
                    //          << " between " << *it1 << " and " << *it2 << std::endl;
                }
            }
        }

        long double result = std::sqrt(static_cast<long double>(min));
        std::cout << "d(" << k << ") = " << std::fixed << std::setprecision(9) << result << std::endl;
        return result;
    }
}

ENREGISTRER_PROBLEME(816, "Shortest Distance Among Points") {
    // We create an array of points P_n in a two dimensional plane using the following random
    // number generator:
    // s_0=290797
    // s_{n+1}={s_n}^2 mod 50515093
    //
    // P_n=(s_{2n},s_{2n+1})
    //
    // Let d(k) be the shortest distance of any two (distinct) points among P_0, ..., P_{k - 1}.
    // E.g. d(14)=546446.466846479.
    //
    // Find d(2000000). Give your answer rounded to 9 places after the decimal point.
    //
    d(14);
    return format::to_fixed(d(2'000'000), 9);
}
