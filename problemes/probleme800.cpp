#include "problemes.h"
#include "timer.h"

#include "numerique.h"
#include "arithmetique.h"
#include "premiers.h"
#include "chiffres.h"
#include "racine.h"

typedef size_t nombre;

namespace {
    nombre C(const std::vector<nombre> & premiers, nombre a, nombre b) {
        size_t count = 0;
        auto limite = std::log(a) * static_cast<double>(b);
        // q.log(p) + p.log(q) <= b.log(a)
        for (auto it = premiers.begin(), en = premiers.end(); it != en; ++it) {
            auto p = *it;
            auto log_p = std::log(p);
            auto limite_q = limite / log_p;
            auto lower_bound = std::ranges::lower_bound(premiers, limite_q);
            if (lower_bound <= it) {
                break;
            }
            while (lower_bound != it) {
                nombre q = *lower_bound;
                if (static_cast<double>(p) * std::log(q) + static_cast<double>(q) * log_p > limite) {
                    --lower_bound;
                } else {
                    break;
                }
            }
            auto distance = std::distance(it, lower_bound);
            if (distance > 0) {
                count += static_cast<size_t>(distance);
            } else {
                break;
            }
        }

        return count;
    }
}

ENREGISTRER_PROBLEME(800, "Hybrid Integers") {
    // An integer of the form $p^q q^p$ with prime numbers p != q is called a hybrid-integer.
    // For example, 800 = 2^5 5^2 is a hybrid-integer.
    //
    // We define $C(n)$ to be the number of hybrid-integers less than or equal to $n$.
    //You are given C(800) = 2 and C(800^{800}) = 10790.
    //
    // Find $C(800800^{800800})$.
    std::vector<nombre> premiers;
    {
        Timer t("Crible");
        premiers::crible235<nombre>(100'000'000, std::back_inserter(premiers));
    }

    std::cout << "C(800) = " << C(premiers, 800, 1) << std::endl;
    std::cout << "C(800, 800) = " << C(premiers, 800, 800) << std::endl;

    return std::to_string(C(premiers, 800800, 800800));
}
