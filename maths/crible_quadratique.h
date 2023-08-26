#pragma once

#include <deque>

#include "arithmetique.h"
#include "premiers.h"
#include "distribution.h"

namespace crible {
    template<typename Nombre>
    Nombre abs(Nombre x, Nombre y) {
        return x > y ? x - y : y - x;
    }

    template<typename Nombre>
    Nombre g1(Nombre x, Nombre n) {
        return (x * x + 1) % n;
    }

    // https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Algorithm
    template<typename Nombre>
    std::optional<Nombre> pollard_rho(Nombre n) {
        Nombre loop = 1;
        Nombre count;
        Nombre x_fixed = 2;
        Nombre x = 2;
        Nombre size = 2;
        Nombre factor;

        do {
            // printf("----   loop %4i   ----\n", loop);
            count = size;
            do {
                x = g1(x, n);
                factor = arithmetique::PGCD(abs(x, x_fixed), n);
                // printf("count = %4i  x = %6i  factor = %i\n", size - count + 1, x, factor);
            } while ((--count > 0) && (factor == 1));
            size *= 2;
            x_fixed = x;
            loop = loop + 1;
        } while (factor == 1);
        // printf("factor is %i\n", factor);

        if (factor == n) {
            return std::nullopt;
        } else {
            return std::make_optional(factor);
        }
    }

    template<typename Nombre>
    std::optional<Nombre> pollard_brent(Nombre n) {
        std::mt19937 &mt = distribution::generator();

        std::uniform_int_distribution<Nombre> distribution(1, n - 1);

        Nombre y = distribution(mt);
        Nombre c = distribution(mt);
        Nombre m = distribution(mt);

        Nombre g = 1;
        size_t r = 1;
        Nombre q = 1;

        Nombre ys = 1;
        Nombre x = 1;

        while (g == 1) {
            x = y;
            for (size_t i = 0; i < r; ++i) {
                y = y * y + c;
                y %= n;
            }

            Nombre k = 0;
            while (k < r && g == 1) {
                ys = y;
                size_t iMin = std::min(m, r - k);
                for (size_t i = 0; i < iMin; ++i) {
                    y = y * y + c;
                    y %= n;

                    q = (q * abs(x, y)) % n;
                }

                g = arithmetique::PGCD(q, n);
                k += m;
            }

            r *= 2;
        }

        if (g == n) {
            while (true) {
                ys = (ys * ys + c) % n;
                g = arithmetique::PGCD(abs(x, ys), n);
                if (g > 1) {
                    break;
                }
            }
        }

        return std::move(g);
    }

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
