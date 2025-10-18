#pragma once

#include "numerique.h"

#include <algorithm>
#include <optional>

#include "premiers.h"

namespace crible {

    // https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Algorithm
    std::optional<unsigned long> pollard_rho(unsigned long n);
    std::optional<unsigned long long> pollard_rho(unsigned long long n);

    std::optional<unsigned long> pollard_brent(unsigned long n);
    std::optional<unsigned long long> pollard_brent(unsigned long long n);

    template<typename Nombre, typename Conteneur>
    std::deque<Nombre> facteurs_premiers(Nombre n, const Conteneur &premiers) {
        std::deque<Nombre> facteurs;

        for (auto premier: premiers) {
            while (n % premier == 0) {
                facteurs.push_back(premier);
                n /= premier;
            }
            if (premier > n) {
                break;
            }
        }

        if (n < 2) {
            return facteurs;
        }

        while (n > 1) {
            if (premiers::miller_rabin(n)) {
                facteurs.push_back(n);
                break;
            }

            if (auto rho = pollard_rho(n)) {
                auto facteurs_rho = facteurs_premiers(rho.value(), premiers);
                facteurs.insert(facteurs.end(), facteurs_rho.begin(), facteurs_rho.end());
                n /= rho.value();
            } else if (auto brent = pollard_brent(n)) {
                auto facteurs_brent = facteurs_premiers(brent.value(), premiers);
                facteurs.insert(facteurs.end(), facteurs_brent.begin(), facteurs_brent.end());
                n /= brent.value();
            }
        }

        std::sort(facteurs.begin(), facteurs.end());
        return facteurs;
    }

}
