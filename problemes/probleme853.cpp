#include <ranges>

#include "problemes.h"

#include <string>

#include "arithmetique.h"
#include "format/map.h"
#include "format/optional.h"
#include "premiers.h"
#include "puissance.h"
#include "timer.h"

typedef unsigned long long nombre;

namespace {
    std::optional<nombre> pisanoPeriod(nombre n, nombre limite) {
        nombre f1 = 0, f2 = 1;
        nombre k = 0;

        while (true) {
            nombre temp = (f1 + f2) % n;
            f1 = f2;
            f2 = temp;
            k++;
            if (f1 == 0 && f2 == 1) {
                return k;
            }
            if (k > limite) {
                return std::nullopt;
            }
        }
    }

    std::optional<nombre> periodPK(nombre p, nombre k, nombre limit) {
        if (auto period = pisanoPeriod(p, limit)) {
            nombre result = puissance::puissance(p, k - 1) * period.value();
            if (result <= limit) {
                return result;
            }
        }
        return std::nullopt;
    }

    std::optional<nombre> pisanoPeriod(const std::map<nombre, nombre>& periods, const std::map<nombre, nombre>& decomposition) {
        nombre result = 1;
        for (auto [p, e]: decomposition) {
            auto it = periods.find(p);
            if (it == periods.end()) {
                return std::nullopt;
            }
            nombre period = puissance::puissance(p, e - 1) * it->second;
            result = arithmetique::PPCM(result, period);
        }

        return result;
    }
}

ENREGISTRER_PROBLEME(853, "Pisano Periods 1") {
    // For every positive integer $n$ the Fibonacci sequence modulo
    // $n$ is periodic. The period depends on the value of $n$.
    // This period is called the <strong>Pisano period</strong> for $n$, often shortened to $\pi(n)$.</p>
    //
    // There are three values of $n$ for which
    // $\pi(n)$ equals $18$: $19$, $38$ and $76$. The sum of those smaller than $50$ is $57$.
    //
    // Find the sum of the values of $n$ smaller than $1\,000\,000\,000$ for which $\pi(n)$ equals $120$.
    nombre limit_period = 120;
    nombre limit = 1'000'000'000;
    std::deque<nombre> premiers;
    {
        Timer t("crible");
        premiers::crible235<nombre>(limit, std::back_inserter(premiers));
    }

    std::cout << "P(19) = " << pisanoPeriod(19, 1'000'000) << std::endl;
    std::cout << "P(38) = " << pisanoPeriod(38, 1'000'000) << std::endl;
    std::cout << "P(76) = " << pisanoPeriod(76, 1'000'000) << std::endl;
    std::cout << "P(361) = " << pisanoPeriod(361, 1'000'000) << std::endl;
    std::cout << "Pk(361) = " << periodPK(19, 2, 1'000'000) << std::endl;
    std::cout << "P(6859) = " << pisanoPeriod(6859, 1'000'000) << std::endl;
    std::cout << "Pk(6859) = " << periodPK(19, 3, 1'000'000) << std::endl;

    std::map<nombre, nombre> periods;

    {
        Timer t("periods");
        for (auto p: premiers) {
            auto period = pisanoPeriod(p, limit_period);
            if (period.has_value() && limit_period % period.value() == 0) {
                // std::cout << p << " ==> " << period << std::endl;
                periods[p] = period.value();
            }
        }
    }

    std::map<nombre, std::map<nombre, nombre>> decompositions;

    for (const auto p: periods | std::views::keys) {
        // std::cout << entry.first << " " << entry.second << std::endl;
        std::map<nombre, std::map<nombre, nombre>> new_decompositions(decompositions);
        for (nombre pk = p, e = 1; pk <= limit; pk *= p, e++) {
            std::cout << p << "^" << e << " = " << pk << std::endl;
            new_decompositions[pk][p] = e;
            for (const auto&[m, d]: decompositions) {
                nombre n = pk * m;
                if (n > limit) {
                    break;
                }
                new_decompositions[n][p] = e;
                new_decompositions[n].insert(d.begin(), d.end());
            }
        }
        decompositions = new_decompositions;
    }

    std::cout << decompositions.size() << std::endl;

    nombre result = 0;

    for (const auto& [n, decomposition]: decompositions) {
        auto period = pisanoPeriod(periods, decomposition);
        // std::cout << n << " ==> " << period << std::endl;
        if (period.has_value() && period.value() == limit_period) {
            // std::cout << n << " ==> " << period << std::endl;
            result += n;
        }
    }

    return std::to_string(result);
}
